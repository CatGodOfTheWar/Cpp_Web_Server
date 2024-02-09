#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

using namespace std;

const int PORT = 8080;

void handleClient(int clientSocket) {
    char buffer[1024] = {0};
    read(clientSocket, buffer, 1024);
    cout << "Request: " << buffer << endl;

    // Simple HTTP response
    string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><body><h1>Hello, World!</h1></body></html>\r\n";
    write(clientSocket, httpResponse.c_str(), httpResponse.size());
}



int main() {
    int serverFd, newSocket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(serverFd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(serverFd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    while (true) {
        cout << "Listening on port " << PORT << "..." << endl;
        if ((newSocket = accept(serverFd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        handleClient(newSocket);
        close(newSocket);
    }

    return 0;
}
