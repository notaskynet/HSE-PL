#include "../include/ssocket.hpp"


char* copy(const std::string& s) {
    char *s_copy = new char[s.size()];
    for(uint32_t i = 0; i < s.size(); ++i) {
        s_copy[i] = s[i];
    }
    return s_copy;
}

// StreamSocket Methods
StreamSocket::StreamSocket() {
    m_sockfd = socket(PF_INET, SOCK_STREAM, 0);
    m_newsock = 0;
    int opt = 1;

    if(m_sockfd < 0) {
        throw std::runtime_error("socket(): failed");
    }

    int32_t setsockopt_status = setsockopt(
        m_sockfd,
        SOL_SOCKET,
        SO_REUSEADDR | SO_REUSEPORT,
        &opt,
        sizeof(opt)
    );

    if (setsockopt_status == 1) {
        throw std::runtime_error("setsockopt(): failed");
    }

    memset(m_sockaddr.sin_zero, 0, sizeof(m_sockaddr.sin_zero));
    m_sockaddr.sin_addr.s_addr = INADDR_ANY;
    m_sockaddr.sin_family = AF_INET;
}

StreamSocket::~StreamSocket() {
    ::close(m_sockfd);
    if(m_newsock >= 0) {
        ::close(m_newsock);
    }
}

void StreamSocket::setPort( const uint16_t &port ) {
    m_sockaddr.sin_port = htons(port);
    
    int16_t bind_status = bind(
        m_sockfd,
        reinterpret_cast<struct sockaddr*>( &m_sockaddr ),
        sizeof(m_sockaddr)
    );

    if(bind_status < 0) {
        throw std::runtime_error("bind(): failed");
    }
}

void StreamSocket::setAddress( const std::string &ip_addr ) {
    m_sockaddr.sin_addr.s_addr = inet_addr( ip_addr.c_str() );
}

void StreamSocket::listen( uint8_t backlog ) {
    int16_t listen_status = ::listen(
        m_sockfd,
        backlog
    );

    if(listen_status < 0) {
        throw std::runtime_error("listen(): failed");
    }
}

int16_t StreamSocket::recieve(void* buffer, int16_t buffer_size) {
    socklen_t slen = sizeof(m_sockaddr) ;
    return ::recvfrom(
        this->m_newsock,
        buffer,
        buffer_size,
        0,
        (struct sockaddr *) &m_sockaddr,
        &slen
    );
}

int16_t StreamSocket:: send(void* buffer, int16_t buffer_size) {
    return ::sendto(
        this->m_newsock,
        buffer,
        buffer_size,
        0,
        (struct sockaddr *) &m_sockaddr,
        sizeof(m_sockaddr)
    );
}


// ServerSocket Methods
ServerSocket::ServerSocket()
    : StreamSocket()
{}

ServerSocket::~ServerSocket() {
    ::close(m_sockfd);
    if(m_newsock >= 0) {
        ::close(m_newsock);
    }
}

bool ServerSocket::acceptClient() {
    socklen_t addr_len = sizeof(m_sockaddr);
    
    m_newsock = accept(
        m_sockfd,
        reinterpret_cast<struct sockaddr*>( &m_sockaddr ),
        &addr_len
    );
    return !(m_newsock < 0);
}

void ServerSocket::closeClient() {
    ::close(m_newsock);
}


// ClientSocket Methods
ClientSocket::ClientSocket()
    : StreamSocket()
{}

ClientSocket::~ClientSocket() {
    ::close(m_sockfd);
    if(m_newsock >= 0) {
        ::close(m_newsock);
    }
}

bool ClientSocket::connect( const std::string &ip_addr, uint16_t port ) {
    struct addrinfo hints, *res;

    assert( !is_connected );
    is_connected = true; 

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    getaddrinfo(
        ip_addr.c_str(),
        std::to_string(port).c_str(),
        &hints,
        &res
    );

    m_newsock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(m_sockfd < 0) {
        throw std::runtime_error("socket(): failed");
    }

    int16_t connection_status = ::connect(
        m_newsock,
        res->ai_addr,
        res->ai_addrlen
    );

    if( connection_status == 0 ) {
        is_connected = true;
    }
    return !(connection_status < 0);
}

void ClientSocket::disconnect() {
    if( is_connected ) {
        ::close(m_newsock);
    }
}
