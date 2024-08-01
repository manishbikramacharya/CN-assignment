#ifndef TRACKER_H
#define TRACKER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include "decoder.h"


void contact_tracker(Metadata *data);
#endif //TRACKER_H