#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_TACKE 100
#define MAX_DATOTEKA 100

typedef struct {
    double x;
    double y;
}TACKA;

FILE* safe_fopen(char*, char*, int);
void ucitaj_tacke(FILE*, TACKA*, int*);
void tezisna(TACKA*, double*, double*, int);
void pripada(TACKA*, double, double, double, int, TACKA*, int*);
void ispisi_tacke(FILE*, TACKA*,int);
void trouglovi(FILE*, TACKA*, int);
double udaljenost(TACKA t1, TACKA t2);


int main (int argc, char *argv[]) {
    if(argc < 2 || atof(argv[1]) < 0 || isnan(atof(argv[1]))) {

        printf("Nedostaje argument (ili je neispravan) poluprecnik kruga.\n");
        printf("Poziv treba da izgleda ovako: ./a.exe 5 (poluprecnik)\n");
        return 1;
    }

    char *endptr;
    double p = strtod(argv[1], &endptr);

    // Proverite da li je konverzija uspešna
    if (endptr == argv[1] || *endptr != '\0' || p < 0 || isnan(p)) {
        printf("Nedostaje argument (ili je neispravan) poluprecnik kruga.\n");
        printf("Poziv treba da izgleda ovako: ./a.exe 5 (poluprecnik)\n");
        return 1;
    }
    TACKA tacke[MAX_TACKE], pripadaju[MAX_TACKE];
    int broj_tacka = 0;
    double xt, yt;
    int n, np;
    double poluprecnik= atof(argv[1]);
    char izlazna_datoteka[MAX_DATOTEKA];
    strcpy(izlazna_datoteka, "pripada_krugu_poluprecnika_");
    strcat(izlazna_datoteka, argv[1]);
    strcat(izlazna_datoteka, ".txt");

    FILE* in = safe_fopen("ne_trougao.txt", "r", EXIT_FAILURE);
    FILE* out1 = safe_fopen(izlazna_datoteka, "w", EXIT_FAILURE);
    FILE* out2 = safe_fopen("trouglovi.txt", "w", EXIT_FAILURE);
    ucitaj_tacke(in, tacke, &n);
    tezisna(tacke, &xt, &yt, n);
    pripada(tacke,xt,yt,poluprecnik,n, pripadaju, &np);
    fprintf(out1, "Krug poluprecnika %.2lf sa centrom u tacki (%.2lf, %.2lf):\n", poluprecnik, xt, yt);
    ispisi_tacke(out1, pripadaju, np);
    trouglovi(out2,tacke,n);


    fclose(in);
    fclose(out1);
    fclose(out2);
    return 0;
}

FILE*  safe_fopen(char* in, char* pmode, int err_code){
    FILE *fp = fopen(in, pmode);
    if(fp == NULL){
        printf("Datoteka sa imenom %s nije uspesno otvorena.\n", in);
        exit(err_code);
    }
    return fp;
}

void ucitaj_tacke(FILE* in, TACKA* tacke, int* n){
    int i =0;
    while((fscanf(in, "%lf %lf", &tacke[i].x,&tacke[i].y))!=EOF){
        i++;
    }
    *n = i;
}

void tezisna(TACKA* tacke, double* xt, double* yt, int n){
    double suma_x = 0;
    double suma_y = 0;
    for(int i = 0; i<n; i++){
        suma_x += tacke[i].x;
        suma_y += tacke[i].y;
    }
    *xt = suma_x / n;
    *yt = suma_y / n;
}

void pripada(TACKA* tacke, double xt, double yt, double poluprecnik, int n, TACKA* pripadaju, int* np){
    int j=0;
    for(int i = 0; i<n; i++){
        double r = sqrt((tacke[i].x-xt)*(tacke[i].x-xt) + (tacke[i].y-yt)*(tacke[i].y-yt));
        if(r < poluprecnik){
            pripadaju[j].x=tacke[i].x;
            pripadaju[j].y=tacke[i].y;
            j++;
        }
    }
    *np = j;
}

void ispisi_tacke(FILE* out, TACKA* tacke, int n){
    for(int i=0; i<n; i++){
    fprintf(out, "(%.2f, %.2f)\n", tacke[i].x, tacke[i].y);
    }
}

void trouglovi(FILE* out, TACKA* tacke, int n){
    int broj_trouglova = 0;
    for(int i = 0;i<n;i++){
        for(int j=i+1;j<n;j++){
            for(int k=j+1;k<n;k++){
                double a = udaljenost(tacke[i], tacke[j]);
                double b = udaljenost(tacke[j], tacke[k]);
                double c = udaljenost(tacke[i], tacke[k]);
                if((a + b > c) && (b + c > a) && (c + a > b)){
                    broj_trouglova++;
                }
        }
    }
}
fprintf(out, "Broj trouglova: %d\n", broj_trouglova);
}

double udaljenost(TACKA t1, TACKA t2) {
    return sqrt(pow(t1.x - t2.x, 2) + pow(t1.y - t2.y, 2));
}