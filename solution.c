#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

#define YEARS    4
#define SUBJECTS 8

typedef struct{
    int year;
    int subject;
} failedT;

void analyze_table(int years, int subjects, int grades_table[years][subjects], failedT failed_table[years*subjects], int *under5, int *exact10);
void print_data(failedT failed_table[], int under5, int exact10);
int read_data(char msg[], int lower_lim, int upper_lim);
void update_data(int years, int subjects,int grades_table[years][subjects]);

int main() {
    int grades_table[YEARS][SUBJECTS] = {
        {5, 6, 6, 2, 8, 7, 10, 7},
        {6, 2, 3, 3, 9, 8,  3, 9},
        {6, 7, 5, 8, 6, 7, 10, 5},
        {1, 3, 3, 8, 9, 4,  3, 6}
    };

    int under5, exact10, answer;
    failedT failed_table[32];
/* Initial printing */ 
    analyze_table(YEARS, SUBJECTS, grades_table, failed_table, &under5, &exact10);
    print_data(failed_table, under5, exact10);
 /*Loop-menu, guard is 0*/
    do{                                     
     printf("Do you want to update a grade? (1 for YES / 0 for NO): "), answer = GetInteger();
     switch (answer){
     case 0: break;
     case 1:
        update_data(YEARS,SUBJECTS,grades_table);
        analyze_table(YEARS, SUBJECTS, grades_table, failed_table, &under5, &exact10);
        print_data(failed_table, under5, exact10);
        break;
    default: break;
    }
    } while (answer != 0);

    return 0;
}

/* This function updates (or initializes on the first time) the failed_table array. The array includes information on the number of exam failures - ironic...
The under5 counter (which is returned) will help us read as many entries as there really are, since there can be 0<=n<=YEARS*SUBJECTS failures.
The exact10 counter (also returend) will be needed later.  */ 

void analyze_table(int years, int subjects, int grades_table[years][subjects], failedT failed_table[YEARS*SUBJECTS], int *under5, int *exact10){
    int i,j;
    (*under5) = 0;
    (*exact10) = 0;
    for (i=0; i<YEARS ; i++){
        for (j=0; j<SUBJECTS; j++){
            if (grades_table[i][j] < 5){
                failed_table[(*under5)].year = i;       
                failed_table[(*under5)].subject = j;
                (*under5)++;
            }
            else if (grades_table[i][j] == 10) (*exact10)++;
        }
    }
}


/* Here, the exact10 counter is used to calculate the number and percentage of perfect grades */ 
void print_data(failedT failed_table[], int under5, int exact10){
    int i;
    float percentage;

    printf("Failed grades:\n");
    for (i=0 ; i<under5 ; i++){
        printf("Year: %d, Subject: %d\n", failed_table[i].year, failed_table[i].subject);
    }

    percentage = 100*((float)exact10/(YEARS*SUBJECTS));
    printf("\nCount of 10s: %d\nPercentage of 10s: %.2f%%\n\n", exact10, percentage);


}

/*Proper understanding of this function is paramount to the implementation of the program. 
 This function is only called by update_data(), and is used to majorly simplify its function.
 It basically boils down to properly reading a bounded value from the user, along with printing the right prompt*/ 
int read_data(char msg[], int lower_lim, int upper_lim){
    int result;
    do {
        printf("%s: ", msg), result=GetInteger();
    } while (result < lower_lim || result > upper_lim);
}

/*As written above, update_data makes use of the read_data function to read values from the user.
Those values are then used to update the grades_table.*/

void update_data(int years, int subjects,int grades_table[years][subjects]){
    int i,j,val;
    char msg1[20] = "Year (0-3)";
    char msg2[20] = "Subject (0-7)";
    char msg3[20] = "Grade (0-10)";

    i=read_data(msg1, 0,3);
    j=read_data(msg2, 0,7);
    val=read_data(msg3, 0,10);
    grades_table[i][j] = val;

    printf("\n\n");
}

