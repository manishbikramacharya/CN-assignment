#ifndef CONNECTION_H
#define CONNECTION_H

#include "piecemanager.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#define HANDSHAKE_LEN 68
#define BLOCK_SIZE 16384

void connect_to_peer(const char *ip, uint16_t port, const unsigned char *info_hash, const char *peer_id, PieceManager *pm);

#endif //CONNECTION_H