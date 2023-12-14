#include "../include/http_handler.hpp"


HttpHandler::HttpHandler(const std::string &payload) {
    std::stringstream ss(payload);
    std::string line;

    std::vector<std::string> args = HttpHandler::split(payload, " ");
    m_request.method  = args[0];
    m_request.path    = args[1];
    m_request.version = args[2];

    if(m_request.method != "GET" && m_request.method != "HEAD") {
        std::cerr << "Invalid method: " << m_request.method << std::endl;
        exit(EXIT_FAILURE);
    }
    if( !m_request.version.starts_with("HTTP") ) {
        std::cerr << "Invalid format of request: "
                  << m_request.version
                  << std::endl;
    }

    #define VALUE 1
    #define KEY   0

    while( getline(ss, line) ) {
        int delimiter_pos = line.find(':');
        m_request.headers.push_back(
            std::make_pair(
                line.substr(0, delimiter_pos),
                line.substr(delimiter_pos + 2, line.size() - delimiter_pos - 1)
            )
        );
    }
}

std::string HttpHandler::getMethod() {
    return m_request.method;
}

std::string HttpHandler::getPath() {
    return m_request.path;

}

std::string HttpHandler::getVersion() {
    return m_request.version;
}

std::string HttpHandler::getHeader(const std::string& key) {
    for(auto& header: m_request.headers) {
        if(header.first == key)
            return header.second;
    }
    return std::string();
}

void HttpHandler::setPath(
    const std::string &path
) {
    m_responce.path = path;
}

void HttpHandler::setMethod(
    const std::string &method
) {
    m_responce.method = method;
}
    
void HttpHandler::setHeader(
    const std::string &key,
    const std::string &value
) {
    m_responce.headers.emplace_back(key, value);
}


std::string HttpHandler::commitResponce(const std::string &status) {
    std::string responce;

    responce += m_request.version;
    responce += " " + status + "\r\n";
    for(const auto& header: m_responce.headers) {
        responce += (header.first + ": " + header.second + "\r\n");
    }
    responce += "\r\n";
    return responce;
}


std::vector<std::string> HttpHandler::split(
    std::string str,
    std::string delimiter
) {
    std::vector<std::string> splited_string;
    int start, end = -1 * delimiter.size();

    do {
        start = end + delimiter.size();
        end = str.find(delimiter, start);
        splited_string.push_back(
            str.substr(start, end - start)
        );
    } while(end != -1);
    
    return splited_string;
}