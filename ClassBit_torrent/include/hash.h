#ifndef HASH_H
#define HASH_H

#include <openssl/sha.h>

unsigned char *getInfoHash(const char *src, size_t src_len);
#endif //HASH_H