#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdbool.h>
#include<fcntl.h>
#include<semaphore.h>
#include<time.h>
#include "sharedmem.h"


static int get_shared_block(char *filename, int size)
{
    key_t key;

    //Request a key
    //The key is linked to a filename, so that other programs can access it
    key = ftok(filename, 0);
    if(key == IPC_RESULT_ERROR)
    {
        return IPC_RESULT_ERROR;
    }

    return shmget(key, size, 0644 | IPC_CREAT);

}

char *attach_mem_block(char *filename, int size)
{
    int shared_block_id = get_shared_block(filename, size);
    char* result;
    
    result = (char*)shmat(shared_block_id, NULL, 0);
    if (shared_block_id == IPC_RESULT_ERROR)
    {
        return NULL;
    }
    return result;
}

bool detach_mem_block(char *block)
{
    return (shmdt(block) != IPC_RESULT_ERROR);
}

bool destroy_mem_block(char *filename)
{
    int shared_block_id = get_shared_block(filename, 0);

    if (shared_block_id == IPC_RESULT_ERROR)
    {
        return NULL;
    }
    return (shmctl(shared_block_id, IPC_RMID, NULL) != IPC_RESULT_ERROR);
}