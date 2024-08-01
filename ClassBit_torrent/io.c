#include "include/io.h"
#include <fcntl.h>
#include <sys/mman.h>

//returns NULL on failure
torrent *load(char *path){

    torrent *t = malloc(sizeof(*t));
    int fd = open(path, O_RDONLY);

    if(fd == -1){
        perror("file opening failed");
        return NULL;
    }
    
    struct stat finfo = {0};
    if(fstat(fd, &finfo) == -1){
        close(fd);
        perror("error getting info from fstat");
        return NULL;
    }

    off_t fsize = finfo.st_size;
    t->len = fsize;
    t->info = (char *) mmap(NULL, fsize, PROT_READ, MAP_PRIVATE, fd, 0);

    if(t->info == MAP_FAILED){
        close(fd);
        perror("failed to allocate enough memory");
        return NULL;
    }
    return t;
}