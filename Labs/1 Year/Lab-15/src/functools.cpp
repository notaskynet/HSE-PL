#include "../include/functools.hpp"

namespace { std::mutex exec_mtx; };

std::string exec(const std::string &cmd) {
    std::lock_guard<std::mutex> exec_lg(exec_mtx);
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    
    if (!pipe) {
        throw std::runtime_error("exec(): popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string hex(const std::string &num) {
    std::stringstream ss;
    ss << std::hex << stoi(num);
    return ss.str();
}

std::string to_upper(std::string str) {
    for (auto &c: str) {
        c = toupper(c);
    }
    return str;
}

void tream(std::string &s) {
    std::stringstream ss(s);
    ss >> s;
}