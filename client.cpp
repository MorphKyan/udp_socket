//
// Created by morph on 2022/1/10.
//

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <sys/unistd.h>
#include <arpa/inet.h>

#define DEST_PORT 8000
#define  DEST_IP_ADDRESS "127.0.0.1"

int main() {
    // socket fd
    int sock_fd;
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        exit(1);
    }

    sockaddr_in addr_serv;
    int len;
    memset(&addr_serv, 0, sizeof addr_serv);
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = inet_addr(DEST_IP_ADDRESS);
    addr_serv.sin_port = htons(DEST_PORT);
    len = sizeof addr_serv;

    int recv_num;
    int send_num;
    char recv_buf[20];
    char send_buf[20] = "who are you";
    std::cout << "client send: " << send_buf << std::endl;

    send_num = sendto(sock_fd, send_buf, strlen(send_buf), 0, reinterpret_cast<sockaddr *>(&addr_serv), len);
    if (send_num < 0) {
        perror("sendto error");
        exit(1);
    }

    recv_num = recvfrom(sock_fd, recv_buf, sizeof recv_buf, 0, reinterpret_cast<sockaddr *>(&addr_serv), &len);
    if (recv_num < 0) {
        perror("recvfrom error");
        exit(1);
    }
    recv_buf[recv_num] = '\0';
    std::cout << "client receive " << recv_num << " bytes: " << recv_buf << std::endl;

    close(sock_fd);

    return 0;
}