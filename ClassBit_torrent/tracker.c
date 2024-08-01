
#include "include/tracker.h"
#include <sys/socket.h>

void contact_tracker(Metadata *data){


    struct sockaddr_in server_addr;
    struct hostent *server;

    int sockfd;
    char buffer[1024];

    char *tracker_url = data->announce;
    
    char hostname[256];
    int port = 80;

    int n = sscanf(tracker_url, "http://%255[^:/]:%d/announce", hostname, &port);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("Error opening socket");
        return ;
    }


    server = gethostbyname(hostname);
    if(!server){
        fprintf(stderr, "Error, no such host\n");
        close(sockfd);
    }

    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting");
        close(sockfd);
        return;
    }

    snprintf(buffer, sizeof(buffer), "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", tracker_url, hostname);
    send(sockfd, buffer, strlen(buffer), 0);

    bzero(buffer, 1024);
    read(sockfd, buffer, 1023);
    printf("Tracker response: %s\n", buffer);

    close(sockfd);
}