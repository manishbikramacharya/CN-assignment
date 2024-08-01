#include <stdio.h>
#include "include/io.h"
#include "include/decoder.h"

int main(){
    torrent *tfile = load("torrentfiles/debian-edu-12.5.0-amd64-netinst.iso.torrent");
    if(!tfile) 
        fprintf(stderr, "Error try again later\n");
    //printf("%s\n", tfile->info);
    singleDecoder(tfile);
    FREE(tfile);
    free(tfile);
    return 0;
}
