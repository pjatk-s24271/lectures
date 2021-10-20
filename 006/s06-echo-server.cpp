#define MAX_CON 2
#define PORT 9999

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <thread>

int con = 0;

void handleConnection(int connection)
{
    while(true) 
    {
        char buffer[1024] = "";

        int bytesRec = recv(connection, buffer, 1023, 0);
        if(bytesRec <= 0) break;
        
        int bytesSend = send(connection, std::string(buffer).c_str(), std::string(buffer).size(), 0);
        if(bytesSend < 0) break;
    }

    close(connection);
    con--;
}

void handleSocket(int* sockfd) {
    while(true)
    {
        int connection = accept(*sockfd, NULL, NULL);
        if (connection < 0) continue;

        if(con < MAX_CON) {
            con++;
            std::thread t(handleConnection, connection);
            t.detach();
        } else {
            std::string msg = "To many connections!\n";
            int bytesSend = send(connection, msg.c_str(), msg.size(), 0);
            if(bytesSend < 0) continue;

            close(connection);
        }
    }
}

int main() {
    sockaddr_in addr;

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(9999);

    int flag = 1;  
    if (-1 == setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag))) {  
        std::cout << "Failed to enable SO_REUSEADDR." << '\n';
        return 0;
    }

    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cout << "Failed to bind to port 9999." << '\n';
        return 0;
    }

    if (listen(sock, MAX_CON) < 0) {
        std::cout << "Failed to listen on socket." << '\n';
        return 0;
    }

    std::thread t(handleSocket, &sock);
    t.join();

    close(sock);
}