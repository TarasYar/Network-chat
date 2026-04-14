#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
int main(){
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr<<"ERROR\n";
    }else {
        std::cout<<"Socket creterd\n";
    }

    sockaddr_in addres{};
    addres.sin_family = AF_INET;
    addres.sin_addr.s_addr = INADDR_ANY;
    addres.sin_port = htons(8080);
    bind(server_fd, (sockaddr*)&addres, sizeof(addres));

    listen(server_fd, 5);
    bool messile_long = true;
    int client = accept(server_fd, nullptr, nullptr);
    while (messile_long) {

        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        read(client, buffer, sizeof(buffer));
        std::cout<<buffer<<'\n';

        std::string send_messeg{};
        std::getline(std::cin,send_messeg);
        send(client, send_messeg.c_str() , send_messeg.size(), 0);
        if (std::string(buffer) == "exit" || send_messeg == "exit") {
            close(client);
            messile_long = false;}
    }
    close(server_fd);
}
