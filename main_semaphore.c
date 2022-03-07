#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define NUM_THREADS 3

sem_t sem;

void* routine(void* arg){
    sem_wait(&sem);
    printf("Thread inside routine\n");
    sleep(1);
    printf("Thread Exiting...\n");
    sleep(1);
    sem_post(&sem);
}
int main(int argc, char* argv[]){
    pthread_t th[NUM_THREADS];
    sem_init(&sem, 0, 1);

    for(int i=0; i<NUM_THREADS; i++){
        pthread_create(&th[i], NULL, &routine, NULL);
    }

    for(int i=0; i<NUM_THREADS; i++){
        pthread_join(th[i],NULL);
    }

    sem_destroy(&sem);
    
    printf("Exiting...\n");

    return 0;
}