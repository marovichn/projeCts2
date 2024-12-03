#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ULICA 21
#define MAX_TIP 11
#define MAX_KVAR 3
#define MAX_OBJEKTI 50

typedef struct{
    char ulica[MAX_ULICA];
    unsigned int broj_ulice;
    unsigned int broj_dom;
    char tip[MAX_TIP];
    char kvar[MAX_KVAR];
}OBJEKAT;

FILE* safe_fopen(char*, char*, int);
void ucitaj_podatke(FILE*, OBJEKAT*, int*);
void kvar(OBJEKAT*,OBJEKAT*,int, unsigned int*, int*);
void ispisi_kvarove(FILE*, OBJEKAT*, int, int, int);

int main (int argc, char *argv[]) {
    if(argc != 4){
        printf("Koristite: ./a.out broj ulazni_podaci.txt izlazna_datoteka.txt\n", argv[0]);
        return EXIT_FAILURE;
    }
    int n;
    OBJEKAT objekti[MAX_OBJEKTI];
    OBJEKAT objekti_kvar[MAX_OBJEKTI] = {0};
    unsigned int dom_u_kvaru;
    int broj_objekata;

    FILE* in = safe_fopen(argv[2], "r", 3);
    ucitaj_podatke(in, objekti, &n);
    kvar(objekti, objekti_kvar, n, &dom_u_kvaru, &broj_objekata);
    FILE* out = safe_fopen(argv[3], "w", 4);
    ispisi_kvarove(out, objekti_kvar, broj_objekata, dom_u_kvaru, atoi(argv[1]));

    fclose(in);
    fclose(out);
    return 0;
}

FILE* safe_fopen(char* filename, char* mod, int err){
FILE* f = fopen(filename,mod);
    if(f == NULL){
        printf("Greska pri otvaranju fajla: %s\n", filename);
        exit(err);
    }
    return f;
}

void ucitaj_podatke(FILE* in, OBJEKAT* objekti, int* n){
    int i=0;
    while(fscanf(in, "%s %u %u %s %s",objekti[i].ulica, &objekti[i].broj_ulice, &objekti[i].broj_dom, objekti[i].tip, objekti[i].kvar)!=EOF){
        i++;
    };

    *n = i;
}

void kvar(OBJEKAT* objekti, OBJEKAT* objekti_kvar, int n,unsigned int* dom_u_kvaru, int* broj_objekata){
    unsigned int domacinstva= 0;
    int duzina_kvar=0;
    int j=0;
    for(int i = 0; i < n; i++){
        if(strcmp(objekti[i].kvar, "DA")==0){
            strcpy(objekti_kvar[j].ulica,objekti[i].ulica);
            objekti_kvar[j].broj_ulice = objekti[i].broj_ulice;
            strcpy(objekti_kvar[j].tip,objekti[i].tip);
            strcpy(objekti_kvar[j].kvar,objekti[i].kvar);
            domacinstva += objekti[i].broj_dom;
            duzina_kvar++;
            j++;
        }
    }
    *dom_u_kvaru = domacinstva;
    *broj_objekata=duzina_kvar;
}

void ispisi_kvarove(FILE* out, OBJEKAT* objekti_kvar, int broj_objekata, int broj_domacinstava, int provera) {
    for(int i = 0; i < broj_objekata; i++) {
        fprintf(out, "%s %u %s\n", objekti_kvar[i].ulica, objekti_kvar[i].broj_ulice, objekti_kvar[i].tip);
    }
    fprintf(out, "\nBroj domacinstava bez struje: %d\n", broj_domacinstava);
    if(broj_objekata > provera) {
        fprintf(out, "\nMoguc kvar trafo stanice!\n");
    }
}

