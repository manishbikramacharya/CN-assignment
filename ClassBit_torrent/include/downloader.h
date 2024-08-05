#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include "piecemanager.h"
#include <stdint.h>
#include <stdio.h>

void write_piece_to_file(unsigned char *data, int data_len, FILE *fp, int piece_index, int offset, PieceManager *pm);

#endif //DOWNLOADER_H