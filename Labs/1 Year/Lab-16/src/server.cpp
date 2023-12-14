#include "../include/server.hpp"


bool ends_with(
    const std::string &str,
    const std::string &ending
) {
    return (str.size() >= ending.size()) &&
           (str.substr(str.size() - ending.size(), str.size()) == ending);
}


HttpServer::HttpServer() {
    m_socket = new ServerSocket();
    is_running = true;
}

HttpServer::~HttpServer() {
    is_running = false;
    delete m_socket;
}


void HttpServer::setAddress(
    uint16_t port,
    const std::string& ip_addr
) {
    if(ip_addr != "localhost") {
        m_socket -> setAddress(ip_addr);
    }
    m_socket -> setPort(port);
}


void HttpServer::setPages(
    const std::map<std::string, fs::path>& pages
) {
    this->pages = pages;
}


void HttpServer::runServer(uint16_t backlog) {
    m_socket -> listen(backlog);

    std::thread infinite_loop(&HttpServer::handleClients, this);
    infinite_loop.join();
}


void HttpServer::handleClients() {
    Task task = this->acceptClient();
    std::cout << "Accepted client!" << std::endl;
    while(is_running) {
        if(m_socket->acceptClient())
            task.resume();
    }
}


Task HttpServer::acceptClient() {
    while (is_running) {
        std::string request = recieveRequest();
        auto handler = HttpHandler(request);

        if( pages.find(handler.getPath()) != pages.end() ) {
            fs::path file = pages[ handler.getPath() ];

            handler.setHeader("Server", "CHTTP");
            handler.setHeader(
                "Content-Length",
                std::to_string( fs::file_size(file) )
            );
            if( ends_with(file.string(), ".html") ||
                ends_with(file.string(), ".htm") ) {
                handler.setHeader("Content-Type", "text/html; charset=utf-8");
            }
            else {
                handler.setHeader("Content-Type", "text/plain");
            }

            std::string responce = handler.commitResponce("200 OK");
            std::cout << responce << std::endl;

            if(handler.getMethod() == "GET") {
                sendPage( responce, file );
            }
            else {
                m_socket->send(
                    const_cast<char*>(responce.c_str()),
                    responce.size()
                );
            }
        }
        else {
            fs::path error_page = pages[ "/404" ];

            handler.setHeader("Server", "CHTTP");
            handler.setHeader(
                "Content-Length",
                std::to_string( fs::file_size(error_page) )
            );

            handler.setHeader(
                "Content-Type",
                "text/html; charset=utf-8"
            );

            std::string responce = handler.commitResponce("404 Not found");
            std::cout << responce << std::endl;

            if(handler.getMethod() == "GET") {
                sendPage(responce, error_page);
            }
            else {
                m_socket->send(
                    const_cast<char*>(responce.c_str()),
                    responce.size()
                );
            }
        }
        co_await std::suspend_always();
    }
}


std::string HttpServer::recieveRequest() {
    #define BUFFER_SIZE 1024

    char* buffer = new char[BUFFER_SIZE];
    std::string tmp, msg;

    m_socket->recieve(buffer, BUFFER_SIZE);
    tmp = std::string(buffer);
    msg = tmp.substr(0, tmp.find("\r\n\r\n") + 1);
    delete[] buffer;
    
    return msg;
}


void HttpServer::sendPage(std::string header, fs::path page) {
    #define BUFFER_SIZE 1024
    
    char* buffer = new char[BUFFER_SIZE];
    std::string msg;
    
    std::ifstream fin(page.string(), std::ifstream::binary);
    fin.read(buffer, BUFFER_SIZE);

    msg = header + ": " + std::string(buffer);
    m_socket->send(
        const_cast<char*>( msg.c_str() ),
        msg.size()
    );

    while(!fin.eof()) {
        fin.read(buffer, BUFFER_SIZE);
        m_socket->send(buffer, BUFFER_SIZE);
    }
    fin.close();
    delete[] buffer;
}
