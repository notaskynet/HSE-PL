#include "FTPClient.hpp"
#include <regex>
#include <iostream>

bool ValidateIp(std::string IP)
{
    std::regex  ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
    return regex_match(IP, ipv4);
}

int main()
{
    std::cout << "Welcome! type help to get list of commands" << std::endl;
    bool keepConnection = true;
    FTPClient ftp(std::cout);
    std::string cmd = "a";
    while(cmd != "exit")
    {
        std::string raw_str;
        std::cout << "CFTP >";
        std::getline(std::cin, raw_str);
        std::vector<std::string> splited_cmd = split(raw_str);
        
        cmd = splited_cmd[0];
        if(!ftp.is_active && cmd == "open")
        {
            std::string s_user, s_password, s_ip;

            std::cout << "Enter ip: ";
            std::cin >> s_ip;
            if(!ValidateIp(s_ip))
            {
                std::cerr << "Invalid IP" << std::endl;
                return 1;
            }
            std::cout << "Enter username: ";
            std::cin.ignore();
            std::cin >> std::skipws;
            std::getline(std::cin, s_user);

            ftp.open(s_ip, 21);
            
            ftp.sendUser(s_user);
            std::cout << "Enter password: ";
            std::cin >> std::skipws;
            std::getline(std::cin, s_password);
            
            ftp.sendPass(s_password);
            ftp.pwd();

        }
        else if(ftp.is_active)
        {
            if(cmd == "help")
                ftp.printHelp();
            else if(cmd == "pwd")
                std::cout << ftp.pwd();
            else if(cmd == "ls")
            {
                std::string path = "";

                if(splited_cmd.size() >= 2)
                    path = splited_cmd[1];
                
                std::cout << ftp.listDir(path);
            }
            else if(cmd == "dir")
            {
                std::string path = "";

                if(splited_cmd.size() >= 2)
                    path = splited_cmd[1];
                
                std::cout << ftp.dirDir(path);
            }
            else if(cmd == "get")
            {
                if(splited_cmd.size() < 2)
                {
                    std::cout << "Invalid parameters. Enter filename" << std::endl;
                    continue;
                }
                std::string file = splited_cmd[1];
                if(ftp.get(file))
                    std::cout << "File doesn't exist";
            }
            else if(cmd == "put")
            {
                if(splited_cmd.size() < 2)
                {
                    std::cout << "Invalid parameters. Enter filename" << std::endl;
                    continue;
                }
                std::string file = splited_cmd[1];
                if(ftp.put(file))
                    std::cout << "File doesn't exist";
            }
            else if(cmd == "delete")
            {
                if(splited_cmd.size() < 2)
                {
                    std::cout << "Invalid parameters. Enter filename" << std::endl;
                    continue;
                }
                std::string file = splited_cmd[1];
                ftp.deleteFile(file);
            }
            else if(cmd == "rename")
            {
                if(splited_cmd.size() != 3)
                {
                    std::cout << "Invalid parameters. Check old and new filenames" << std::endl;
                    continue;
                }
                ftp.rename(splited_cmd[1], splited_cmd[2]);
            }
            else if(cmd == "cd")
            {
                if(splited_cmd.size() < 2)
                {
                    std::cout << "Invalid parameters. Enter path" << std::endl;
                    continue;
                }
                std::string new_path = splited_cmd[1];
                ftp.changeDir(new_path);
            }
            else if(cmd == "lcd")
            {
                if(splited_cmd.size() < 2)
                {
                    std::cout << "Invalid parameters. Enter path" << std::endl;
                    continue;
                }
                std::string new_path = splited_cmd[1];
                ftp.lcd(new_path);
            }
            else if(cmd == "mkdir")
            {
                if(splited_cmd.size() < 2)
                {
                    std::cout << "Invalid parameters. Enter directory name" << std::endl;
                    continue;
                }
                std::string new_path = splited_cmd[1];
                ftp.mkdir(new_path);
            }
            else if(cmd == "rmdir")
            {
                if(splited_cmd.size() < 2)
                {
                    std::cout << "Invalid parameters. Enter directory name" << std::endl;
                    continue;
                }
                std::string new_path = splited_cmd[1];
                ftp.rmdir(new_path);
            }
            else if(cmd == "ascii" || cmd == "binary")
            {
                std::cout << "Switched to " + cmd + " mode" << std::endl;
            }
            else if (cmd == "close")
                ftp.closeConnection();
            else
                std::cout << "Invalid command. Type `help` to get list of commands" << std::endl;
        }
        else
        {
            std::cout << "Firstly enter command: `open`" << std::endl;
        }
    }
    return 0;
}