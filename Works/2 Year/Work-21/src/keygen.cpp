#include "../include/keygen.h"
#include <fstream>

// Utilities


struct KeyGenerator::UserInformation
{
    std::string m_country = "";
    std::string m_state = "";
    std::string m_locality = "";
    std::string m_organization = "";
    std::string m_unit = "";
    std::string m_common_name = "";

    UserInformation() = default;

    UserInformation(
        std::string country,
        std::string state,
        std::string locality,
        std::string organization,
        std::string unit,
        std::string common_name 
    ) {
        m_country = country;
        m_state = state;
        m_locality = locality;
        m_organization = organization;
        m_unit = unit;
        m_common_name = common_name;
    }

    std::string toStdString() const
    {
        return  "/C="  + m_country +
                "/ST=" + m_state +
                "/L="  + m_locality +
                "/O="  + m_organization +
                "/OU=" + m_unit +
                "/CN=" + m_common_name;
    }
};


struct KeyGenerator::CommandOptions
{
    std::string m_hash_algorithm = "";
    std::string m_encrypt_algorithm = "";
    std::string m_certname = "";
    std::string m_keyname = "";
    UserInformation m_user_info;

    CommandOptions(
            std::string hash_algorithm,
            std::string encrypt_algorithm,
            std::string certname,
            std::string keyname,
            UserInformation user_info
    ) {
        m_hash_algorithm = hash_algorithm;
        m_encrypt_algorithm = encrypt_algorithm;
        m_certname = certname;
        m_keyname = keyname;
        m_user_info = user_info;
    }
};


// Methods of class "KeyGenerator"

std::string KeyGenerator::generateCommand(
    const CommandOptions &cmd_options
) {
    return  "openssl req -x509 -" + cmd_options.m_hash_algorithm + 
            " -newkey " + cmd_options.m_encrypt_algorithm +
            " -pkeyopt paramset:A -nodes -keyout " + cmd_options.m_keyname +
            " -out " + cmd_options.m_certname +
            " -subj \"" + cmd_options.m_user_info.toStdString() + "\"";
}


std::string KeyGenerator::generateKeyCertificate(
    const CommandOptions &cmd_options
) {
    std::ofstream outfile;
    std::string cmd = generateCommand(cmd_options);
    
    outfile.open("logs.txt", std::ios_base::app);
    outfile << cmd << std::endl;

    if( std::system(cmd.c_str()) != 0 )
    {
        return "Failed to generate cert";
    }
    else
    {
        std::ifstream cert_file(cmd_options.m_certname);
        if( !cert_file.is_open() )
        {
            return "Error openning certificate";
        }
        else
        {
            std::stringstream cert_output;
            std::string buffer;

            while (cert_file >> buffer)
            {
                cert_output << buffer << std::endl;
            }
            cert_file.close();
            return cert_output.str();
        }
    }
}

// Main methods


KeyGenerator::KeyGenerator()
    : KeyGenerator(500, 500) {}


KeyGenerator::KeyGenerator(int width, int height)
{
    window = new QWidget;
    text_edit = new QTextEdit;
    generate_button = new QPushButton("&Generate certificate");
    crypto_list = new QComboBox;
    hash_list = new QComboBox;

    crypto_list->addItems(algorithms);
    hash_list->addItems(hashes);
    window->setFixedSize(width, height);
    text_edit->setReadOnly(true);

    QObject::connect(
        generate_button,
        &QPushButton::clicked,
        [=]() {
            this->showCertificate();
        }
    );

    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *layout_lists = new QHBoxLayout;

    layout_lists->addWidget(crypto_list);
    layout_lists->addWidget(hash_list);
    layout->addLayout(layout_lists);

    QStringList field_names = {
        "Country",
        "State",
        "Locality",
        "Organization",
        "Organizational Unit Name",
        "Common Name"    
    };

    for (QString name : field_names)
    {
        fields[name] = new QLineEdit;
        QLabel *label = new QLabel;
        QHBoxLayout *field_layout = new QHBoxLayout;
        label->setText(name);
        label->setBuddy(fields[name]);
        field_layout->addWidget(label);
        field_layout->addWidget(fields[name]);
        layout->addLayout(field_layout);
    }

    fields["Locality"]->setMaxLength(2);

    layout->addLayout(layout_lists);
    layout->addWidget(text_edit);
    layout->addWidget(generate_button);

    window->setLayout(layout);
    window->setWindowTitle("Key Generator GOST");
    window->show();
}


KeyGenerator::~KeyGenerator()
{
    delete window;
}


void KeyGenerator::showCertificate()
{
    UserInformation user_info(
        fields["Country"]->text().toStdString(),
        fields["State"]->text().toStdString(),
        fields["Locality"]->text().toStdString(),
        fields["Organization"]->text().toStdString(),
        fields["Organizational Unit Name"]->text().toStdString(),
        fields["Common Name"]->text().toStdString()
    );

   CommandOptions cmd_options(
        hash_list->currentText().toStdString(),
        crypto_list->currentText().toStdString(),
        "certificate.crt",
        "privateKey.key",
        user_info
   );  

    std::string certificate = generateKeyCertificate(cmd_options);
    text_edit->setText(certificate.c_str());
}
