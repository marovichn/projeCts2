#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IME 16
#define MAX_SIZE 50

typedef struct igrac{
char ime[MAX_IME];
int broj_poena;
int broj_skokova;
int broj_asistencija;
int broj_odigranih_utakmica;
double efikasnost;
}IGRAC;

FILE *safe_fopen(char*, char*, int);
void ucitaj_igrace(FILE*, IGRAC*, int*);
void izracunaj_efikasnost(IGRAC*, int);
void sortiraj_obelezi(IGRAC*, int, int);
void ispisi(FILE*, IGRAC*, int);
double prosek(IGRAC*, int);

int main (int argc, char *argv[]) {
    if(argc != 4){
        printf("Primer poziva: ./a.out ime_datoteke.txt ime_igraca broj_poena\n");
        return EXIT_FAILURE;
    }

    IGRAC igraci[MAX_SIZE]; 
    int n;
    FILE* in = safe_fopen(argv[1], "r", EXIT_FAILURE);
    ucitaj_igrace(in, igraci, &n);
    izracunaj_efikasnost(igraci, n);
    int granica = atoi(argv[3]);
    sortiraj_obelezi(igraci, n, granica);
    FILE* out = safe_fopen(argv[2], "w", EXIT_FAILURE);
    ispisi(out, igraci, n);
    double avg = prosek(igraci, n);
    printf("Prosecna efikasnost igraca je: %.2f\n", avg);
    
    fclose(in);
    fclose(out);
    return 0;
}

FILE *safe_fopen(char *filename, char *mode, int exit_code){
    FILE *file = fopen(filename, mode);
    if(file == NULL){
        printf("Greska pri otvaranju fajla: %s\n", filename);
        exit(exit_code);
    }
    return file;
}

void ucitaj_igrace(FILE *in, IGRAC *igraci, int *n){
    int i =0;
    while(fscanf(in, "%s %d %d %d %d", igraci[i].ime, &igraci[i].broj_poena, &igraci[i].broj_skokova, &igraci[i].broj_asistencija, &igraci[i].broj_odigranih_utakmica)!=EOF){
        i++;
    }
    *n = i;
}

void izracunaj_efikasnost(IGRAC *igraci, int n){
    for(int i=0; i<n; i++){
        igraci[i].efikasnost = (double)(igraci[i].broj_poena + igraci[i].broj_skokova + igraci[i].broj_asistencija)/igraci[i].broj_odigranih_utakmica;
    }
}

void sortiraj_obelezi(IGRAC* igraci, int n, int granica){
    int max = 0;
    for(int i=0;i<n;i++){
        if(igraci[i].broj_odigranih_utakmica < granica){
            strcat(igraci[i].ime, "(-)");
        }
        if(igraci[i].efikasnost > igraci[max].efikasnost && igraci[i].broj_odigranih_utakmica > granica){
            max = i;
        }
    }
    strcat(igraci[max].ime, "(*)");
    

    IGRAC temp;
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(igraci[j].efikasnost < igraci[j+1].efikasnost){
                temp = igraci[j];
                igraci[j] = igraci[j+1];
                igraci[j+1] = temp;
            }
        }
    }
 
}

void ispisi(FILE *out, IGRAC *igraci, int n){
    for(int i=0;i<n;i++){
        fprintf(out,"%12s %10d %10d %10d %10d %10.2lf\n", igraci[i].ime, igraci[i].broj_poena, igraci[i].broj_skokova, igraci[i].broj_asistencija, igraci[i].broj_odigranih_utakmica, igraci[i].efikasnost);
    }
}

double prosek(IGRAC* igraci, int n){
    double suma = 0;
    for(int i = 0;i<n;i++){
        suma += igraci[i].efikasnost;
    }
    double prosek = suma/n;
    return prosek;
}