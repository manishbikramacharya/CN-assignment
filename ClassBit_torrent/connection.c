#include "include/connection.h"
#include "include/downloader.h"
#include "include/piecemanager.h"
#include <arpa/inet.h>
#include <openssl/sha.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_MESSAGE_LENGTH 16384

int handshake(int sock, const unsigned char *info_hash, const char *peer_id) {
    unsigned char handshake[68] = {0};

    handshake[0] = 19;
    memcpy(&handshake[1], "BitTorrent protocol", 19);
    memcpy(&handshake[28], info_hash, 20);
    memcpy(&handshake[48], peer_id, 20);
    printf("Sending Handshake: ");
    for (int i = 0; i < 68; i++) {
        printf("%02x", handshake[i]);
    }
    printf("\n");

    if (send(sock, handshake, 68, 0) < 0) {
        perror("send handshake");
        close(sock);
        return 0;
    }

    unsigned char recv_handshake[68] = {0};

    if (recv(sock, recv_handshake, 68, 0) < 0) {
        perror("receive handshake");
        close(sock);
        return 0;
    }

    printf("Received Handshake: ");
    for (int i = 0; i < 68; i++) {
        printf("%02x", recv_handshake[i]);
    }
    printf("\n");

    if (memcmp(&recv_handshake[28], info_hash, 20) != 0) {
        fprintf(stderr, "Info hash does not match\n");
        close(sock);
        return 0;
    }

    printf("Handshake successful\n");
    return 1;
}

void send_interested(int sock) {
    unsigned char message[5] = {0, 0, 0, 1, 2}; // Length = 1, ID = 2 (interested)

    if (send(sock, message, 5, 0) < 0) {
        perror("send interested");
        close(sock);
        exit(1);
    }

    printf("Sent interested message\n");
}

void send_have(int sock, int piece_index) {
    unsigned char message[9] = {0};
    int len = htonl(5); // Length = 5
    int index = htonl(piece_index);

    memcpy(message, &len, 4);
    message[4] = 4; // ID = 4 (have)
    memcpy(&message[5], &index, 4);

    if (send(sock, message, 9, 0) < 0) {
        perror("send have");
        close(sock);
        exit(1);
    }

    printf("Sent have message for piece %d\n", piece_index);
}

void send_request(int sock, int piece_index, int block_offset, int block_length) {
    unsigned char message[17] = {0};
    int len = htonl(13); // Length = 13
    int index = htonl(piece_index);
    int offset = htonl(block_offset);
    int length = htonl(block_length);

    memcpy(message, &len, 4);
    message[4] = 6; // ID = 6 (request)
    memcpy(&message[5], &index, 4);
    memcpy(&message[9], &offset, 4);
    memcpy(&message[13], &length, 4);

    if (send(sock, message, 17, 0) < 0) {
        perror("send request");
        close(sock);
        exit(1);
    }

    printf("Requested piece %d, offset %d, length %d\n", piece_index, block_offset, block_length);
}

int verify_piece(unsigned char *piece_data, int piece_length, unsigned char *expected_hash) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(piece_data, piece_length, hash);
    return memcmp(hash, expected_hash, SHA_DIGEST_LENGTH) == 0;
}

void connect_to_peer(const char *ip, uint16_t port, const unsigned char *info_hash, const char *peer_id, PieceManager *pm) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        return;
    }

    struct sockaddr_in peer_addr = {0};
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &peer_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&peer_addr, sizeof(peer_addr)) < 0) {
        perror("connect");
        close(sock);
        return;
    }

    if (!handshake(sock, info_hash, peer_id)) {
        return;
    }

    send_interested(sock);
    
    unsigned char *peer_bitfield = NULL;
    int bitfield_len = 0;
    int unchoked = 0;

    while (1) {
        unsigned char len_buf[4] = {0};
        ssize_t recv_bytes = recv(sock, len_buf, 4, 0);
        if (recv_bytes <= 0) {
            if (recv_bytes == 0) {
                printf("Peer has closed the connection\n");
            } else {
                perror("receive length");
            }
            goto cleanup;
        }

        if (recv_bytes < 4) {
            fprintf(stderr, "Incomplete length received\n");
            goto cleanup;
        }

        int len = ntohl(*(int *)len_buf);
        if (len == 0) {
            // Keep-alive message, just continue
            continue;
        }
        if (len < 0 || len > MAX_MESSAGE_LENGTH) {
            fprintf(stderr, "Invalid message length: %d\n", len);
            goto cleanup;
        }

        unsigned char *message = malloc(len);
        size_t total_received = 0;

        while (total_received < len) {
            recv_bytes = recv(sock, message + total_received, len - total_received, 0);
            if (recv_bytes <= 0) {
                if (recv_bytes == 0) {
                    printf("Peer closed connection while receiving message\n");
                } else if (errno != EINTR && errno != EAGAIN) {
                    perror("receive message");
                }
                free(message);
                goto cleanup;
            }
            total_received += recv_bytes;
        }

        int message_id = message[0];

        switch (message_id) {
            case 0:
                printf("Received choke message\n");
                unchoked = 0;
                break;
            case 1:
                printf("Received unchoke message\n");
                unchoked = 1;
                break;
            case 4: { // 'have' message
                if (len != 5) {
                    fprintf(stderr, "Invalid 'have' message length\n");
                    break;
                }
                int piece_index = ntohl(*(int *)&message[1]);
                if (piece_index < 0 || piece_index >= pm->num_pieces) {
                    fprintf(stderr, "Invalid piece index in 'have' message\n");
                    break;
                }
                printf("Received 'have' message for piece %d\n", piece_index);
                break;
            }
            case 5:
                printf("Received bitfield message\n");
                if (peer_bitfield == NULL) {
                    bitfield_len = len - 1;
                    peer_bitfield = malloc(bitfield_len);
                    memcpy(peer_bitfield, &message[1], bitfield_len);
                }
                break;
            case 7: {
                printf("Received piece message\n");
                int index = ntohl(*(int *)&message[1]);
                int begin = ntohl(*(int *)&message[5]);
                int piece_length = len - 9;
                unsigned char *piece_data = &message[9];

                unsigned char expected_hash[SHA_DIGEST_LENGTH];
                memcpy(expected_hash, &pm->pieces_hash[index * SHA_DIGEST_LENGTH], SHA_DIGEST_LENGTH);

                if (verify_piece(piece_data, piece_length, expected_hash)) {
                    write_piece_to_file(piece_data, piece_length, pm->fp, index, begin, pm);
                    printf("Piece %d downloaded and verified successfully\n", index);
                    mark_as_downloaded(pm, index);
                    send_have(sock, index);
                } else {
                    fprintf(stderr, "Failed to verify piece %d\n", index);
                }
                break;
            }
            default:
                printf("Currently this message id isn't supported: %d\n", message_id);
                break;
        }

        free(message);
        
        if (unchoked && peer_bitfield != NULL) {
            int piece_index = select_piece(pm, peer_bitfield);
            if (piece_index != -1) {
                int piece_length = (piece_index == pm->num_pieces - 1) ? 
                    (pm->file_length % pm->piece_length) : pm->piece_length;
                send_request(sock, piece_index, 0, piece_length);
            } else if (are_all_pieces_downloaded(pm)) {
                printf("All pieces downloaded. Closing connection.\n");
                goto cleanup;
            }
        }
    }

cleanup:
    free(peer_bitfield);
    close(sock);
}
