#pragma once

#include "http_handler.hpp"
#include "ssocket.hpp"

#include "coro.hpp"
#include <atomic>
#include <thread>

#include <filesystem>
#include <iostream>
#include <fstream>

#include <cstdint>
#include <cassert>

#include <string>
#include <vector>
#include <map>

namespace fs = std::filesystem;


class HttpServer {
private:
    ServerSocket *m_socket;

    std::map<std::string, fs::path> pages;
    std::atomic_bool is_running;
public:
    HttpServer();
    ~HttpServer();

    void setAddress(uint16_t port, const std::string& ip_addr);
    void setPages(const std::map<std::string, fs::path>& pages);
    void runServer(uint16_t backlog);
private:
    void handleClients();
    Task acceptClient();
    std::string recieveRequest();
    void sendPage(std::string header, fs::path page);
};
