#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<semaphore.h>

#define THREAD_NUM 4
pthread_mutex_t mutex;
int count = 0;

sem_t semaphore;

void* routine1(void* args)
{
    while (1)
    {
        // sem_wait(&semaphore);
        pthread_mutex_lock(&mutex);
        count +=5;   
        printf("[%d] Current value %d \n", *(int*)args, count);
    }
    
    return 0;
}

void* routine2(void* args)
{
    
    while (1)
    {
        pthread_mutex_unlock(&mutex);
        printf("[%d] Mutex unlock\n", *(int*)args);

        // sem_post(&semaphore);
        // printf("[%d] Semaphore unlock\n", *(int*)args);
        usleep(50000);
    }
    
    return 0;
}
int main(int argc, char *argv[])
{
    pthread_t th[THREAD_NUM];
    // sem_init(&semaphore, 0, 1);
    pthread_mutex_init(&mutex, NULL);
    int i;
    for(i = 0; i <THREAD_NUM; i++)
    {
        int* a = (int* ) malloc(sizeof(int));
        *a = i;
        if (i%2 == 0){
            if(pthread_create(&th[i], NULL, &routine1, a) != 0)
            {
                perror("Fail to creat thread");
            }
        }else
        {
            if(pthread_create(&th[i], NULL, &routine2, a) != 0)
            {
                perror("Fail to creat thread");
            }
        }
    }

    for(i = 0; i <THREAD_NUM; i++)
    {
        if(pthread_join(th[i], NULL) != 0)
        {
            perror("Fail to join thread");
        }
    }
    sem_destroy(&semaphore);
    return 0;
}