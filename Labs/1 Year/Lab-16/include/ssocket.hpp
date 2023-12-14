#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#include <unistd.h>
#include <stdexcept>

#include <cassert>
#include <cstdint>
#include <cstring>
#include <string>


class StreamSocket {
protected:
    struct sockaddr_in m_sockaddr;
    int16_t m_sockfd, m_newsock;

public:
    StreamSocket();
    ~StreamSocket();

    void setPort( const uint16_t &port );
    void setAddress( const std::string &ip_addr );
    
    void    listen( uint8_t backlog );
    int16_t recieve( void* buffer, int16_t buffer_size );
    int16_t send( void* buffer, int16_t buffer_size );
};


class ServerSocket: public StreamSocket {
public:
    ServerSocket();
    ~ServerSocket();

    bool acceptClient();
    void closeClient();
};


class ClientSocket: public StreamSocket {
private:
    bool is_connected = false;
public:
    ClientSocket();
    ~ClientSocket();

    bool connect( const std::string &ip_addr, uint16_t port );
    void disconnect();
};
