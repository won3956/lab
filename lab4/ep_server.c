#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define PORT_NUM 3600
#define EPOLL_SIZE 20
#define MAXLINE 1024

struct udata {
    int fd;
    char name[80];
};

int user_fds[1024];

void send_msg(struct epoll_event ev, char *msg);

int main(int argc, char **argv) {
    struct sockaddr_in addr, clientaddr;
    struct epoll_event ev, *events;
    struct udata *user_data;
    int listenfd;
    int clientfd;
    int i;
    socklen_t addrlen, clilen;
    int readn;
    int eventn;
    int epollfd;
    char buf[MAXLINE];

    events = (struct epoll_event *)malloc(sizeof(struct epoll_event) * EPOLL_SIZE);
    if ((epollfd = epoll_create(100)) == -1) {
        perror("epoll_create error");
        return 1;
    }

    addrlen = sizeof(addr);
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT_NUM);
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // 수정: `htons` -> `htonl`

    if (bind(listenfd, (struct sockaddr *)&addr, addrlen) == -1) {
        perror("bind error");
        return 1;
    }

    listen(listenfd, 5);

    ev.events = EPOLLIN;
    ev.data.fd = listenfd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev);

    memset(user_fds, -1, sizeof(int) * 1024);

    while (1) {
        eventn = epoll_wait(epollfd, events, EPOLL_SIZE, -1);
        if (eventn == -1) {
            perror("epoll_wait error");
            return 1;
        }

        for (i = 0; i < eventn; i++) {
            if (events[i].data.fd == listenfd) {
                memset(buf, 0x00, MAXLINE);
                clilen = sizeof(struct sockaddr);
                clientfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clilen);
                user_fds[clientfd] = 1;

                user_data = malloc(sizeof(struct udata));
                user_data->fd = clientfd;

                char *tmp = "First insert your nickname: ";
                write(user_data->fd, tmp, strlen(tmp));

                sleep(1);
                read(user_data->fd, user_data->name, sizeof(user_data->name));
                user_data->name[strlen(user_data->name) - 1] = 0;

                printf("Welcome [%s]\n", user_data->name);
                sleep(1);

                sprintf(buf, "Okay your nickname: %s\n", user_data->name);
                write(user_data->fd, buf, strlen(buf));

                ev.events = EPOLLIN;
                ev.data.ptr = user_data;
                epoll_ctl(epollfd, EPOLL_CTL_ADD, clientfd, &ev);

            } else {
                user_data = events[i].data.ptr;
                memset(buf, 0x00, MAXLINE);
                readn = read(user_data->fd, buf, MAXLINE);

                if (readn <= 0) {
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, user_data->fd, events);
                    close(user_data->fd);
                    user_fds[user_data->fd] = -1;
                    free(user_data);
                } else {
                    send_msg(events[i], buf);
                }
            }
        }
    }
}

void send_msg(struct epoll_event ev, char *msg) {
    int i;
    char buf[MAXLINE + 24];
    struct udata *user_data;
    user_data = ev.data.ptr;

    for (i = 0; i < 1024; i++) {
        if (user_fds[i] == 1) {
            memset(buf, 0x00, MAXLINE + 24);
            sprintf(buf, "%s: %s", user_data->name, msg);
            write(i, buf, strlen(buf)); // 수정: `MAXLINE+24` -> `strlen(buf)`
        }
    }
}
