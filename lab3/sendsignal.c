#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int i = 0;

void p_handler(int);
void c_handler(int);

int main(void) {
    pid_t pid, ppid;
    struct sigaction act;

    pid = fork(); // fork 호출
    if (pid == 0) {
        // 자식 프로세스
        act.sa_handler = c_handler;
        sigaction(SIGUSR1, &act, NULL);
        ppid = getppid(); // 부모 프로세스 ID 가져오기
        while (1) {
            sleep(1);
            kill(ppid, SIGUSR1); // 부모 프로세스에 시그널 전송
            pause(); // 시그널 대기
        }
    } else if (pid > 0) {
        // 부모 프로세스
        act.sa_handler = p_handler;
        sigaction(SIGUSR1, &act, NULL);
        while (1) {
            pause(); // 시그널 대기
            sleep(1);
            kill(pid, SIGUSR1); // 자식 프로세스에 시그널 전송
        }
    } else {
        // fork 실패
        perror("Error");
        return 1;
    }
    return 0;
}

void p_handler(int signo) {
    printf("\nParent handler call %d times.\n", ++i);
}

void c_handler(int signo) {
    printf("\nChild handler call %d times.\n", ++i);
}
