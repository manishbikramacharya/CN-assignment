#ifndef TRACKER_H
#define TRACKER_H

#include "decoder.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include "connection.h"
#include <arpa/inet.h>

#define MAX_URL_LENGTH 2048

struct peersinfo{
    char ip[INET_ADDRSTRLEN];
    uint16_t port;
};


typedef struct{
    struct peersinfo *peer;
}availablePeers;

typedef struct{
    uint64_t interval_len;
    char *peerList;
    size_t peerLen;
    char *nxttrackerID;
}ResponseBody;


typedef struct trackerinfo{
    uint64_t interval;
    uint32_t numPeers; //actual number of peer and not the length of the message from peer
    availablePeers plist;
}trackerinfo;


struct MemoryStruct{
    char *memory;
    size_t size;
};

trackerinfo getPeerlist(Metadata *data);
#endif //TRACKER_H