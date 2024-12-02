#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd;
    struct flock testlock;
    int pid;

    testlock.l_type = F_WRLCK;
    testlock.l_whence = SEEK_SET;
    testlock.l_start = 0;
    testlock.l_len = 10;

    /* open file */
    fd = open("testlock", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    if (fcntl(fd, F_SETLKW, &testlock) == -1) {
        perror("Parent locking");
        exit(1);
    }
    printf("parent: locked record\n");

    pid = fork();  // fork() 호출 수정
    /* child process */
    if (pid == 0) {
        testlock.l_len = 5;
        if (fcntl(fd, F_SETLKW, &testlock) == -1) {
            perror("Child locking");
            exit(1);
        }
        printf("child: locked\n");
        sleep(5);
        printf("child: exiting\n");
    }
    else if (pid > 0) {
        sleep(5);
        printf("parent exiting\n");
    }
    else {
        perror("Fork failed");
    }

    return 0; // main 함수 종료 명시
}
