#include "../include/openssl_tools.hpp"

std::string openssl_tools::StringifyCI(
    const openssl_tools::CertificateInformation &cert_info
) {
    return  "/C="  + cert_info.m_country +
            "/ST=" + cert_info.m_state +
            "/L="  + cert_info.m_locality +
            "/O="  + cert_info.m_organization +
            "/OU=" + cert_info.m_unit +
            "/CN=" + cert_info.m_common_name;
}



std::string openssl_tools::generatePrivateKey(
    const std::string &crypto_algorithm,
    const std::string &key_path
) {
    std::string cmd = "openssl genpkey -algorithm " + crypto_algorithm +
                      " -pkeyopt paramset:A -out " + key_path;
    if( std::system(cmd.c_str()) != 0 )
    {
        return "Fault while generating private key!";
    }
    return key_path;
}


std::string openssl_tools::generateCertificate(
    const std::string &hash_algorithm,
    const CertificateInformation &cert_info,
    const std::string &key_path,
    const std::string &cert_name
) {
    std::string cmd = "openssl req -x509 -" + hash_algorithm +
                      " -new -key " + key_path +
                      " -out " + cert_name +
                      " -subj \"" + StringifyCI(cert_info) + "\"";

    if( std::system(cmd.c_str()) != 0 )
    {
        return "Fault while generating certificate!";
    }

    std::ifstream cert_file(cert_name);
    
    if( !cert_file.is_open() )
    {
        return "Can`t open certificate file!";
    }

    std::stringstream cert_data;
    std::string buffer;
    while( cert_file.good() ) {
        getline(cert_file, buffer);
        cert_data << buffer << std::endl;
    }

    return cert_data.str();
}
