#include <stdio.h>

int max(int a, int b);
void add_one(int a[], int b);

int main (int argc, char **args) {
    int a[20];
    for(int i = 0; i < 20; i++){
        a[i] = i + 1;
    }
    add_one(a, 20);
    for (int i = 0; i < 20; i++)
    {
    printf("%d\n", a[i]);
    }
    

    return 0;
}

int max(int a,int b){
    if (a > b)
        return a;
    else
        return b;
}

void add_one(int a[], int b){
    for(int i =0; i < b; i++){
        a[i] += + 10;
    }
}