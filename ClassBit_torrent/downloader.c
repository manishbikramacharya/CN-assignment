#include "include/downloader.h"



void write_piece_to_file(unsigned char *data, int data_len, FILE *fp, int piece_index, int offset, PieceManager *pm){
    fseek(fp, piece_index * pm->piece_length + offset, SEEK_SET);
    if(fwrite(data, 1, data_len, fp) != data_len){
        perror("fwrite");
        exit(1);
    }
    fflush(fp);  // Ensure data is written to disk immediately
}