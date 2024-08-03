#include "include/hash.h"
#include <openssl/sha.h>
#include <stdio.h>

void getinfoHash(unsigned char *dest, const char *src, size_t src_len) {
    SHA1((unsigned char *)src, src_len, dest);
}

void printSHA1(unsigned char *hash, size_t length){
    for(size_t i=0; i < length; i++){
        printf("%02x", hash[i]);
    }

    printf("\n");
}