/* Ricardo Reyna - rjr110
 * Due Date: 02/24/2020 - Assignment 1, number 1.B
 * Operating Systems - M/W 5:00 pm
 */

#include <stdio.h>
#include<string.h>


struct student{
    char name[10];
    char temp[10];
};

int main() {

    struct student learners[10];
    int count = 0;
    int totalnames = 10;
    int flag = 0;
    int i, j; //index for loop
    char name[10][10] = {};

    printf("Enter student names. To stop press Ctrl-D on a new line. \n");

    while ( (totalnames > count) && flag != EOF) {

        flag = scanf("%s", &name[count]);

        strcpy(learners[count].name, name[count]);
        count++;
    }

    for(i=0; i < totalnames-1; i++){
        for(j=i+1; j < totalnames; j++){
            if(strcmp(name[i], name[j]) > 0){
                strcpy(learners->temp, name[i]);
                strcpy(name[i], name[j]);
                strcpy(name[j], learners->temp);
            }
        }
    }

    printf("\n");
    for(i=0; i < totalnames; i++){
        printf("%s\n", name[i]);
    }

    return 0;
}
