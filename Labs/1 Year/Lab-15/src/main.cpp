
#include <filesystem>
#include <iostream>

#include "../include/checksum.hpp"
#include <vector>

#include "../include/thread_pool.hpp"
#include <atomic>
#include <mutex>

namespace fs = std::filesystem;


void printUsage() {
    std::cout << "Usage: read README.md" << std::endl;
}

std::atomic_bool is_valid{true};
 std::mutex mtx;
void checkFileIntegrity(Checksum &file_checksum) {
    std::string actual_checksum = calculateHash(
        file_checksum.filepath,
        file_checksum.algorithm
    );

    if( file_checksum.checksum != actual_checksum ) {
        mtx.lock();
        std::cerr << "Checksum mismatch for file: " << file_checksum.filepath << std::endl;
        std::cerr << "Expected: " << file_checksum.checksum << std::endl;
        std::cerr << "Actual:   " << actual_checksum << std::endl;
        mtx.unlock();
        is_valid = false;
    }
}


int main(int argc, char **argv) {
    std::vector<Checksum> files_checksum;
    ThreadPool thread_pool;
    
    if( fs::exists("Checksum.ini") ) {
        // Using 'Checksum.ini' file
        std::ifstream fin("Checksum.ini");
        files_checksum = std::move(
            parseChecksum(fin)
        );
    }
    else if( argc > 1 ) {
        // Using command-line arguments
        files_checksum = std::move(
            parseChecksum(argc, argv)
        );
    }
    else {
        // Error: Wrong usage of program
        printUsage();
        exit(EXIT_FAILURE);
    }

    for(auto &file_checksum: files_checksum) {
        thread_pool.add(
            checkFileIntegrity,
            file_checksum
        );
    }

    if(is_valid) {
        std::cout << "All files are valid" << std::endl;
    }
    return 0;
}