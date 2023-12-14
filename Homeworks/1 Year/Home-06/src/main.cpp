#include "Chat.hpp"
#include <iostream>
#include <climits>
#include <sstream>
int main()
{
    Chat chat(7777);
    std::string msg = "";
    std::cin.putback('\n');
    fcntl(0, F_SETFL, O_NONBLOCK);
    while(1)
    {
        // Если есть данные: 
        // 1 - В сокете) Считать и напечатать
        // 2 - В стандартном вводе) Считать, отправить и напечатать

        
        std::string foreign_message = chat.recvMsg();
        if(foreign_message.size())
        {
            std::cout << foreign_message << std::endl;
        }
        int c = 0;
        //std::cout << "GO NEXT: "  << std::endl;

        if((c = std::cin.peek()) != std::cin.eof())
        {
            //std::cout  << "SOMETHING HERE " << c << std::endl;
            //ungetc(c, stdin);
            // while ((c = std::cin.get()) != '\n' )
            // {
            //     msg += c;
            // }
            getline(std::cin, msg);
            std::cin.clear();
            //std::cout << msg << " " << msg.size() << std::endl;
            if(msg.size())
            {
                chat.sendMsg(msg);
                msg = "";
            }
            //std::cin.putback('\n');
        }
    }
    return 0;
}