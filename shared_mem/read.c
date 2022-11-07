#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdbool.h>
#include<fcntl.h>
#include<semaphore.h>
#include "sharedmem.h"


int main(int argc, char *argv[])
{
    char* FILENAME = "write.c";

    if (argc != 1)
    {
        printf("usage - %s //no args", argv[0]);
        return -1;
    }

    sem_unlink(SEM_CONSUMER);
    sem_unlink(SEM_PRODUCER);

    sem_t *sem_prod = sem_open(SEM_PRODUCER, O_CREAT, 0660, 0);
    if (sem_prod == SEM_FAILED)
    {
        perror("sem_open/producer");
        exit(EXIT_FAILURE);
    }

    sem_t *sem_cons = sem_open(SEM_CONSUMER, O_CREAT, 0660, 1);

    if (sem_cons == SEM_FAILED)
    {
        perror("sem_open/consumer");
        exit(EXIT_FAILURE);
    }

    char* block = attach_mem_block(FILENAME, 4096);
    if (block == NULL)
    {
        printf("ERROR: couldn't get block\n");
        return -1;
    }

    printf("--------SEMAPHORE------- \n");

    while(true)
    {
        if(strlen(block) > 0)
        {
            // time_t t;
            // time(&t);
            // printf("Time: %s\n", ctime(&t));
            int val_cons, val_prod;

            // sem_getvalue(sem_cons, &val_cons);
            // printf("SEM_CON value: %d |", val_cons);
            // sem_getvalue(sem_prod, &val_prod);
            // printf("SEM_PROD value: %d\n", val_prod);

            sem_wait(sem_prod);

            //
            // sem_getvalue(sem_prod, &val_prod);
            // printf("SEM_PROD value: %d\n", val_prod);

            printf("Reading: \"%s\"\n", block);

            bool done = (strcmp(block, "quit") ==0);
            sem_post(sem_cons);

            // sem_getvalue(sem_cons, &val_cons);
            // printf("SEM_CON value: %d\n", val_cons);
            printf("----------------------------------\n");
            if(done) break;
        }

    }

    sem_close(sem_prod);
    sem_close(sem_cons);

    
    detach_mem_block(block);

    return 0;
}

// #define IPC_RESULT_ERROR (-1)
// #define SEM_PRODUCER "/myproducer"
// #define SEM_CONSUMER "/myconsumer"

// static int get_shared_block(char *filename, int size)
// {
//     key_t key;

//     //Request a key
//     //The key is linked to a filename, so that other programs can access it
//     key = ftok(filename, 0);
//     if(key == IPC_RESULT_ERROR)
//     {
//         return IPC_RESULT_ERROR;
//     }

//     return shmget(key, size, 0644 | IPC_CREAT);

// }

// char *attach_mem_block(char *filename, int size)
// {
//     int shared_block_id = get_shared_block(filename, size);
//     char* result;
    
//     result = (char*)shmat(shared_block_id, NULL, 0);
//     if (shared_block_id == IPC_RESULT_ERROR)
//     {
//         return NULL;
//     }
//     return result;
// }

// bool detach_mem_block(char *block)
// {
//     return (shmdt(block) != IPC_RESULT_ERROR);
// }

// bool destroy_mem_block(char *filename)
// {
//     int shared_block_id = get_shared_block(filename, 0);

//     if (shared_block_id == IPC_RESULT_ERROR)
//     {
//         return NULL;
//     }
//     return (shmctl(shared_block_id, IPC_RMID, NULL) != IPC_RESULT_ERROR);
// }