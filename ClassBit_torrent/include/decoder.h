#ifndef DECODER_H
#define DECODER_H
#include <stdint.h>
#include "io.h"
#include <string.h>
#include <openssl/sha.h>

//last minute change this torrent client will only work with single file torrent

typedef struct{
    char *announce;
    char **announce_list;
    uint32_t a_length;
    uint64_t p_length;
    char *p_hashes;
    uint32_t num_files;
    char *name;
    uint64_t t_size;
    char **url_list;
    uint32_t num_url;
    char *info;
    unsigned char info_hash[SHA_DIGEST_LENGTH];
}Metadata;

Metadata *getData(torrent *t);
void test(torrent *t);
void singleDecoder(torrent *torrent);
#endif //DECODER_H