#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <sys/unistd.h>

#define SERV_PORT 8000

int main() {
    // socket fd
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        exit(1);
    }

    // socket setting
    sockaddr_in addr_serv;
    int len;
    memset(&addr_serv, 0, sizeof(sockaddr_in));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_port = htons(SERV_PORT);
    // receive from any address
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    len = sizeof addr_serv;

    // bind socket
    if (bind(sock_fd, reinterpret_cast<sockaddr *>(&addr_serv), sizeof addr_serv)) {
        perror("bind error");
        exit(1);
    }

    int recv_num;
    int send_num;
    char recv_buf[20];
    char send_buf[20] = "i am server";
    sockaddr_in addr_client;

    while (true) {
        std::cout << "server wait:" << std::endl;
        recv_num = recvfrom(sock_fd, recv_buf, sizeof recv_buf, 0, reinterpret_cast<sockaddr *>(&addr_client), &len);
        if (recv_num < 0) {
            perror("recvfrom error");
            exit(1);
        }

        recv_buf[recv_num] = '\0';
        std::cout << "server receive " << recv_num << " bytes: " << recv_buf << std::endl;
        send_num = sendto(sock_fd, send_buf, recv_num, 0, reinterpret_cast<sockaddr *>(&addr_client), sizeof send_buf);

        if (send_num < 0) {
            perror("sendto error");
            exit(1);
        }
    }

    close(sock_fd);

    return 0;
}
