#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<semaphore.h>
#include <time.h>
#define THREAD_NUM 16

sem_t semaphore;
int count = 0;
void* routine(void* args)
{
    printf("[%d] Waiting...\n", *(int*)args);
    sem_wait(&semaphore);
    sleep(1);
    count ++;
    printf("[%d] Logged in - count value: %d\n", *(int*)args, count);
    
    printf("[%d] Logged out\n", *(int*)args);
    sem_post(&semaphore);
    free(args);
    return 0;
}

int main(int argc, char *argv[])
{
    pthread_t th[THREAD_NUM];
    sem_init(&semaphore, 0, 2);
    int i;
    clock_t t;
    t = clock();
    for(i = 0; i <THREAD_NUM; i++)
    {
        int* a = (int* ) malloc(sizeof(int));
        *a = i;
        if(pthread_create(&th[i], NULL, &routine, a) != 0)
        {
            perror("Fail to creat thread");
        }
    }

    for(i = 0; i <THREAD_NUM; i++)
    {
        if(pthread_join(th[i], NULL) != 0)
        {
            perror("Fail to join thread");
        }
    }
    t = clock() - t;
    sem_destroy(&semaphore);
    printf("Time: %fs", (double)t/CLOCKS_PER_SEC);
    return 0;
}