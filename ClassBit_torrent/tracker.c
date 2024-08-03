#include "./include/tracker.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <string.h>
#include <stdlib.h>

#define SHA1_LENGTH 20

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        printf("not enough memory\n");
        return 0;
    }
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void getTrackers(Metadata *data) {
    CURL *curl;
    CURLcode res;

    char url[MAX_URL_LENGTH];
    struct MemoryStruct chunk;

    chunk.memory = malloc(1); // will grow as needed
    chunk.size = 0;

    const char *tracker_url;
    if (data->announce) {
        tracker_url = data->announce;
    } else if (data->announce_list && data->a_length > 0) {
        tracker_url = data->announce_list[0];
    } else {
        fprintf(stderr, "No trackers available\n");
        return;
    }

    unsigned char *info_hash = data->info_hash;
    const char *peer_id = "-AZ2060-123456789012"; // Example peer ID

    int port = 6881;
    long long uploaded = 0;
    long long downloaded = 0;
    long long left = data->t_size - downloaded;
    const char *event = "started";

    curl = curl_easy_init();
    if (curl) {
        char *encoded_info_hash = curl_easy_escape(curl, (const char *)info_hash, 20);
        char *encoded_peer_id = curl_easy_escape(curl, peer_id, strlen(peer_id));

        if (encoded_info_hash && encoded_peer_id) {
            snprintf(url, MAX_URL_LENGTH,
                     "%s?info_hash=%s&peer_id=%s&port=%d&uploaded=%lld&downloaded=%lld&left=%lld&compact=1&no_peer_id=1&event=%s",
                     tracker_url, encoded_info_hash, encoded_peer_id, port, uploaded, downloaded, left, event);

            printf("Generated URL: %s\n", url); // Print the generated URL for debugging

            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // Enable verbose output

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            } else {
                printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
                printf("Response: %.100s\n", chunk.memory);
            }

            curl_free(encoded_info_hash);
            curl_free(encoded_peer_id);
        } else {
            fprintf(stderr, "Failed to encode info_hash or peer_id\n");
        }
        curl_easy_cleanup(curl);
    }
    free(chunk.memory);
}
