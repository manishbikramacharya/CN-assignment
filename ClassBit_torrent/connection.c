#include "include/connnection.h"
#include <arpa/inet.h>
#include <openssl/sha.h>
#include <sys/socket.h>

void send_handshake(int sock, const unsigned char *info_hash, const char *peer_id) {
    unsigned char handshake[HANDSHAKE_LEN];
    memset(handshake, 0, HANDSHAKE_LEN);

    handshake[0] = 19; // Protocol identifier length
    memcpy(&handshake[1], "BitTorrent protocol", 19); // Protocol identifier
    // Reserved bytes are already zeroed out by memset
    memcpy(&handshake[28], info_hash, 20); // Info hash
    memcpy(&handshake[48], peer_id, 20); // Peer ID

    printf("Sending Handshake: ");
    for (int i = 0; i < HANDSHAKE_LEN; i++) {
        printf("%02x", handshake[i]);
    }
    printf("\n");

    // Sending handshake
    send(sock, handshake, HANDSHAKE_LEN, 0);
}

void receive_handshake(int sock, unsigned char *info_hash) {
    unsigned char handshake[HANDSHAKE_LEN];

    recv(sock, handshake, HANDSHAKE_LEN, 0);

    printf("Received Handshake: ");
    for (int i = 0; i < HANDSHAKE_LEN; i++) {
        printf("%02x", handshake[i]);
    }
    printf("\n");

    if (memcmp(&handshake[28], info_hash, 20) != 0) {
        fprintf(stderr, "Info hash does not match\n");
        close(sock);
        exit(1);
    }

    printf("Handshake successful\n");
}
void send_interesteed(int sock) {
    unsigned char message[5];
    memset(message, 0, 5);

    message[3] = 1;

    message[4] = 2;

    if(send(sock, message, 5, 0) < 0) {
        perror("send interested");
        close(sock);
        exit(1);
    }

    printf("Sent interested message\n");
}

void request_piece(int sock, int piece_index, int block_offset, int block_length) {

    unsigned char message[17];
    int len = htonl(13);
    memcpy(message, &len, 4);
    message[4]= 6;
    int index = htonl(piece_index);
    memcpy(&message[5], &index, 4);
    int offset = htonl(block_offset);
    memcpy(&message[9], &offset, 4);
    int length = htonl(block_length);
    memcpy(&message[13], &length, 4);

    if(send(sock, message, 17, 0) < 0){
        perror("send request");
        close(sock);
        exit(1);
    }

    printf("Requested piece %d, offset %d, length %d\n", piece_index, block_offset, block_length);
}

void receive_piece(int sock, unsigned char *buffer, int buffer_len) {
    int bytes_received = 0;
    while(bytes_received < buffer_len) {
        int result = recv(sock, buffer + bytes_received, buffer_len - bytes_received, 0);
    
        if(result < 0) {
            perror("recv");
            close(sock);
            exit(1);
        }

        bytes_received += result;
    }
}


void write_piece_to_file(const unsigned char *data, int data_len, FILE *file){
    if(fwrite(data, 1,data_len, file) != data_len){
        perror("fwrite");
        fclose(file);
        exit(1);
    }
}


int verify_piece(const unsigned char *piece_data, int piece_length, const unsigned char *expected_hash){
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(piece_data, piece_length, hash);
    return memcmp(hash, expected_hash, SHA_DIGEST_LENGTH) == 0;
}


void connect_to_peer(const char *ip, uint16_t port, const unsigned char *info_hash, const char *peer_id) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0){
        perror("socket");
        exit(1);
    }

    struct sockaddr_in peer_addr;

    peer_addr.sin_family = AF_INET;
    peer_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &peer_addr.sin_addr);


    if(connect(sock, (struct sockaddr *)&peer_addr, sizeof(peer_addr)) < 0) {
        perror("connect");
        close(sock);
        exit(1);
    }

    send_handshake(sock, info_hash, peer_id);
    receive_handshake(sock, (unsigned char *)info_hash);


    //could exchange messages but rn dunno how
    close(sock);
}