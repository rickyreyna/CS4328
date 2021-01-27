/* Ricardo Reyna - rjr110
 * Due Date: 02/24/2020 - Assignment 1, number 1.A
 * Operating Systems - M/W 5:00 pm
 */

#include <stdio.h>
#include<string.h>


struct student{
    char name[10];
    float gpa;
};

int main() {

    struct student learners[10];
    int count = 0;
    int flag = 0;
    int i = 0; //index for loop

    printf("Enter student name and it's GPA. To stop press Ctrl-D on a new line. \n");

    while (flag != EOF) {


        char name[10];
        float gpa;

        flag = scanf("%s", &name);
        scanf("%f", &gpa);

        strcpy(learners[count].name, name);
        learners[count].gpa = gpa;
        count++;
    }

    for(i=0; i<count; i++){
        if(learners[i].gpa >= 3.0){
            printf("%s", learners[i].name);
            printf("\n");
        }
    }

    return 0;
}
