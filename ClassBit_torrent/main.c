#include <stdio.h>
#include "include/io.h"
#include "include/decoder.h"

int main(){
    torrent *tfile = load("torrentfiles/debian-12.6.0-amd64-netinst.iso.torrent");
    if(!tfile) 
        fprintf(stderr, "Error try again later\n");
    singleDecoder(tfile);
    FREE(tfile);
    free(tfile);
    return 0;
}
