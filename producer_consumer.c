#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>

#define NUM_THREADS 2

int buffer[10];
int count=0;
pthread_mutex_t mut;
sem_t semempty, semFull; 


void* producer(void* arg){
    //producde
    while(1){
        int x = rand() % 100;
        sem_wait(&semempty);
        pthread_mutex_lock(&mut);
        buffer[count] = x;
        count++;
        pthread_mutex_unlock(&mut);
        sem_post(&semFull);
    }
}

void* consumer(void* arg){
    while(1){
        sem_wait(&semFull);
        pthread_mutex_lock(&mut);
        int from = buffer[count-1];
        count--;
        printf("Got a number that is: %d\n", from);
        sleep(1);   
        pthread_mutex_unlock(&mut);
        sem_post(&semempty);
        
    }
}

void* functions[NUM_THREADS] = {&producer, &consumer};
int main(void){
    srand(time(NULL));
    pthread_mutex_init(&mut,NULL);
    pthread_t th[NUM_THREADS];
    sem_init(&semempty, 0,10);
    sem_init(&semFull, 0,0);
    for(int i=0; i<NUM_THREADS; i++){
        pthread_create(&th[i], NULL, functions[i], NULL);
    }

    for(int i=0; i<NUM_THREADS; i++){
        pthread_join(th[i], NULL);
    }

    pthread_mutex_destroy(&mut);
    sem_destroy(&semempty);
    sem_destroy(&semFull);

printf("Main program exiting...\n");
    return 0;

}