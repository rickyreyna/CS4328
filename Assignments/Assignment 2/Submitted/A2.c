/* Ricardo Reyna - rjr110
 * Due Date: 04/03/2020 - Assignment 2
 * Operating Systems - M/W 5:00 pm
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>
#include <io.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

main() {

    char *path, *argv[20], buf[80], n, *p;
    int m, status, inword, continu; // m = # of commands?

    while(1) {
        inword = 0;
        p = buf;
        m = 0;
        continu=0;

        printf( "\nshhh> ");

        while ( ( n = getchar() ) != '\n'  || continu ) {
            if ( n ==  ' ' ) {
                if ( inword ) {
                    inword = 0;
                    *p++ = 0;
                }
            }

            else if ( n == '\n' ) continu = 0;

            else if ( n == '\\' && !inword ) continu = 1;

            else {
                if ( !inword ) {
                    inword = 1;
                    argv[m++] = p;
                    *p++ = n;
                }
                else {
                    *p++ = n;
                }
            }
        }

        *p++ = 0;
        argv[m] = 0;

        if ( strcmp(argv[0],"exit") == 0 ) {
            exit (0);
            return 0;
        }
//        if ( fork() == 0 ) {
//            execvp( argv[0], argv );
//            printf ( " didn't exec \n ");
//
//        }

/*
 * PREPROCESSING
 * Assuming every command is a valid command
 * processes = k pipes + 1
 * cout '|' replace | with 0
 * cout '<' replace < with 0. Save file name
 * cout '>' replace > with 0. Save file name
 * Need an array for the starting of each array
 *  Ex. start[0] = 0
 *      start[1] = 0
 */

        int i; // index
        int pipes = 0;  // k
        char input[10][10];
        char output[10][10];
        int output_count = 0;
        int input_count = 0;
        int start[20] = {0};
        int counter = 0;

        for(i = 0; i < m; i++) {
          //  printf("argv[i]: %s \n", argv[i]);

            start[counter] = i; // counts till pipe

            // Checks if argument is a pipe
            if ( strcmp(argv[i], "|" ) == 0 ) {
                argv[i] = 0;
                pipes++;
                start[counter++];
            }
            // Checks if argument is input redirect
            if ( strcmp(argv[i], "<" ) == 0 ) {
                argv[i] = 0;
                strcpy(input[input_count], argv[i+1]);
               // printf("Input: %s", input[input_count]);
                input_count++;
            }
            // Checks if argument is output redirect
            if ( strcmp(argv[i], ">" ) == 0 ) {
                argv[i] = 0;
                strcpy(output[output_count], argv[i+1]);
               // printf("Output: %s", output[output_count]);
                output_count++;
            }
           // printf("Argv[i]: %s \n", argv[1]);
        }

        ///
        int left_fd[2];
        int right_fd[2];
        pid_t pid;
        int fd[2];
        int n, m, = 0; // n used for input, m used for output

         for(i=0; i=pipes; i++){


            if(there are pipes && is not the last process) {
                pipe(right_fd);
            }

            pid = fork();
            if(pid < 0) { // Error
                perror("ERROR - Fork");
                exit(2);
            }

            else if(pid > 0) { // Parent Process
                if(i > 0){
                    close(left_fd[0]);
                    close(left_fd[1]);
                }
                left_fd[0] = right_fd[0];
                left_fd[1] = right_fd[1];
            }

            else { // Child Process
                if(input redirection && i == 0){ // input redir, first child process
                    // Input redirection
                    n = open("input.txt" , O_RDONLY);
                    close(0);
                    dup(n);
                    close(n);
                    // Connect back to pipe
                    close(1);
                    dup(fd[1]);
                    close(fd[0]);
                    close(fd[1]);
                    execl("./pre", "pre",(char *)0);
                }
                if(there are pipes) {
                    1st: r_fd
                    middle: l_fd to r_fd
                    last: r_fd
                }
               if(output redir && i == pipes){// output redir, last child process
                   // Output Redirection
                    m = creat("output.txt", 0755);
                    close(1);
                    dup(m)
                    close(m);
                    // Change input of process
                    close(0);
                    dup(fd[0]);
                    close(fd[0]);
                    close(fd[1]);
                    execl("./sort", "sort", (char *)0);

                }
                execvp(argv[start[i]], &argv[start[i]]);
            }
        }
        wait(&status);
    }
}

