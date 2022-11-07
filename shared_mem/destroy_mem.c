#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdbool.h>
#include "sharedmem.h"


int main(int argc, char *argv[])
{
    char* FILENAME = "write.c";
    if (argc != 1)
    {
        printf("usage -%s (no args)", argv[0]);
        return -1;
    }

    if (destroy_mem_block(FILENAME))
    {
        printf("Destroy block: %s\n", FILENAME);
    } 
    else
    {
        printf("Could not destroy block: %s\n", FILENAME);
    }

    return 0;
}

// #define IPC_RESULT_ERROR (-1)

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