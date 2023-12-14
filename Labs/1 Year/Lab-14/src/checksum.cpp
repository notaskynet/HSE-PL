#include "../include/checksum.hpp"
#include "../include/functools.hpp"


std::string calculateHash(
    fs::path file_path,
    Checksum::Algorithm algorithm
) {
    std::string hash;
    std::string cmd;

    switch(algorithm) {
        case Checksum::Algorithm::CRC32: {
            cmd = "cksum ";
            break;
        }
        case Checksum::Algorithm::SHA256: {
            cmd = "sha256sum ";
            break;
        }
        case Checksum::Algorithm::MD5: {
            cmd = "md5sum ";
            break;
        }
        default: {
            throw std::invalid_argument(file_path.string() + ": Invalid algorithm");
        }
    }
    
    cmd += file_path.string();
    hash = exec(cmd);
    hash = hash.substr(0, hash.find(" "));
    if(algorithm == Checksum::Algorithm::CRC32) {
        hash = hex(hash);
    }
    return "0x" + to_upper(hash);
}


Checksum::Algorithm getAlgorithmFromLine(
    const std::string &algorithm_type
) {
    Checksum::Algorithm algorithm = Checksum::Algorithm::None;
    
    if (algorithm_type == "CRC32" || algorithm_type == "crc32") {
        algorithm = Checksum::Algorithm::CRC32;
    }
    else if (algorithm_type == "MD5" || algorithm_type == "md5") {
        algorithm = Checksum::Algorithm::MD5;
    }
    else if (algorithm_type == "SHA256" || algorithm_type == "sha256"){
        algorithm = Checksum::Algorithm::SHA256;
    }
    else {
        throw std::invalid_argument("Invalid type of algorithm");
    }
    return algorithm;
}


std::vector<Checksum> parseChecksum(
    std::ifstream &in
) {
    std::vector<Checksum> files_checksum;
    Checksum::Algorithm cur_algorithm = Checksum::Algorithm::None;
    std::string line;

    while(std::getline(in, line)) {
        if ( ';' == line[0] ) {
            // Comment
            continue;
        }
        else if ( '[' == line[0] ) {
            // Algorithm
            cur_algorithm = getAlgorithmFromLine(
                line.substr(1, line.find("]") - 1)
            );
        }
        else {
            // Filename & Checksum
            if( cur_algorithm  == Checksum::Algorithm::None ) {
                throw std::invalid_argument("Failed to parse Checksum.ini: Wrong args!");
            }

            std::string filename = line.substr(0, line.find("="));
            std::string checksum = "0x" + to_upper(
                line.substr( line.find("=") + 3)
            );
            tream(checksum);

            files_checksum.emplace_back(
                fs::path(filename),
                checksum,
                cur_algorithm
            );
            cur_algorithm  = Checksum::Algorithm::None;
        }
    }
    return files_checksum;
}

std::vector<Checksum> parseChecksum(
    int argc,
    char **argv
) {
    Checksum::Algorithm cur_algorithm = Checksum::Algorithm::None;
    std::vector<Checksum> files_checksum;

    for(int i = 1; i < argc; ++i) {
        if(strcmp(argv[i], "-a") == 0) {
            cur_algorithm = getAlgorithmFromLine(argv[++i]);
        }
        else {
            if(cur_algorithm == Checksum::Algorithm::None) {
                throw std::invalid_argument("Inavalid algorithm");
                exit(EXIT_FAILURE);
            }

            std::string filename(argv[i]);
            std::string hash(argv[++i]);

            files_checksum.emplace_back(
                filename,
                hash,
                cur_algorithm
            );
        }
    }
    return files_checksum;
}

