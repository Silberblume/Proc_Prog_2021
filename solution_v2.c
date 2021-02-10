#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

// Dhlwsh Statherwn
#define YEARS    4
#define SUBJECTS 8
#define N        32

// Dhlwsh struct Gia Erwthma 1
typedef struct
{
    int year;
    int subject;
} eight_to_tenT;

// Dhlwsh Protypwn Synarthsewn
void analyze_table(int grades_table[YEARS][SUBJECTS], eight_to_tenT eight_to_ten_table[], int *over8, float *over_avrg);
void print_data(eight_to_tenT eight_to_ten_table[], int count, float avrg);
int read_data(char prompt[], int lower, int upper);
void update_data(int grades_table[YEARS][SUBJECTS]);

int main()
{
    //dhlwsh struct
    eight_to_tenT eight_to_ten_table[N];
    //arxikh dhlwsh pinaka
    int grades_table[YEARS][SUBJECTS] = {
        {5, 6, 6, 2, 8, 7, 10, 7},
        {6, 2, 3, 3, 9, 8,  3, 9},
        {6, 7, 5, 8, 6, 7, 10, 5},
        {1, 3, 3, 8, 9, 4,  3, 6}
    };
    //dhlwsh counter gia vathmous >= 8
    int over8;
    //dhlwsh metavlhths pou pairnei thn epilogh toy xrhsth gia allagh vathmou
    int ans;
    //metavlhth gia vathmous panw apo ton meso oro. Den mou aresei polu ws onoma alla kanei th douleia
    float over_avrg;

    //Arxikh Klhsh Synarthsewn Gia Erwthmata 2, 3
    analyze_table(grades_table, eight_to_ten_table, &over8, &over_avrg);
    print_data(eight_to_ten_table, over8, over_avrg);

    /*
    \n Gia na einai swsto to output. Atermon vroxos pou stamataei an ans == 0, kai sunexizei an o xrhsthshs
    dwsei kati ektos tou 0. An dwsei 1 mpainei mesa sto if kai kalountai oi katallhles sunarthseis
    */
    printf("\n");
    while (1)
    {
        printf("Do you want to update a grade? (1 for YES / 0 for NO): ");
        ans = GetInteger();
        if (ans == 0)
            break;
        else if (ans == 1)
        {
            update_data(grades_table);
            analyze_table(grades_table, eight_to_ten_table, &over8, &over_avrg);
            printf("\n");
            print_data(eight_to_ten_table, over8, over_avrg);
            printf("\n");
        }
    }

    return 0;
}

/*
Arxikopoiw counters kai to sum, vazw 2 forew gia na prospelasw ton pinaka vazwntas 2 if pou elexoun an einai
o vathmos panw apo 8 kai panw apo 5. An einai panw apo 8 allazw to struct antistoixa mazi me ton counter o opoios dra
kai ws index kai ws count. Sthn allh if auxanw kai to count twn vathmwn panv apo 5 kai ta auxanw. Tha mporousan na mpoun
emfwleumenes oi ifs alla doulueie kai de thelw na spasw twn kwdika.
*/

void analyze_table(int grades_table[YEARS][SUBJECTS], eight_to_tenT eight_to_ten_table[], int *over8, float *avrg)
{
    int i, j;
    int sum, count;

    sum = count = 0;
    *over8 = 0;
    for (i = 0; i < YEARS; i++)
    {
        for (j = 0; j < SUBJECTS; j++)
        {
            if (grades_table[i][j] >= 8)
            {
                eight_to_ten_table[*over8].year = i;
                eight_to_ten_table[*over8].subject = j;
                (*over8)++;
            }
            if (grades_table[i][j] >= 5)
            {
                count++;
                sum += grades_table[i][j];
            }
        }
    }

    *avrg = sum / (float) count;
}

/* Metaferw to count gia panw apo 8, pernaw me mia for to struct kai ektypwnw meta to average*/
void print_data(eight_to_tenT eight_to_ten_table[], int count, float avrg)
{
    int i;

    printf("8 to 10 grades:\n");
    for (i = 0; i < count; i++)
        printf("Year: %d, Subject: %d\n", eight_to_ten_table[i].year, eight_to_ten_table[i].subject);

    printf("\nAverage of passed: %.2f\n", avrg);
}

/* Exw enan atermon vroxo o opoios stamataei mono an o arithmos einai entos twn oriwn */
int read_data(char prompt[], int lower, int upper)
{
    int n;

    while (1)
    {
        printf("%s", prompt);
        n = GetInteger();
        if (lower <= n && n <= upper)
            return n;
    }
}

/* Arxika kalw thn read_data me tiw katallhlew parametrous, kai meta allazw katallhla ton vathmo */
void update_data(int grades_table[YEARS][SUBJECTS])
{
    int i, j;
    int year, subject, grade;

    year = read_data("Year (0-3): ", 0, 3);
    subject = read_data("Subject (0-7): ", 0, 7);
    grade = read_data("Grade (0-10): ", 0, 10);

    grades_table[year][subject] = grade;
}
