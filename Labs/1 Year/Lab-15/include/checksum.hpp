#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>

#include <vector>
#include <cstring>
#include <string>

#include <mutex>

namespace fs = std::filesystem;


struct Checksum {
    enum class Algorithm { None, CRC32, MD5, SHA256 };
    fs::path    filepath;
    std::string checksum;
    Algorithm   algorithm = Algorithm::None;

    Checksum(fs::path filepath, std::string checksum, Algorithm algorithm)
        : filepath(filepath), checksum(checksum), algorithm(algorithm) {}
};

std::string calculateHash(
    fs::path file_path,
    Checksum::Algorithm algorithm
);

std::vector<Checksum> parseChecksum(
    std::ifstream &in
);

std::vector<Checksum> parseChecksum(
    int argc,
    char **argv
);