#pragma once

#include <iostream>
#include <sstream>

#include <utility>
#include <string>
#include <vector>
#include <map>


class HttpHandler {
private:
    using key_value = std::pair<std::string, std::string>;

    struct HttpProperties {
        std::string method;
        std::string path;
        std::string version;

        std::vector<std::pair<std::string, std::string>> headers;
    };
    HttpProperties m_request, m_responce;

public:
    HttpHandler(const std::string &payload);
    ~HttpHandler() = default;

    std::string getMethod();
    std::string getPath();
    std::string getVersion();
    std::string getHeader(const std::string& key);
    
    void setPath( const std::string &path );
    void setMethod( const std::string &method );
    void setHeader( const std::string &key, const std::string &value );

    std::string commitResponce( const std::string &status ); 

    static std::vector<std::string> split( std::string str, std::string delimiter );
};