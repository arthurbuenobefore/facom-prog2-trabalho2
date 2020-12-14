#include<stdio.h>
#include <string.h>
#include<stdlib.h>

#define MAX 1000001

typedef struct {
    char opcao[1];
    char placa[20];
    int ano;
    char marca[10];
    char modelo[15];
    char estado[3];
}tcarro;

typedef struct{
    int rrn;
    char placa[8];
}tpos;

void quick_sort(tpos *a, int left, int right) {
        int i, j;
        char x[20];
        char y[20];
        int y_index;
        
        i = left;
        j = right;
        strcpy(x, a[(left + right) / 2].placa);        
    
        while(i <= j) {
            while(strcmp(a[i].placa, x) < 0 && i < right) {
                i++;
            }

            while(strcmp(a[j].placa, x) > 0  && j > left) {
                j--;
            }

            if(i <= j) {
                if(strcmp(a[i].placa, a[j].placa) > 0){
                    strcpy(y, a[i].placa);
                    y_index = a[i].rrn;
                    a[i] = a[j];
                    strcpy(a[j].placa, y);
                    a[j].rrn = y_index;
                }
                i++;
                j--;                
            };
        }
        
        if(j > left) {
            quick_sort(a, left, j);
        }
        if(i < right) {
            quick_sort(a, i, right);
        }
    }

int main(){
    FILE * arq;
    FILE * fout;
    tcarro p;
    int i;
    i = 0;
    arq = fopen("base.bin","rb");
    fout = fopen("index.bin","wb");
    tpos *vetor;
    vetor = (tpos *)malloc(sizeof(tpos) * MAX);
    while(!feof(arq)){
        fseek(arq,i*sizeof(tcarro),SEEK_SET);
        fread(&p, sizeof(char), sizeof(tcarro), arq);
        strcpy(vetor[i].placa, p.placa);
        vetor[i].rrn = i;
        i++;
    }
    quick_sort(vetor, 0, MAX - 1);
    fwrite(vetor, sizeof(char), sizeof(tpos) * MAX, fout);

    free(vetor);
    fclose(arq);
    fclose(fout);
    return EXIT_SUCCESS;
}