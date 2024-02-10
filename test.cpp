#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

using namespace std;

class Server 
{
    public:
        const int PORT = 8080;
        void start(){
        addSocket();
        setSocket();
        setAddress();
    }
    void addSocket(){
        if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            error("socket failed");
        }
    }
    void setSocket(){
        if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
            error("setsockopt");
        }
    }
    void setAddress(){
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);
    }
    void stop(){
        exit(EXIT_FAILURE);
    }
    void error(const char* error){
        perror(error);
        exit(EXIT_FAILURE); 
    } 
    private:
        int serverFd;
        int newSocket;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
};

class Routing: public Server {
    public:
    

    private:

    protected:
};

class HandleRequest: public Routing {
    public:

    private:

    protected:
};

class Login {
    public:

    private:

    protected:

    void checkCredentials(){

    }

};



int main() {
    Server serverObj;
    serverObj.start();
    return 0;
}