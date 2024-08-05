#include "./include/tracker.h"
#include "include/decoder.h"

#include <stdint.h>

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

ResponseBody parseResponse(struct MemoryStruct *response){
    size_t index = 0;
    ResponseBody Response={
        .interval_len = 0,
        .nxttrackerID = NULL,
        .peerLen = 0,
        .peerList = NULL,
    };

    while(index < response->size){
        while(response->memory[index] == 'd' || response->memory[index] == 'l' || response->memory[index] == 'e')   index++;
        char *k = getbstring(response->memory, &index);
        if(strcmp(k, "interval") == 0){
            uint64_t interval_length = getLength(response->memory, &index);
            Response.interval_len = interval_length;
        }
        if(strcmp(k, "peers") == 0){
            char *endptr;
            Response.peerLen = strtol(&response->memory[index], &endptr, 10);
            Response.peerList = getbstring(response->memory, &index);
        }
        if(strcmp(k, "tracker id") == 0){
            Response.nxttrackerID = getbstring(response->memory, &index);
        }
        free(k);
    }
    return Response;
}

availablePeers parse_peers(ResponseBody response) {
    if (response.peerLen % 6 != 0) {
        fprintf(stderr, "Invalid peers length\n");
        exit(1);
    }
    availablePeers ap;
    ap.peer = malloc(sizeof(struct peersinfo) * ((response.peerLen)/6));
    for (size_t i = 0, y = 0; i < response.peerLen; i += 6, y++) {
        snprintf(ap.peer[y].ip, sizeof(ap.peer[y].ip), "%u.%u.%u.%u", 
            (unsigned char)response.peerList[i], 
            (unsigned char)response.peerList[i + 1], 
            (unsigned char)response.peerList[i + 2], 
            (unsigned char)response.peerList[i + 3]);

        ap.peer[y].port = ((unsigned char)response.peerList[i + 4] << 8) | (unsigned char)response.peerList[i + 5];

        printf("Peer: %s:%u\n", ap.peer[y].ip, ap.peer[y].port);
    }
    return ap;
}

trackerinfo getPeerlist(Metadata *data) {
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
        exit(1);
    }

    unsigned char *info_hash = data->info_hash;
    const char *peer_id = "-AZ2060-123456789012";

    int port = 6881;
    uint64_t uploaded = data->uploaded;
    uint64_t downloaded = data->downloaded;
    uint64_t left = data->t_size - downloaded;
    const char *event = "started";

    curl = curl_easy_init();
    
    trackerinfo tracker;

    if (curl) {
        char *encoded_info_hash = curl_easy_escape(curl, (const char *)info_hash, 20);
        char *encoded_peer_id = curl_easy_escape(curl, peer_id, strlen(peer_id));

        if (encoded_info_hash && encoded_peer_id) {
            snprintf(url, MAX_URL_LENGTH,
                     "%s?info_hash=%s&peer_id=%s&port=%d&uploaded=%zu&downloaded=%zu&left=%zu&compact=1&no_peer_id=1&event=%s",
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

                ResponseBody ResponseValues = parseResponse(&chunk);
                printf("Interval_Length = %zu\nPeer_Len = %zu\nPeer_List:-%s\nNext_peerid = %s\n", ResponseValues.interval_len, ResponseValues.peerLen, ResponseValues.peerList, ResponseValues.nxttrackerID);
                tracker.numPeers = (ResponseValues.peerLen/ 6);
                tracker.interval = ResponseValues.interval_len;
                tracker.plist = parse_peers(ResponseValues);
                free(ResponseValues.peerList);
            }

            curl_free(encoded_info_hash);
            curl_free(encoded_peer_id);
        } else {
            fprintf(stderr, "Failed to encode info_hash or peer_id\n");
        }
        curl_easy_cleanup(curl);
    }
    free(chunk.memory);
    return tracker;
}
