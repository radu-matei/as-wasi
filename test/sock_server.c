#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

void process(int sock)
{
    int n;
    char buf[256];
    bzero(buf, 256);
    n = read(sock, buf, 255);

    if (n < 0)
    {
        perror("ERROR: cannot read from socket");
        exit(1);
    }

    printf("message received from client: %s\n", buf);
    // sleeping for 5 seconds to simulate work being done...
    sleep(5);
    n = write(sock, buf, n);

    if (n < 0)
    {
        perror("ERROR: cannot write to socket");
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n, pid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = 3333;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR: cannot bind to sockfd");
        exit(1);
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while (1)
    {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

        if (newsockfd < 0)
        {
            perror("ERROR: cannot accept");
            exit(1);
        }

        pid = fork();
        if (pid < 0)
        {
            perror("ERROR: cannot fork");
            exit(1);
        }

        if (pid == 0)
        {
            close(sockfd);
            process(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
        }
    }
}
