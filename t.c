#include <stdio.h>
#include <string.h>  // for strcpy() function
#include <stdlib.h>  // for malloc() function

#define MAX_NAZIV 30
#define MAX_KLUBOVA 20

typedef struct fudbal_st {
    char naziv_tima[MAX_NAZIV];
    int gol_razlika;
    unsigned broj_bodova;
} FUDBAL;

int main (int argc, char **argv) {
    FUDBAL klubovi[MAX_KLUBOVA];
    return 0;
}