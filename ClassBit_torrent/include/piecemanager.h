#ifndef PIECEMANAGER_H
#define PIECEMANAGER_H

#include <stdint.h>
#include <stdlib.h>
#include "decoder.h"
#include <stdio.h>

typedef struct {
    uint8_t *bitfield;
    size_t num_pieces;
    size_t piece_length;
    size_t file_length;
    char *pieces_hash;
    uint64_t *downloaded;
    uint64_t *uploaded;
    FILE *fp;
}PieceManager;

int is_piece_downloaded(PieceManager *pm, int piece_index);
int are_all_pieces_downloaded(PieceManager *pm);
PieceManager *create_piece_manager(Metadata *data);
void clean_pm(PieceManager *pm);
int select_piece(PieceManager *pm, const unsigned char *peer_bitfield);
void mark_as_downloaded(PieceManager *pm, int piece_index);

#endif //PIECEMANAGER_H
