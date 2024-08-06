#include "include/piecemanager.h"
#include "include/decoder.h"
#include <string.h>

PieceManager *create_piece_manager(Metadata *data) {
    PieceManager *pm = malloc(sizeof(*pm));
    pm->num_pieces = ((data->t_size + data->p_length - 1) / data->p_length);
    pm->piece_length = data->p_length;
    pm->file_length = data->t_size;
    pm->bitfield = calloc((pm->num_pieces + 7) / 8, sizeof(uint8_t));
    pm->downloaded = &data->downloaded;
    pm->uploaded = &data->uploaded;
    pm->pieces_hash = data->p_hashes;
    
    size_t tempLen = strlen("downloadedFile/") + strlen(data->name) + 1;
    char *downloadLocation = malloc(tempLen);
    strcpy(downloadLocation, "downloadedFile/");
    strcat(downloadLocation, data->name);
    downloadLocation[tempLen - 1] = 0;
    pm->fp = fopen(downloadLocation, "wb");
    free(downloadLocation);
    
    return pm;
}

void clean_pm(PieceManager *pm) {
    free(pm->bitfield);
    fclose(pm->fp);
    free(pm);
}

int select_piece(PieceManager *pm, uint8_t *peer_bitfield, int bitfield_len) {
    for (size_t i = 0; i < pm->num_pieces; i++) {
        // Check if the piece is not downloaded and the peer has it
        if (!is_piece_downloaded(pm, i) && (i / 8 < bitfield_len) && (peer_bitfield[i / 8] & (1 << (7 - (i % 8))))) {
            return i;
        }
    }
    return -1; // no piece left to download from this peer
}

void mark_as_downloaded(PieceManager *pm, int piece_index) {
    if (piece_index >= 0 && piece_index < pm->num_pieces) {
        pm->bitfield[piece_index / 8] |= (1 << (7 - (piece_index % 8)));
        *(pm->downloaded) += (piece_index == pm->num_pieces - 1) ? 
            (pm->file_length % pm->piece_length) : pm->piece_length;
    }
}

int is_piece_downloaded(PieceManager *pm, int piece_index) {
    if (piece_index >= 0 && piece_index < pm->num_pieces) {
        return (pm->bitfield[piece_index / 8] & (1 << (7 - (piece_index % 8)))) != 0;
    }
    return 0;
}

int are_all_pieces_downloaded(PieceManager *pm) {
    for (int i = 0; i < pm->num_pieces; i++) {
        if (!is_piece_downloaded(pm, i)) {
            return 0;
        }
    }
    return 1;
}
