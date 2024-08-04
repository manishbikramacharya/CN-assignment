#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#define HANDSHAKE_LEN 68

void receive_handshake(int sock, unsigned char *info_hash);
void connect_to_peer(const char *ip, uint16_t port, const unsigned char *info_hash, const char *peer_id);

#endif //CONNECTION_H