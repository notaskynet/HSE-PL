#include "key_generator.h"


KeyGenerator::KeyGenerator()
{
    textEdit = new QTextEdit;
    textEdit -> setReadOnly(true);
    textEdit -> setText("*Push a button to generate a key*");
}

KeyGenerator::~KeyGenerator()
{
    delete textEdit;
}

void KeyGenerator::updateKey()
{
    std::stringstream ss;
    if(std::system("openssl genpkey -algorithm gost2012_256 -pkeyopt paramset:TCB -out ca.key")) // Fail!
    {
        ss << "*Failed to generate a key*";
    }
    else
    {
        std::ifstream key_file("ca.key");
        if(key_file.is_open())
        {
            for(std::string line; std::getline(key_file, line); )
                ss << line << std::endl;
        }
        else
        {
            ss << "Failed to open key file";
        }
        key_file.close();
    }
    textEdit->setText(ss.str().c_str());
    std::remove("ca.key");
}
