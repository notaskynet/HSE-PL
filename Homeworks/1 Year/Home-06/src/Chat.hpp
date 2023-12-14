#include "UDPSocket.hpp"
#include <string>
#include <iostream>
#include <ctime>
#include <climits>
#define BUF_SIZE 4096

class Chat
{
    private:
        std::string name;
        UDPSocket* sock;

    public:
        Chat(int port)
        {
            std::cout << "Hello, enter your nickname: ";
            std::getline(std::cin, name);
            sock = new UDPSocket(port);
            sock->peer("255.255.255.255");
        }
        ~Chat()
        {
            std::cout << "Goodbye!" << std::endl;
        }
        void sendMsg(const std::string msg) const
        {
            std::time_t t = std::time(nullptr);
            tm *tm_local = std::localtime(&t);
            std::string msg_to_send = name + " " + std::to_string(tm_local->tm_hour) + ":" + std::to_string(tm_local->tm_min) + ": " + msg;
            if(this->sock->send(msg_to_send.c_str(), msg_to_send.size()) < 0)
                std::cerr << "Error! Message wasn't sent" << std::endl;
            else
                std::cerr << msg_to_send << std::endl;
        }
        std::string recvMsg()
        {
            char* buf = new char[BUF_SIZE];

            //std::cout  << "trying to recieve..." << std::endl;
            int res = this->sock->receive(buf, BUF_SIZE);
            //std::cout << "recived: " << res << std::endl;
            
            std::string msg(buf);
            delete[] buf;
            return (msg.rfind(name, 0) != 0 && res != -1) ? msg : "";
        }
};