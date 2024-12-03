#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DRZAVA 20
#define MAX_HRANA 20
#define MAX_TIMOVI 100

typedef struct tim_st{
char drzava[MAX_DRZAVA];
char hrana[MAX_HRANA];
double publika;
double ziri;
}TIM;

FILE* safe_fopen(char*, char*, int);
void ucitaj_timove(FILE*, TIM*, int*);
void sledeci(TIM*, TIM*, int, double, int*);
void ispisi(FILE*, TIM*, int);

int main (int argc, char *argv[]) {
    if(argc!=3){
        printf("Koristite: ./a.out ime_ulazne_datoteke.txt granica (realan broj)\n");
        return 1;
    }
    TIM timovi[MAX_TIMOVI];
    TIM sledeci_tim[MAX_TIMOVI];
    int n;
    int nova_duzina;
    FILE* in = safe_fopen(argv[1], "r", EXIT_FAILURE);
    ucitaj_timove(in,timovi, &n);
    sledeci(timovi, sledeci_tim, n, atof(argv[2]), &nova_duzina);
    FILE* out = safe_fopen("rezultati.txt", "w", EXIT_SUCCESS);
    ispisi(out,sledeci_tim, nova_duzina);

    fclose(in);
    fclose(out);
    return 0;
}

FILE* safe_fopen(char* file, char* mode, int err) {
    FILE* fp = fopen(file, mode);
    if(fp == NULL) {
        printf("Greska pri otvaranju fajla: %s\n", file);
        exit(err);
    }
    return fp;
}

void ucitaj_timove(FILE* in, TIM* timovi, int* n) {
    int i=0;
    while((fscanf(in,"%s %s %lf %lf", timovi[i].drzava, timovi[i].hrana, &timovi[i].publika, &timovi[i].ziri))!=EOF){
        
        i++;
    }
    *n = i;
}

void sledeci(TIM* timovi, TIM* sledeci_tim, int n, double granica, int* nova_duzina) {
    int j=0;
    for(int i = 0;i<n;i++){
        if((timovi[i].publika + timovi[i].ziri)>granica){
            sledeci_tim[j] = timovi[i];
            j++;
        }
    }
    *nova_duzina = j;
}

void ispisi(FILE* out, TIM* novi_timovi, int duzina){
    double prosek=0;
    double suma=0;
    for(int i = 0; i<duzina; i++){
        suma += novi_timovi[i].publika + novi_timovi[i].ziri;
        fprintf(out, "%s %s %.2f %.2f\n", novi_timovi[i].drzava, novi_timovi[i].hrana, novi_timovi[i].publika, novi_timovi[i].ziri);
    }
    prosek = suma/(duzina*2);
    fprintf(out, "Prosecna ocena timova koji su prosli u sledeci krug takmicenja je: %.2f\n", prosek);
}