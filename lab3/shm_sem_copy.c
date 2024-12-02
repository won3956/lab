#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

#define SHMSIZE 1024
#define SHMKEY (key_t)0111
#define SEMKEY (key_t)0111

union semapore {
    int value;
    struct semid_ds *buf;
    unsigned short int *array;
};

static int sem;

int parent_process_read(char *filename) {
    int shm;
    void *shmaddr;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fopen failed");
        return -1;
    }
    printf("Parent process start.\n");
    sleep(3);

    if ((shm = shmget(SHMKEY, SHMSIZE, IPC_CREAT | 0666)) == -1) {
        perror("shmget failed");
        fclose(fp);
        return -1;
    }

    if ((shmaddr = shmat(shm, NULL, 0)) == (void *)-1) {
        perror("shmat failed");
        fclose(fp);
        return -1;
    }

    if (fgets((char *)shmaddr, SHMSIZE, fp) == NULL) {
        perror("fgets failed");
        shmdt(shmaddr);
        fclose(fp);
        return -1;
    }

    if (shmdt(shmaddr) == -1) {
        perror("shmdt failed");
        fclose(fp);
        return -1;
    }

    printf("Read success\n");
    fclose(fp);
    printf("Parent process finish.\n");
    return 0;
}

int child_process(char *filename) {
    int shm;
    void *shmaddr;
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("fopen failed");
        return -1;
    }
    printf("Child process start.\n");
    sleep(2);

    if ((shm = shmget(SHMKEY, SHMSIZE, IPC_CREAT | 0666)) == -1) {
        perror("shmget failed");
        fclose(fp);
        return -1;
    }

    if ((shmaddr = shmat(shm, NULL, 0)) == (void *)-1) {
        perror("shmat failed");
        fclose(fp);
        return -1;
    }

    if (fputs((char *)shmaddr, fp) == EOF) {
        perror("fputs failed");
        shmdt(shmaddr);
        fclose(fp);
        return -1;
    }

    printf("Copy success.\n");

    if (shmdt(shmaddr) == -1) {
        perror("shmdt failed");
        fclose(fp);
        return -1;
    }

    if (shmctl(shm, IPC_RMID, NULL) == -1) {
        perror("shmctl failed");
        fclose(fp);
        return -1;
    }

    fclose(fp);
    printf("Child process finish.\n");
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <original file name> <create file name>\n", argv[0]);
        exit(1);
    }

    union semapore semapore;
    struct sembuf mysem_open = {0, -1, SEM_UNDO};
    struct sembuf mysem_close = {0, 1, SEM_UNDO};

    sem = semget(SEMKEY, 1, 0666 | IPC_CREAT);
    if (sem == -1) {
        perror("semget error");
        exit(1);
    }

    semapore.value = 1;
    if (semctl(sem, 0, SETVAL, semapore) == -1) {
        perror("semctl error");
        exit(1);
    }

    if (semop(sem, &mysem_open, 1) == -1) {
        perror("semop error");
        exit(1);
    }

    if (parent_process_read(argv[1]) == -1) {
        semop(sem, &mysem_close, 1);
        exit(1);
    }

    sleep(2);

    if (child_process(argv[2]) == -1) {
        semop(sem, &mysem_close, 1);
        exit(1);
    }

    semop(sem, &mysem_close, 1);

    printf("Check your %s file.\n", argv[2]);
    return 0;
}
