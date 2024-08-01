#include "include/hash.h"
#include <openssl/sha.h>
#include <stdlib.h>
#include <string.h>

unsigned char *getInfoHash(const char *src, size_t src_len) {
    unsigned char *dest = malloc(SHA_DIGEST_LENGTH);
    if (dest == NULL) {
        return NULL;  // Handle malloc failure
    }
    SHA1((unsigned char *)src, src_len, dest);
    return dest;
}