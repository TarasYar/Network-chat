#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
int main(){
    int client_server = socket(AF_INET, SOCK_STREAM, 0);
    if (client_server < 0) {
        std::cerr<<"ERROR\n";
    }else {
        std::cout<<"Client server created\n";
    }

    sockaddr_in addres{};
    addres.sin_family = AF_INET;
    addres.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &addres.sin_addr);

    connect(client_server, (sockaddr*)&addres, sizeof(addres));
    std::cout<<"Conected to server\n";
    bool messile_long = true;
    while (messile_long) {
        std::string messege_to_server{};
        std::getline(std::cin,messege_to_server);
        send(client_server,messege_to_server.c_str(), messege_to_server.size(), 0);

        char get_message[1024];
        memset(get_message, 0, sizeof(get_message));
        read(client_server, get_message, sizeof(get_message));
        std::cout<<get_message<<'\n';
        if (std::string(get_message) == "exit" || messege_to_server == "exit") {
            close(client_server);
            messile_long = false;
        }
    }
    close(client_server);
}
