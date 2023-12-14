#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

class UDPSocket
{
    protected:
        int sockfd;
        struct sockaddr_in recvaddr;
        struct sockaddr_in sendaddr;  
    public:
        UDPSocket()
        {
            int broadcast = 1;

            sockfd = socket(AF_INET, SOCK_DGRAM, 0);
            if(sockfd < 0){
                printf("Error while creating socket\n");
            }

            if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
            sizeof(broadcast))< 0) {
                perror("setsockopt (SO_BROADCAST)");
                exit(1);
            }

            memset(recvaddr.sin_zero, 0, sizeof(recvaddr.sin_zero));
            recvaddr.sin_family = AF_INET;
            recvaddr.sin_addr.s_addr = INADDR_ANY;
            
            memset(sendaddr.sin_zero, 0, sizeof(sendaddr.sin_zero));
            sendaddr.sin_family = AF_INET;
            sendaddr.sin_addr.s_addr = INADDR_BROADCAST;

            this->bind();
            fcntl(sockfd, F_SETFL, SOCK_NONBLOCK);
        };
        UDPSocket(int port)
        {
            int broadcast = 1;

            sockfd = socket(AF_INET, SOCK_DGRAM, 0);
            if(sockfd < 0){
                printf("Error while creating socket\n");
                exit(1);
            }
            
            if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
            sizeof(broadcast))< 0) {
                perror("setsockopt (SO_BROADCAST)");
                exit(1);
            }

            memset(recvaddr.sin_zero, 0, sizeof(recvaddr.sin_zero));
            recvaddr.sin_family = AF_INET;
            recvaddr.sin_addr.s_addr = INADDR_ANY;
            
            memset(sendaddr.sin_zero, 0, sizeof(sendaddr.sin_zero));
            sendaddr.sin_family = AF_INET;
            sendaddr.sin_addr.s_addr = INADDR_BROADCAST;

            this->port(port);
            this->bind();
            fcntl(sockfd, F_SETFL, SOCK_NONBLOCK);
        };
        ~UDPSocket();

        void bind()
        {
            if(::bind(sockfd, (struct sockaddr*)&recvaddr, sizeof(recvaddr)) < 0)
            {
                perror("Error while binding socket");
                exit(1);
            }
        }
        void port(int port)
        {
            sendaddr.sin_port = htons(port);
            recvaddr.sin_port = htons(port);
        };
        void peer(const char* address)
        {
            this->recvaddr.sin_addr.s_addr  = inet_addr(address);
            this->sendaddr.sin_addr.s_addr  = inet_addr(address);
        }
        sockaddr_in peer()
        {
            return this->recvaddr;
        }
        int receive(char *buf, int count)
        {
            //this->bind(recvaddr);
            socklen_t slen = sizeof(sendaddr) ;
            return recvfrom(sockfd, buf, count, 0, (struct sockaddr *) &sendaddr, &slen);
        }
        int send(const char *buf, int count)
        {
            //this->bind(sendaddr);
            return sendto(sockfd, buf, count+1, 0, (struct sockaddr *) &sendaddr, sizeof(sendaddr));
        }
};
