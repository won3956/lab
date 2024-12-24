#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

#define BUFFER_SIZE 50
#define NUMITEMS 30

char message[BUFFER_SIZE] = "Child Thread:";
int message_cnt = 0;

pthread_mutex_t insert_mutex;
pthread_mutex_t client_mutex;
pthread_mutex_t server_mutex;
pthread_cond_t client_broad;
pthread_cond_t server_sig;

void receive_broadcast(int arg) {
    pthread_cond_wait(&client_broad, &client_mutex);
    printf("THREAD %d RECEIVED: %s\n", arg, message);
}

void *server(void *arg) {
    while (1) {
        pthread_mutex_lock(&server_mutex);
        pthread_cond_wait(&server_sig, &server_mutex);
        pthread_cond_broadcast(&client_broad);
        message_cnt = 0;
        pthread_mutex_unlock(&server_mutex);
    }
}

void *client(void *arg) {
    int status;
    while (1) {
        if (message_cnt == 0) {
            message_cnt = 1;
            sleep(1);
            printf("THREAD: %d: ", (int)(intptr_t)arg);
            printf("\n");
            pthread_cond_signal(&server_sig);
        } else {
            receive_broadcast((int)(intptr_t)arg);
            pthread_mutex_unlock(&client_mutex);
        }
    }
}

int main(int argc, char *argv[]) {
    int status;
    int cycle;
    void *result;
    pthread_t server_tid, client_tid[8];

    pthread_mutex_init(&client_mutex, NULL);
    pthread_mutex_init(&server_mutex, NULL);
    pthread_cond_init(&server_sig, NULL);
    pthread_cond_init(&client_broad, NULL);

    cycle = 5;
    for (int i = 0; i < cycle; i++) {
        status = pthread_create(&client_tid[i], NULL, client,
         (void *)(intptr_t)(i + 1));
        if (status != 0) {
            perror("Create client thread");
        }
    }

    status = pthread_create(&server_tid, NULL, server, NULL);
    if (status != 0) {
        perror("Create server thread");
    }

    status = pthread_join(server_tid, NULL);
    if (status != 0) {
        perror("Join server thread:");
    }

    for (int i = 0; i < cycle; i++) {
        status = pthread_join(client_tid[i], NULL);
        if (status != 0) {
            perror("Join Client thread");
        }
    }

    pthread_mutex_destroy(&client_mutex);
    pthread_mutex_destroy(&server_mutex);
    pthread_cond_destroy(&client_broad);
    pthread_cond_destroy(&server_sig);

    return 0;
}
