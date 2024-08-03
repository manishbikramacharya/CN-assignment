#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <openssl/sha.h>

void getinfoHash(unsigned char *dest, const char *src, size_t src_len) {
    SHA1((unsigned char *)src, src_len, dest);
}

uint64_t getinfoindex(char *str, size_t sindex) {
    uint32_t depth = 1;
    uint64_t curr_index = sindex + 1;
    while (depth) {
        if (str[curr_index] == 'd' || str[curr_index] == 'l') {
            depth++;
            curr_index++;
        } else if (str[curr_index] == 'e') {
            depth--;
            curr_index++;
        } else if (str[curr_index] >= '0' && str[curr_index] <= '9') {
            char *endptr;
            uint64_t length = strtol(&str[curr_index], &endptr, 10);
            curr_index = endptr - str;
            curr_index += length + 1; // Move past the length and the ':'
        } else if (str[curr_index] == 'i') {
            curr_index++;
            char *endptr;
            strtol(&str[curr_index], &endptr, 10);
            curr_index = endptr - str;
            curr_index++; // Move past the 'e' of the integer
        } else {
            fprintf(stderr, "Unexpected character at index %zu: %c\n", curr_index, str[curr_index]);
            exit(EXIT_FAILURE);
        }

        if (curr_index >= strlen(str)) {
            fprintf(stderr, "Reached end of string without closing the dictionary.\n");
            exit(EXIT_FAILURE);
        }
    }
    return curr_index;
}
int main() {
    char *str = "d4:name12:complex_file12:piece lengthi262144e6:pieces32:12345678901234567890123456789012e5:filesld6:lengthi12345e4:pathl6:folder6:1.txted6:lengthi67890e4:pathl6:folder6:2.txtee";
    uint64_t s_len = 0;
    uint64_t end_len = getinfoindex(str, s_len);

    char *info_dict = malloc(end_len - s_len + 1);
    if (info_dict == NULL) {
        perror("malloc failed");
        return 1;
    }

    const char *test_info_dict = "d4:name12:example_file12:piece lengthi262144e6:pieces20:12345678901234567890e";
    unsigned char test_hash[20];
    getinfoHash(test_hash, test_info_dict, strlen(test_info_dict));
    printf("Test info hash: ");
    for (int i = 0; i < 20; i++) {
        printf("%02x", test_hash[i]);
    }
    printf("\n");

    memcpy(info_dict, str, end_len - s_len);
    info_dict[end_len - s_len] = '\0'; // Null-terminate the string

    //printf("<%zu-%zu>%s\n and strlen gives= %zu\n", s_len, end_len, info_dict, strlen(str));

    free(info_dict);
    return 0;
}
