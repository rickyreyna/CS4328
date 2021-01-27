/* Ricardo Reyna - rjr110
 * Due Date: 04/12/2020 - Assignment 3, Part B
 * Operating Systems - M/W 5:00 pm
 */
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

void *get25percent(void *argp);

struct arguments {
    double scholarship;
    double award;
};

pthread_mutex_t mutex;

int main() {
    int i = 0;
	
    pthread_t studentA;
    pthread_t studentB;
    pthread_t studentC;

    struct arguments threadArgs = {.scholarship = 4000, .award = 0};

    pthread_setconcurrency(2);

    while(threadArgs.scholarship != 0) {
        pthread_create(&studentA, NULL, get25percent, &threadArgs);
        sleep(1);
        pthread_create(&studentB, NULL, get25percent, &threadArgs);
        sleep(1);
        pthread_create(&studentC, NULL, get25percent, &threadArgs);
        sleep(1);

        pthread_join(studentA, NULL);
        pthread_join(studentB, NULL);
        pthread_join(studentC, NULL);
    }

    pthread_exit(0);
}

void *get25percent(void *arg) {
    struct arguments * insideArgs = arg;
    pthread_t id = pthread_self();

    pthread_mutex_lock(&mutex);
    insideArgs->award = ceil( (insideArgs->scholarship * 0.25) );
    insideArgs->scholarship -= insideArgs->award; 
    printf("Student: %x. Award = %0.0f\n", id, insideArgs->award);
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}



