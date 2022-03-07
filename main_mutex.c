#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define NUM_THREADS 2

pthread_mutex_t mutex1, mutex2;
pthread_cond_t cond;


int mails=0;

// typedef void* func (void*);

// func functions[2] = {routine, func routine2};


void* routine(void* id){
    printf("Thread %d entered the routine function\n", *(int*)id);
    pthread_mutex_lock(&mutex1);
    pthread_cond_wait(&cond, &mutex1);
    sleep(1);
    pthread_mutex_lock(&mutex2);
        
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    free(id);
}

void* routine2(void* id){
    printf("Thread %d entered the routine function\n", *(int*)id);
    pthread_mutex_lock(&mutex2);
    sleep(1);
    pthread_mutex_lock(&mutex1);
    
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    pthread_cond_signal(&cond);
    free(id);
}

void* functions[2] = {&routine, &routine2};

int main(int argc, char*argv[]){
    pthread_t t[NUM_THREADS];
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
    pthread_cond_init(&cond, NULL);

    for(int i=0; i<NUM_THREADS; i++){
        int* r = malloc(sizeof(int));
        *r = i;
        pthread_create(&t[i], NULL,functions[i], r);
    }

    for( int i=0; i<NUM_THREADS; i++){
        pthread_join(t[i], NULL);
    }

    printf("total number of mails: %d\n", mails);
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
    pthread_cond_destroy(&cond);
    return 0;
}