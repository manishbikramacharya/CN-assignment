#ifndef HASH_H
#define HASH_H

#include <openssl/sha.h>

unsigned char *getInfoHash(const char *src, size_t src_len);
void getinfoHash(unsigned char *dest, const char *src, size_t src_len);
void printSHA1(unsigned char *hash, size_t length);
#endif //HASH_H