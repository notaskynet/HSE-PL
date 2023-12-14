#include "../include/mainwindow.hpp"


MainWindow::MainWindow()
    : MainWindow(500, 500) {}


MainWindow::MainWindow(int width, int height)
{
    window = new QWidget;
    window->setFixedSize(width, height);

    QVBoxLayout *base_layout = new QVBoxLayout;
    
    crypto_list = new QComboBox;
    crypto_list->addItems(cripto_algos);

    hash_list = new QComboBox;
    hash_list->addItems(hash_algos);

    QHBoxLayout *layout_lists = new QHBoxLayout;
    layout_lists->addWidget(crypto_list);
    layout_lists->addWidget(hash_list);
    base_layout->addLayout(layout_lists);
    
    certificate = new QTextEdit;
    certificate->setReadOnly(true);
    
    generate_certificate_button = new QPushButton("&Generate certificate");
    generate_key_button = new QPushButton("&Generate new key");
    select_key_button = new QPushButton("&Select key");
    
    QObject::connect(
        select_key_button,
        &QPushButton::clicked,
        [=]() {
            this->selectKey();
        }
    );

    QObject::connect(
        generate_key_button,
        &QPushButton::clicked,
        [=]() { this->generateKey(); }
    );
    
    QObject::connect(
        generate_certificate_button,
        &QPushButton::clicked,
        [=]() { this->generateCertificate(); }
    );

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
        fields[name]->setPlaceholderText(name);
        base_layout->addWidget(fields[name]);
    }
    fields["Locality"]->setMaxLength(2);

    key_path = new QLineEdit;
    key_path->setPlaceholderText("Key path");
    key_path->setReadOnly(true);

    QHBoxLayout *select_key_layout = new QHBoxLayout;
    select_key_layout->addWidget(select_key_button);
    select_key_layout->addWidget(generate_key_button);
    select_key_layout->addWidget(key_path);
    base_layout->addLayout(select_key_layout);

    base_layout->addWidget(generate_certificate_button);
    base_layout->addWidget(certificate);

    window->setLayout(base_layout);
    window->setWindowTitle("Key&Certificate Generator");
}


MainWindow::~MainWindow()
{
    delete window;
}


void MainWindow::show() {
    window->show();
}


void MainWindow::selectKey()
{
    QString key_filename = QFileDialog::getOpenFileName(
        nullptr,
        "Open File",
        "/home",
        "Private key (*.key)"
    );
    key_path->setText(key_filename);
}


void MainWindow::generateKey()
{
    key_path->setText(
        QString::fromUtf8(
            openssl_tools::generatePrivateKey(
                crypto_list->currentText().toStdString(),
                "cert.key"
            ).c_str()
        )
    );
}


void MainWindow::generateCertificate()
{
    openssl_tools::CertificateInformation cert_info;

    cert_info.m_country = fields["Country"]->text().toStdString();
    cert_info.m_state = fields["State"]->text().toStdString();
    cert_info.m_locality = fields["Locality"]->text().toStdString();
    cert_info.m_organization = fields["Organization"]->text().toStdString();
    cert_info.m_unit = fields["Organizational Unit Name"]->text().toStdString();
    cert_info.m_common_name = fields["Common Name"]->text().toStdString();


    std::string certificate_text = openssl_tools::generateCertificate(
        hash_list->currentText().toStdString(),
        cert_info,
        key_path->text().toStdString(),
        "cert.crm"
    );
    certificate->setText(certificate_text.c_str());
}