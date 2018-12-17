#include<stdio.h>
#include<pthread.h>
#include<sys/time.h>
#include<math.h>
#include<stdlib.h>

#define true 1
#define false 0
#define RUNTIMES 100
#define MAX 10000000

int flag[2];
int turn;

int index = 0;
int data[MAX];

void *thread1()
{
    int i, temp;
    printf("thread1 enters critical section\n");
    for(i = 0; i < MAX; i += 2)
    {
        temp = __sync_fetch_and_add(&index, 1);
        data[temp] = i; //even ( i+1 for thread 2)
    }
}

//thread2
void *thread2()
{
    int i, temp;
    printf("thread2 enters critical section\n");
    for(i = 0; i < MAX; i += 2)
    {
        temp = __sync_fetch_and_add(&index, 1);
        data[temp] = i + 1; // odd
    }  
}

int main()
{
    pthread_t tid1, tid2;
    int i, err, diff, temp;
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    for(i = 0; i < 1000; i ++)
    {
        err = pthread_create(&tid1, NULL, thread1, NULL);
        if(err != 0)
        {
            printf("Create thread 1 failed!\n");
            exit(0);
        }
        err = pthread_create(&tid2, NULL, thread2, NULL);
        if(err != 0)
        {
            printf("Create thread 2 failed!\n");
            exit(0);
        }
        err = pthread_join(tid1, NULL);
        if(err != 0)
        {
            printf("Stop thread 1 failed!\n");
            exit(0);
        }
        err = pthread_join(tid2, NULL);
        if(err != 0)
        {
            printf("Stop thread 2 failed!\n");
            exit(0);
        }
    }
    gettimeofday(&end_time, NULL);
    
    diff = abs(data[0] - data[1]);
    for(i = 1; i < MAX && data[i]; i ++)
    {
        temp = abs(data[i] - data[i+1]);
        diff = diff < temp ? temp : diff;
    }

    printf("Max abstraction of difference is %d.\n", diff);
    printf("Runtime: %f.\n", difftime(end_time.tv_sec, start_time.tv_sec)/1000);
    return 0;
}