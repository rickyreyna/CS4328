/* Ricardo Reyna - rjr110
 * Due Date: 02/24/2020 - Assignment 1, number 3
 * Operating Systems - M/W 5:00 pm
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char* argv[]) {
    char cmd[10];
    int pid;

    if(argc == 1 || argc > 2 || argc < 1)
        printf("\nPlease enter a valid unix command in command line to proceed further");

    else {
        pid = fork();
        if (pid == 0) {
            sprintf(cmd, argv[1]);
            system(cmd);
            printf("The Child Process is running: \n%d" , getpid());
            printf("Parent Process: \n%d" , getppid()); //returns parent id
            printf("Completed \n%d" , getpid());
        }
        else if(pid < 0)
        {
            printf("Fork failed.\n");
        }

        else {
            printf("Waiting for child to complete");
            wait(NULL);
            printf("Child has finished running: \n%d" , getpid());
            printf("Completed\n%d" , getpid());
        }
    }
	
    return 0;
}