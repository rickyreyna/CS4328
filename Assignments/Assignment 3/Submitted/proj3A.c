/* Ricardo Reyna - rjr110
 * Due Date: 04/12/2020 - Assignment 3, Part A
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

int main() {
    int i = 0;
    const int NUM_THREADS = 3;

    pthread_t studentA;
    pthread_t studentB;
    pthread_t studentC;

    struct arguments threadArgs = {.scholarship = 4000, .award = 0};

    pthread_create(&studentA, NULL, get25percent, &threadArgs);
    pthread_create(&studentB, NULL, get25percent, &threadArgs);
    pthread_create(&studentC, NULL, get25percent, &threadArgs);

    pthread_exit(0);
}

void *get25percent(void *arg) {
    struct arguments * insideArgs = arg;
    pthread_t id = pthread_self();

    while((insideArgs->scholarship) > 0){
        insideArgs->award = ceil( (insideArgs->scholarship * 0.25) ); 
        insideArgs->scholarship -= insideArgs->award; 

        printf("Student : %x. Award = %0.0f\n", id, insideArgs->award);
    }

    pthread_exit(0);
}



