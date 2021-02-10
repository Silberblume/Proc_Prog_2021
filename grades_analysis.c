#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

#define YEARS    4
#define SUBJECTS 8

int main() {
    int grades_table[YEARS][SUBJECTS] = {
        {5, 6, 6, 2, 8, 7, 10, 7},
        {6, 2, 3, 3, 9, 8,  3, 9},
        {6, 7, 5, 8, 6, 7, 10, 5},
        {1, 3, 3, 8, 9, 4,  3, 6}
    };

    return 0;
}

