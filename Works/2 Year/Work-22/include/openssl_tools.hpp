#pragma once

#include <sstream>
#include <fstream>
#include <string>


namespace openssl_tools
{
    struct CertificateInformation;

    std::string StringifyCI(
        const CertificateInformation &cert_info
    );

    std::string generateCertificate(
        const std::string &hash_algorithm,
        const CertificateInformation &cert_info,
        const std::string &key_path,
        const std::string &cert_path
    );

    std::string generatePrivateKey(
        const std::string &crypto_algorithm,
        const std::string &key_path
    );
};

struct openssl_tools::CertificateInformation
{
    std::string m_country = "";
    std::string m_state = "";
    std::string m_locality = "";
    std::string m_organization = "";
    std::string m_unit = "";
    std::string m_common_name = "";
};
