#include "TCPSocket.hpp"
#include <string>
#include <iostream>
#include <ctime>
#include <climits>
#include <filesystem>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;
#define BUF_SIZE 2048

std::vector<std::string> split (std::string s, std::string delimiter = " ") {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

class FTPClient
{
    private:
        std::string ip;
        TCPSocket* sock;
        TCPSocket* data_sock;
        std::ostream& output;
        fs::path ftp_path;
        fs::path lcd_path;

    public:
        bool is_active = false;
        FTPClient() : ip("127.0.0.1"), output(std::cout), ftp_path(fs::current_path()), lcd_path(fs::current_path()) { }
        FTPClient(std::ostream& out = std::cout) 
        : ip("127.0.0.1"), output(out), ftp_path(fs::current_path()), lcd_path(fs::current_path())
        {
            sock = new TCPSocket("127.0.0.1");
        }
        void open(std::string ip="127.0.0.1", int port=21)
        {
            sock = new TCPSocket(ip, port);
            output << "Connecting to server..." << std::endl;
            this->sock->connect();
            output << this->recvMsg();
            this->is_active = true;
        }
        void enterPASVmode()
        {
            std::string cmd_send = "PASV\r\n";
            this->sock->send(cmd_send.c_str(), cmd_send.size());
            std::string resp = this->recvMsg();
            output << "PASV response: " << resp;

            char buff[resp.size()+1] = {};
            strcpy(buff, resp.c_str());
            int a,b;
            char *tmp_char;
            tmp_char = strtok(buff,"(");
            tmp_char = strtok(NULL,"(");
            tmp_char = strtok(tmp_char, ")");
            int c,d,e,f;
            sscanf(tmp_char, "%d,%d,%d,%d,%d,%d",&c,&d,&e,&f,&a,&b);
            std::string o1 = std::to_string(c);
            std::string o2 = std::to_string(d);
            std::string o3 = std::to_string(e);
            std::string o4 = std::to_string(f);
            
            int port = a*256 + b;

            this->data_sock = new TCPSocket(o1+"."+o2+"."+o3+"."+o4, port);
            this->data_sock->connect();
        }
        void sendUser(std::string username)
        {
            std::string user_send = "USER " + username + "\r\n";
            this->sock->send(user_send.c_str(), user_send.size());
            output << "USER response: " << this->recvMsg();
        }
        void sendPass(std::string password)
        {
            std::string pass_send = "PASS " + password + "\r\n";
            this->sock->send(pass_send.c_str(), pass_send.size());
            output << "PASS response: " << this->recvMsg();
        }
        void signIn(std::string username, std::string password)
        {
            sendUser(username);
            sendPass(password);
            this->enterPASVmode();
        }
        ~FTPClient()
        {
           this->closeConnection();
        }
        void closeConnection()
        {
            output << "Closing connection..." << std::endl;
            this->quit();
            this->is_active = false;
        }
        void changePort(int port)
        {
            sock->port(port);
        }
        void changeDir(std::string new_path)
        {
            std::string cmdToSend = "CWD " + new_path + "\r\n";
            this->sock->send(cmdToSend.c_str(), cmdToSend.size());

            std::string resp = this->recvMsg();
            std::stringstream ss(resp);
            int code;
            ss >> code;
            if(code == 250)
            {
                if(new_path[0] == '/')
                    ftp_path = new_path;
                else if(new_path == "..")
                    ftp_path = ftp_path.parent_path();
                else 
                {
                    while (new_path.rfind("../", 0) == 0)
                    {
                        new_path = new_path.substr(3, new_path.size()-3);
                        ftp_path = ftp_path.parent_path();
                    }
                    if(ftp_path.u8string()[ftp_path.u8string().size()-1] != '/')
                        ftp_path += '/';
                    ftp_path += new_path;
                }
            }
            std::cout << "PATH: " << ftp_path << std::endl;

            output << resp;
        }
        std::string pwd()
        {
            std::string cmdToSend = "PWD\r\n";
            this->sock->send(cmdToSend.c_str(), cmdToSend.size());

            std::string resp = this->recvMsg();
            std::vector<std::string> s_vector(split(resp, "\""));
            if(s_vector.size() == 1)
                std::cerr << "Strange path";
            else
                ftp_path = s_vector[1];
            int code;

            return resp;
        }
        std::string listDir(std::string new_path)
        {
            this->enterPASVmode();
            if(!new_path.size())
                new_path = ftp_path.u8string();

            std::string cmdToSend = "NLST " + new_path + "\r\n";
            
            this->sock->send(cmdToSend.c_str(), cmdToSend.size());
            output << this->recvMsg() << this->recvMsg();
            return this->recvDataMsg();
        }
        std::string dirDir(std::string new_path)
        {
            this->enterPASVmode();
            if(!new_path.size())
                new_path = ftp_path.u8string();

            std::string cmdToSend = "LIST " + new_path + "\r\n";
            
            this->sock->send(cmdToSend.c_str(), cmdToSend.size());
            output << this->recvMsg() << this->recvMsg();
            return this->recvDataMsg();
        }

        int get(std::string filename) {
            this->enterPASVmode();
            char str[512];
            std::string file_cmd = "RETR " + filename + "\r\n";
            
            this->sock->send(file_cmd.c_str(), file_cmd.size());


            std::string resp = this->recvMsg();
            std::stringstream ss(resp);
            int code;
            ss >> code;
            if(code == 550)
                return 1;
            output << resp;

            char size[resp.size()+1] = {};
            strcpy(size, resp.c_str());

            char *tmp_size;
            tmp_size = strtok(size,"(");
            tmp_size = strtok(NULL,"(");
            tmp_size = strtok(tmp_size, ")");
            tmp_size = strtok(tmp_size, " ");

            int file_size;
            sscanf(tmp_size,"%d",&file_size);
            
            this->recvFile(filename, file_size);
            output << this->recvMsg();
            this->data_sock->close();
            return 0;
        }

        int put(std::string filename) {
            this->enterPASVmode();
            char str[512];
            std::string file_cmd = "STOR " + filename + "\r\n";
            
            this->sock->send(file_cmd.c_str(), file_cmd.size());


            std::string resp = this->recvMsg();
            if(!fs::exists(lcd_path / filename))
                return 1;
            this->sendFile(lcd_path / filename, fs::file_size(lcd_path / filename));
            this->data_sock->close();
            output << "recving msg\n";
            output << this->recvMsg();
            return 0;
        }
        void deleteFile(std::string filename)
        {
            std::string cmdToSend = "DELE " + filename + "\r\n";
            this->sock->send(cmdToSend.c_str(), cmdToSend.size());
            output << this->recvMsg();
        }
        void mkdir(std::string dir_name)
        {
            std::string cmdToSend = "MKD " + dir_name + "\r\n";
            this->sock->send(cmdToSend.c_str(), cmdToSend.size());
            output << this->recvMsg();
        }
        void rmdir(std::string dir_name)
        {
            std::string cmdToSend = "RMD " + dir_name + "\r\n";
            this->sock->send(cmdToSend.c_str(), cmdToSend.size());
            output << this->recvMsg();
        }
        void lcd(std::string path)
        {
            lcd_path = path;
        }
        void rename(std::string old_name, std::string new_name)
        {
            std::string cmdToSend = "RNFR " + old_name + "\r\n";
            this->sock->send(cmdToSend.c_str(), cmdToSend.size());
            std::string resp = this->recvMsg();
            std::stringstream ss(resp);
            int code;
            ss >> code;
            output << resp;
            if(code == 350)
            {
                cmdToSend = "RNTO " + new_name + "\r\n";
                this->sock->send(cmdToSend.c_str(), cmdToSend.size());
                output << this->recvMsg();
            }
        }
        void quit()
        {
            std::string cmdToSend = "QUIT\r\n";
            this->sock->send(cmdToSend.c_str(), cmdToSend.size());
            output << this->recvMsg();
            this->sock->close();
        }
        void printHelp()
        {
            output << "  * `help` - display this message;" << std::endl
            << "  * `ascii`, `binary` - switch transfer type"<< std::endl
            << "  * `cd` - change directory;" << std::endl
            << "  * `close` - close connection;" << std::endl
            << "  * `delete` - delete file;" << std::endl
            << "  * `dir` - get list of files in extended format;" << std::endl
            << "  * `get` - download file;" << std::endl
            << "  * `lcd` - change directory to local directory;" << std::endl
            << "  * `ls` - get list of files;" << std::endl
            << "  * `mkdir` - create directory;" << std::endl
            << "  * `open` - open connection;" << std::endl
            << "  * `put` - send file;" << std::endl
            << "  * `pwd` - get name of current directory;" << std::endl
            << "  * `rename` - rename file;" << std::endl
            << "  * `rmdir` - remove directory." << std::endl;
        }
        void sendFile(std::string filename, int file_size)
        {
            FILE *f;
            f = std::fopen(filename.c_str(), "rb");
            char buff[file_size]; 
            fread(buff,1,file_size,f);
            this->data_sock->send(buff, file_size);
            output << "file sent\n";
            fclose(f);
            output << "file closed\n";
        }
        void recvFile(std::string filename, int file_size)
        {
            FILE *f;
            f = std::fopen((lcd_path / filename).u8string().c_str(), "wb");
            int read = 0;
            do {
                    char buff[BUF_SIZE]; 
                    int readed = this->data_sock->receive(buff, BUF_SIZE);
                    fwrite(buff,1,readed,f);
                    read += readed;
                } while (read < file_size);
            fclose(f);
        }
        std::string recvDataMsg()
        {
            char* buf = new char[BUF_SIZE];

            int res = this->data_sock->receive(buf, BUF_SIZE);
            std::string msg(buf);

            while (msg.size() >= 2 && msg[msg.size()-2] != '\r' && msg[msg.size()-1] != '\n')
                msg.pop_back();
            if (msg.size() == 1)
                msg = "";
                
            delete[] buf;
            
            return msg;
        }
        std::string recvMsg()
        {
            char* buf = new char[BUF_SIZE];

            int res = this->sock->receive(buf, BUF_SIZE);
            std::string tmp(buf);
            std::string msg = tmp.substr(0, tmp.find("\n") + 1);
            memset(buf, 0, BUF_SIZE);
            delete[] buf;
            
            return msg;
        }
};