#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define THREAD_NUM 4
int count = 0;
pthread_mutex_t mutex;

void* routine(void *arg)
{
    pthread_mutex_lock(&mutex);
    for(int i = 0; i < 2000; i ++){
        count++;
    } 
    pthread_mutex_unlock(&mutex);
    // printf("Count value - thread [%d]: %d\n", *(int*)arg, count);
}

int main(int argc, char *argv[])
{
    pthread_t p[THREAD_NUM];
    pthread_mutex_init(&mutex, NULL);
    int i;
    for(i = 0; i <THREAD_NUM; i++)
    {
        // int* a = (int* ) malloc(sizeof(int));
        // *a = i;
        if(pthread_create(&p[i], NULL, &routine, NULL) != 0)
        {
            perror("Fail to creat thread");
        }
    }

    for(i = 0; i <THREAD_NUM; i++)
    {
        if(pthread_join(p[i], NULL) != 0)
        {
            perror("Fail to join thread");
        }
    }
    pthread_mutex_destroy(&mutex);
    printf("Count value: %d\n", count);
    return 0;
}