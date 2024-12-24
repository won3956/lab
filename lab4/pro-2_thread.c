#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>  // intptr_t를 사용하려면 이 헤더를 포함해야 합니다.

#define THREAD_NUMBER 7

void *thread_func(void *arg) {
    // arg는 실제로 포인터로 받아오기 때문에, 이를 다시 int로 변환합니다.
    printf("Thread: I'm [%d] Thread\n", (int)(intptr_t)arg);
    return arg;
}

int main() {  // main 함수 반환 타입을 void에서 int로 변경
    pthread_t tid[THREAD_NUMBER];
    int status;
    int i;

    for (i = 0; i < THREAD_NUMBER; i++) {
        status = 0;
        // pthread_create에서 포인터와 정수 간 변환
        status = pthread_create(&tid[i], NULL, thread_func, (void *)(intptr_t)i);  // (void *)(intptr_t)i
        if (status != 0) {
            fprintf(stderr, "Create thread %d %d\n", i, status);
            exit(1);
        }
    }

    pthread_exit(NULL);
    return 0;  // main 함수에서 return 0
}
