/// The point of this HW is to learn more about critical section
/// HW will have 3 threads that will be executed in a loop as long as there is money the students will keep coming back
/// Termination point is when money is 0.
/// Should print the sequence of students taking the money. When adding all the prints it should equal 4000
/// HOMEWORK 3 MUST USE 3 THREADS. FIRST PART DOES NOT PROTECT CRITICAL SECTION. SECOND PART MUST PROTECT THE CRITICAL SECTION
/// USE ceil() FROM MATH LIBRARY TO ROUND NUMBERS. EX. ceil(3.14) = 4
/// TO COMPILE USE: $ gcc -o pl pl.c -lpthread -lm    (-lpthread tells the compiler you are using the thread pacakage and -lm tells the compiler to use the math pacckage)
///  sleep() delays in seconds
#include <stdio.h>
#include <pthread.h>

#define TIMES 10
#define CAPACITY 3
#define ITEMSIZE 20

struct Buffer
{
    int item[ITEMSIZE];
    int size;
};

void *producer();
void *consumer();

pthread_mutex_t mutex;
pthread_cond_t  full_cond;
pthread_cond_t  empty_cond;
struct Buffer buffer;

int main()
{
    int i;
    pthread_t tid;

    for (i =0; i< ITEMSIZE; i++) buffer.item[i]=-1;
    buffer.size = 0;

    pthread_setconcurrency(2); /// This line is to make threads run at the same time
/// This is system call used to create a new thread
/// First parameter is the thread ID, second and fourth are not relevant for this hw. The third parameter is the function that the thread will run.
    pthread_create(&tid, NULL, (void *(*)(void *))producer, NULL);
    pthread_create(&tid, NULL, (void *(*)(void *))consumer, NULL);


    pthread_exit(0); /// Normal termination of thread
}

void *producer() {
    int i,j;

    for (j = 0; j<TIMES; j++) {
        pthread_mutex_lock(&mutex); /// THIS LINE PROTECTS THE FOLLOWING PART (THE CRITICAL SECTION) Equivalent to P(Mutex)
        if (buffer.size == CAPACITY) { // checks if buffer is full
            printf("Buffer is full. Producer is waiting...\n");
            pthread_cond_wait(&full_cond, &mutex);  // Blocks producer thread
        }
        else { // Otherwise we can put more items in the producer
            printf("Producer adds one more item ...\n");
            buffer.item[buffer.size++] = buffer.size;
            for (i =0;i<buffer.size; i++)
                printf("%d ", buffer.item[i]);
            printf("\n");
            pthread_cond_broadcast(&empty_cond); // This unblocks consumer thread

        }
        pthread_mutex_unlock(&mutex); /// THIS LINE STOPS PROTECTING THE CRITICAL SECTION equivalent to M(Mutex)
    }
}

void *consumer() {
    int i,j;

    for (j=0; j<TIMES; j++) {
        pthread_mutex_lock(&mutex); /// THIS LINE PROTECTS THE FOLLOWING PART (THE CRITICAL SECTION) Equivalent to P(Mutex)

        if (buffer.size == 0) { // Checks if buffer is empty
            printf("Buffer is empty. Consumer is waiting...\n");
            pthread_cond_wait(&empty_cond, &mutex); // Blocks consumer thread
        }
        else {
            printf("Consumer consumes an item from buffer...\n");
            buffer.size--;
            for (i=0; i<buffer.size; i++)
                printf("%d ", buffer.item[i]);
            printf("\n");
            pthread_cond_broadcast(&full_cond); // Unblock producer thread
        }
        pthread_mutex_unlock(&mutex); /// THIS LINE STOPS PROTECTING THE CRITICAL SECTION equivalent to M(Mutex)
    }

}




