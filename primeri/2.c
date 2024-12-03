#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100
#define MAX_DATOTEKA 200

typedef struct {
    double x;
    double y;
    double z;
    double ro;
}TACKA;

FILE* safe_fopen(char*, char*, int);
void ucitaj_tacke(FILE*, TACKA*, int*);
void izracunaj_rastojanje(TACKA*, TACKA, int);
void ispisi_tacke(FILE*, TACKA*, int);
double min_max_rastojanje(TACKA*, int);
void ispisi_zapremine(FILE*,double, double, double);


int main (int argc, char *argv[]) {
    if(argc!=3){
        printf("Koristite: %s ime_izlazne_datoteke.txt a (stranica)\n", argv[0]);
        return 1;
    }

    TACKA tacke[MAX_SIZE];
    TACKA centar;
    centar.x = 0.00;
    centar.y = 0.00;
    centar.z = 0.00;
    int n;
    
    FILE* in = safe_fopen("tacke.txt", "r", EXIT_FAILURE);
    ucitaj_tacke(in, tacke, &n);
    izracunaj_rastojanje(tacke, centar, n);
    FILE* out = safe_fopen(argv[1], "w", EXIT_FAILURE);
    ispisi_tacke(out, tacke, n);
    double zapremina = min_max_rastojanje(tacke, n);
    double argument_stranica = atof(argv[2]);
    double zapremina_argument = pow(argument_stranica, 3);
    double razlika;
    if(zapremina > zapremina_argument){
        razlika = zapremina - zapremina_argument;
    }else{
        razlika = zapremina_argument - zapremina;
    }
    char izlazna_datoteka[MAX_SIZE];
    strcpy(izlazna_datoteka, "sracunata_kocka_minus_");
    strcat(izlazna_datoteka, argv[2]);
    strcat(izlazna_datoteka, "_kocka.txt");
    FILE* out2 = safe_fopen(izlazna_datoteka,"w",EXIT_FAILURE);
    ispisi_zapremine(out2,zapremina, zapremina_argument, razlika);

    return 0;
}

FILE* safe_fopen(char* filename, char* mode, int err) {
    FILE* file = fopen(filename, mode);
    if (file == NULL) {
        printf("Greska pri otvaranju fajla: %s\n", filename);
            exit(err);
    }
    return file;
}

void ucitaj_tacke(FILE* in, TACKA* tacke, int* broj_tacka) {
    int i = 0;
    while(fscanf(in,"%lf %lf %lf", &tacke[i].x, &tacke[i].y, &tacke[i].z)!=EOF){
        i++;
    }
    *broj_tacka = i;
}

void izracunaj_rastojanje(TACKA* tacke, TACKA centar, int n) {
    for(int i=0; i<n;i++){
        tacke[i].ro = sqrt(pow(tacke[i].x - centar.x, 2)+ pow(tacke[i].y - centar.y,2)+pow(tacke[i].z - centar.z,2));
    }
}

void ispisi_tacke(FILE* out, TACKA* tacke, int n) {
    for(int i=0;i<n;i++){
        fprintf(out, "(%.2lf, %.2lf, %.2lf), %.2lf\n", tacke[i].x, tacke[i].y, tacke[i].z, tacke[i].ro);
    }
}

double min_max_rastojanje(TACKA* tacke, int n){
    TACKA min, max;
    min.x = min.y = min.z = max.x = max.y = max.z = 0.00;
    double min_rast = tacke[0].ro;
    double max_rast = tacke[0].ro;
    for(int i=0;i<n;i++){
        if(tacke[i].ro < min_rast){
            min_rast = tacke[i].ro;
            min = tacke[i];
        }else{
            min = tacke[0];
        }
        if(tacke[i].ro > max_rast){
            max_rast = tacke[i].ro;
            max = tacke[i];
        }
    }
    double stranica =  sqrt(pow(max.x - min.x, 2)+ pow(max.y - min.y,2)+
    pow(max.z - min.z,2));
    double zapremina =pow(stranica,3);
    return zapremina;
}


void ispisi_zapremine(FILE* out,double zapremina, double zapremina_argument, double razlika){
    fprintf(out,"Zapremina sracunate kocke: %.2lf\n", zapremina);
    fprintf(out,"Zapremina argument kocke:  %.2lf\n", zapremina_argument); 
    fprintf(out,"Razlika u zapreminama:     %.2lf\n", razlika);
}