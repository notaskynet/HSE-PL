#include "../include/server.hpp"

#include <filesystem>
#include <iostream>

#include <string>
#include <map>

#define PORT 5000

namespace fs = std::filesystem;


int main() {
    HttpServer server;
    std::map<std::string, fs::path> pages = {
        {"/", "./pages/index.html"},
        {"/404", "./pages/404.html"}
    };
    
    server.setAddress(PORT, "localhost");
    server.setPages(pages);
    
    std::cout << "Starting server at ip: 127.0.0.1:" << std::to_string(PORT) << std::endl;
    server.runServer(10);
    return 0;
}