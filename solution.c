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

    analyze_table(YEARS, SUBJECTS, grades_table, failed_table, &under5, &exact10);
    print_data(failed_table, under5, exact10);

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

int read_data(char msg[], int lower_lim, int upper_lim){
    int result;
    do {
        printf("%s: ", msg), result=GetInteger();
    } while (result < lower_lim || result > upper_lim);
}

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

