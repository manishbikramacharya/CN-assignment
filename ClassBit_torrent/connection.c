#include "include/connection.h"
#include "include/downloader.h"
#include "include/piecemanager.h"
#include <arpa/inet.h>
#include <errno.h>
#include <openssl/sha.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HANDSHAKE_LEN 68
#define BLOCK_SIZE 16384 // Standard block size in BitTorrent

static int handshake(int sock, const unsigned char *info_hash, const char *peer_id) {
    unsigned char handshake[HANDSHAKE_LEN] = {0};
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

    unsigned char recv_handshake[HANDSHAKE_LEN] = {0};

    if (recv(sock, recv_handshake, 68, 0) < 0) {
        perror("receive handshake");
        close(sock);
        return 0;
    }
    printf("Received handshake: ");
    for (int i = 0; i < 68; i++) {
        printf("%02x", recv_handshake[i]);
    }
    printf("\n");

    if (memcmp(&recv_handshake[28], info_hash, 20) != 0) {
        fprintf(stderr, "Unmatching handshake\n");
        close(sock);
        return 0;
    }
    printf("Handshake successful\n");
    return 1;
}

static void sendInterestedMessage(int sock) {
    unsigned char message[5] = {0, 0, 0, 1, 2};
    if (send(sock, message, 5, 0) < 0) {
        perror("Send interested");
        close(sock);
        exit(1);
    }
    printf("Successfully sent interested message\n");
}

static void send_have(int sock, int piece_index) {
    unsigned char message[9] = {0};
    int len = htonl(5);
    int index = htonl(piece_index);

    memcpy(message, &len, 4);
    message[4] = 4;
    memcpy(&message[5], &index, 4);

    if (send(sock, message, 9, 0) < 0) {
        perror("send have");
        close(sock);
        exit(1);
    }

    printf("Sent have message for piece %d\n", piece_index);
}

static void request_piece(int sock, int piece_index, int begin, int length) {
    unsigned char message[17] = {0};
    int len = htonl(13);
    int index = htonl(piece_index);
    int offset = htonl(begin);
    int block_length = htonl(length);

    memcpy(message, &len, 4);
    message[4] = 6; // request message id
    memcpy(&message[5], &index, 4);
    memcpy(&message[9], &offset, 4);
    memcpy(&message[13], &block_length, 4);

    if (send(sock, message, 17, 0) < 0) {
        perror("send request");
        close(sock);
        exit(1);
    }

    printf("Sent request for piece %d, offset %d, length %d\n", piece_index, begin, length);
}

void connect_to_peer(const char *ip, uint16_t port, const unsigned char *info_hash, const char *peer_id, PieceManager *pm) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket connection");
        return;
    }

    struct sockaddr_in peer_addr = {0};
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &peer_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&peer_addr, sizeof(peer_addr)) < 0) {
        perror("Connection error");
        close(sock);
        return;
    }

    if (!handshake(sock, info_hash, peer_id)) {
        return;
    }

    sendInterestedMessage(sock);

    unsigned char *peer_bitfield = NULL;
    int bitfield_len = 0;
    int unchoked = 0;

    unsigned char *current_piece = NULL;
    int current_piece_index = -1;
    int bytes_received = 0;

    while (1) {
        unsigned char len_buf[4] = {0};
        ssize_t recv_bytes = recv(sock, len_buf, 4, 0);
        if (recv_bytes <= 0) {
            if (recv_bytes == 0) {
                printf("Peer has closed the connection\n");
            } else {
                perror("receive length");
            }
            break;
        }

        if (recv_bytes < 4) {
            fprintf(stderr, "Incomplete length received\n");
            continue; // attempt to receive again
        }

        int len = ntohl(*(int *)len_buf);
        if (len == 0) {
            printf("Keep alive message received\n");
            continue;
        }

        printf("Length received %d\n", len);
        if (len < 0 || len > 65536) { // Check for invalid lengths
            fprintf(stderr, "Invalid message length\n");
            break;
        }

        unsigned char *message = malloc(len);
        if (message == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            break;
        }

        size_t total_received = 0;
        while (total_received < len) {
            recv_bytes = recv(sock, message + total_received, len - total_received, 0);

            if (recv_bytes <= 0) {
                if (recv_bytes == 0) {
                    printf("Peer closed connection while receiving message\n");
                } else if (errno != EINTR && errno != EAGAIN) {
                    perror("received message");
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
            case 4: {
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
                    if (peer_bitfield == NULL) {
                        fprintf(stderr, "Memory allocation error\n");
                        free(message);
                        goto cleanup;
                    }
                    memcpy(peer_bitfield, &message[1], bitfield_len);
                }
                break;
            case 7: {
                printf("Received piece message\n");
                int index = ntohl(*(int *)&message[1]);
                int begin = ntohl(*(int *)&message[5]);

                int block_length = len - 9;
                unsigned char *block_data = &message[9];

                if (index != current_piece_index) {
                    if (current_piece != NULL) {
                        free(current_piece);
                    }
                    current_piece = malloc(pm->piece_length);
                    if (current_piece == NULL) {
                        fprintf(stderr, "Memory allocation error\n");
                        free(message);
                        goto cleanup;
                    }
                    current_piece_index = index;
                    bytes_received = 0;
                }

                if (begin + block_length <= pm->piece_length) {
                    memcpy(current_piece + begin, block_data, block_length);
                    bytes_received += block_length;

                    printf("Received %d bytes for piece %d (total: %d/%zu)\n", 
                           block_length, index, bytes_received, pm->piece_length);

                    if (bytes_received == pm->piece_length) {
                        unsigned char hash[SHA_DIGEST_LENGTH];
                        SHA1(current_piece, pm->piece_length, hash);

                        if (memcmp(hash, &pm->pieces_hash[index * SHA_DIGEST_LENGTH], SHA_DIGEST_LENGTH) == 0) {
                            printf("Piece %d downloaded and verified successfully\n", index);
                            write_piece_to_file(current_piece, pm->piece_length, pm->fp, index, 0, pm);
                            mark_as_downloaded(pm, index);
                            send_have(sock, index);

                            free(current_piece);
                            current_piece = NULL;
                            current_piece_index = -1;
                            bytes_received = 0;
                        } else {
                            fprintf(stderr, "Failed to verify piece %d\n", index);
                            bytes_received = 0;
                        }
                    }
                } else {
                    fprintf(stderr, "Received invalid piece data\n");
                }
                break;
            }
            default:
                printf("Currently this message id isn't supported: %d\n", message_id);
                break;
        }
        free(message);

        if (unchoked) {
            int piece_index = select_piece(pm, peer_bitfield, bitfield_len);
            if (piece_index != -1) {
                int piece_length = (piece_index == pm->num_pieces - 1) ? 
                    (pm->file_length % pm->piece_length) : pm->piece_length;
                
                for (int offset = 0; offset < piece_length; offset += BLOCK_SIZE) {
                    int length = (offset + BLOCK_SIZE > piece_length) ? (piece_length - offset) : BLOCK_SIZE;
                    request_piece(sock, piece_index, offset, length);
                }
            } else {
                printf("All pieces from this peer downloaded. Closing connection...\n");
                break;
            }
        }

        if (are_all_pieces_downloaded(pm)) {
            printf("Download completed successfully!\n");
            break;
        }
    }

cleanup:
    if (current_piece != NULL) {
        free(current_piece);
    }
    free(peer_bitfield);
    close(sock);
}
