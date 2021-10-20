#define ADDRESS "127.0.0.1"
#define PORT 9999

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    sockaddr_in addr;
    std::string msg = "default message";

    if(argc != 1) msg = std::string(argv[1]);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
   
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, ADDRESS, &addr.sin_addr) <= 0) return 0;
   
    int status = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (status < 0) {
        std::cout << "Failed to connect." << '\n';
        return 0;
    }
    
    int bytesSend = send(sock, msg.c_str(), msg.size(), 0);
    if(bytesSend < 0) {
        std::cout << "Failed to send" << '\n';
        return 0;
    }

    char buffer[1024] = "";
    int bytesRec = recv(sock, buffer, 1023, 0);
    if(bytesRec <= 0) {
        std::cout << "Failed to receive." << '\n';
        return 0;
    }

    std::cout << buffer;

    return 0;
}