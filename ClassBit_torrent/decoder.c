#include "./include/decoder.h"
#include <openssl/sha.h>
#include <stdint.h>
#include <string.h>
#include "./include/hash.h"
#include "include/tracker.h"

void print_hex(char *data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02x ", (unsigned char)data[i]);
    }
    printf("\n");
}

static char *getbstring(char *str, size_t *index){
    //general bencoded string.
    char *endptr;
    long long len = strtol(&str[*index], &endptr, 10);
    *index = endptr - str;
    if(str[*index] == ':') (*index)++;
    char *string = malloc(len + 1);
    memcpy(string, &str[*index], len);
    string[len] = 0;
    *index += len;
    return string;
}

uint64_t getLength(char *str, size_t *index){
    (*index)++;
    char *endptr;
    long long len = strtol(&str[*index], &endptr, 10);
    *index = endptr - str;
    if(str[*index] == 'e') (*index)++;
    return len;
}

uint64_t getinfoindex(char *str, size_t sindex, size_t total_length){
    uint64_t depth = 1;
    uint64_t curr_index = sindex+1;
    while(depth){
        switch(str[curr_index]){
            case 'd':
            case 'l':
                ++depth, ++curr_index;
                break;
            
            case 'e':
                --depth, ++curr_index;
                break;
            case '0' ... '9':{
                char *endptr;
                long long len = strtol(&str[curr_index],&endptr, 10);
                curr_index = (endptr-str)+1+len;
                break;
            }

            case 'i':{
                ++depth, ++curr_index;
                char *endptr;
                long long len = strtol(&str[curr_index], &endptr, 10);
                curr_index = endptr- str;
                break;
            }

            default:
                break;
        }
    }
    return curr_index;
}

void singleDecoder(torrent *torrent){
    size_t index = 0;
    Metadata data = {
        .a_length = 0,
        .announce = NULL,
        .announce_list = NULL,
        .url_list = NULL,
        .p_hashes = NULL,
        .name = NULL,
        .num_files = 0,
        .p_length = 0,
        .info = NULL,
        .info_hash = {0},
        .t_size = 0,
    };

    size_t start_addr = 0;
    size_t end_addr = 0;    
    while(index < torrent->len){
        while(torrent->info[index] == 'd' || torrent->info[index] == 'l' || torrent->info[index] == 'e') index++;
        
        char *k = getbstring(torrent->info, &index);

        if(strcmp(k, "length") == 0){
            data.t_size = getLength(torrent->info, &index);
            while(torrent->info[index] == 'd' || torrent->info[index] == 'l' || torrent->info[index] == 'e') index++;
        }

        if(strcmp(k, "info") == 0){
            start_addr = index;
        }
        if(strcmp(k, "name") == 0 || strcmp(k, "path") == 0){
            while(torrent->info[index] == 'd' || torrent->info[index] == 'l' || torrent->info[index] == 'e') index++;
            data.name = getbstring(torrent->info, &index);
            /*add core for nested folders imao*/
            while(torrent->info[index] == 'd' || torrent->info[index] == 'l' || torrent->info[index] == 'e') index++;
        }
        if(strcmp(k, "piece length") == 0){
            data.p_length = getLength(torrent->info, &index);
        }
        if(torrent->info[index] == 'i'){ //these are for the ones we don't care at all
            long long a = getLength(torrent->info, &index);
        }
        if(strcmp(k, "announce") == 0){
            data.announce = getbstring(torrent->info, &index);
        }
        if(strcmp(k, "pieces") == 0){
            data.p_hashes = getbstring(torrent->info, &index);
        }

        if(strcmp(k, "announce-list") == 0){
            while(torrent->info[index] != 'e'){ //this e is breaking the program
                while(torrent->info[index] == 'd' || torrent->info[index] == 'l' || torrent->info[index] == 'e') index++; //consumes all 'l'
                data.announce_list = realloc(data.announce_list, sizeof(char *) * (data.a_length+1));
                data.announce_list[data.a_length++] = getbstring(torrent->info, &index);
                if(torrent->info[index] == 'e') index++;
            }
            index++;
        }
        if(strcmp(k, "url-list") == 0){
            index++;
            while(torrent->info[index] != 'e'){
                data.url_list = realloc(data.url_list,(data.num_url + 1) *sizeof(char *));
                data.url_list[data.num_url++] = getbstring(torrent->info, &index);
            }
        }
    }

    end_addr = getinfoindex(torrent->info, start_addr, torrent->len);
    data.info = malloc((end_addr - start_addr) +1);
    memcpy(data.info, &torrent->info[start_addr], (end_addr -start_addr));
    data.info[end_addr - start_addr] = 0;
    getinfoHash(data.info_hash, data.info, end_addr - start_addr);

    printf("Name = %s\ntotalSize = %zu\n", data.name, data.t_size);
    printf("announce = %s\npiece_length = %zu\n",
                             data.announce,  data.p_length);

    if(data.announce_list){
        printf("announce list:-\n");
        for(uint32_t i=0; i<data.a_length;i++){
            printf("%s\n", data.announce_list[i]);
        }
    }
    
    printf("url_list:-\n");
    for(uint32_t i=0; i<data.num_url;i++){
        printf("%s\n", data.url_list[i]);
    }
    printf("info_hash:-");
    printSHA1(data.info_hash, 20);

    getTrackers(&data);
    free(data.name);
    free(data.announce);
    free(data.p_hashes);
    free(data.info);
    for(uint32_t i =0; i<data.num_url; i++){
        free(data.url_list[i]);
    }
    free(data.url_list);
    for(uint32_t i=0; i<data.a_length; i++){
        free(data.announce_list[i]);
    }
    free(data.announce_list);
}