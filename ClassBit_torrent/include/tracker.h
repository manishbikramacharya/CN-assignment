#ifndef TRACKER_H
#define TRACKER_H

#include "decoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_URL_LENGTH 2048

struct MemoryStruct{
    char *memory;
    size_t size;
};

void getTrackers(Metadata *data);

#endif //TRACKER_H