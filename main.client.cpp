#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "Protocol/Requests/LoginRequest.cpp"
#include "Protocol/Responses/LoginResponse.cpp"

#include "Protocol/Requests/RegistrationRequest.cpp"
#include <iostream>
using namespace std;
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    int nSocket;
    int nConnect;
    int nBytes;
    struct sockaddr_in stServerAddr;
    struct hostent *lpstServerEnt;
    char cbBuf[BUF_SIZE];

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s server_name port_number\n", argv[0]);
        exit(1);
    }

    /* look up server's IP address */
    lpstServerEnt = gethostbyname(argv[1]);
    if (!lpstServerEnt)
    {
        fprintf(stderr, "%s: Can't get the server's IP address.\n", argv[0]);
        exit(1);
    }

    /* create a socket */
    nSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (nSocket < 0)
    {
        fprintf(stderr, "%s: Can't create a socket.\n", argv[0]);
        exit(1);
    }

    /* server info */
    memset(&stServerAddr, 0, sizeof(struct sockaddr));
    stServerAddr.sin_family = AF_INET;
    memcpy(&stServerAddr.sin_addr.s_addr, lpstServerEnt->h_addr, lpstServerEnt->h_length);
    stServerAddr.sin_port = htons(atoi(argv[2]));

    /* connect to the server */
    nConnect = connect(nSocket, (struct sockaddr *)&stServerAddr, sizeof(struct sockaddr));
    if (nConnect < 0)
    {
        fprintf(stderr, "%s: Can't connect to the server (%s:%i).\n", argv[0], argv[1], atoi(argv[2]));
        exit(1);
    }

    /* connection is now established; read from socket */
    LoginRequest request("meviu55k", "!P@ssw0rda");
    string str = request.ToString();
    printf("%s: [sending string to %s]\n%s\n", argv[0], inet_ntoa((struct in_addr)stServerAddr.sin_addr), str.c_str());

    int size = str.size();
    write(nSocket, &size, sizeof(size));
    write(nSocket, str.c_str(), size);

    read(nSocket, &size, sizeof(size));
    char buffer[size];
    read(nSocket, buffer, sizeof(buffer));

    cout << buffer << endl;

    close(nSocket);
    return 0;
}