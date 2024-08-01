#ifndef IO_H
#define IO_H

#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define FREE(x) do{(munmap(x->info, x->len));}while(0)

typedef struct {
    char *info;
    size_t len;
}torrent;

torrent *load(char *path);

#endif //IO_H