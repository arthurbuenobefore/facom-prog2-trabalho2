#include<stdio.h>
#include<stdlib.h>

typedef struct {
    char opcao[1];
    char placa[20];
    int ano;
    char marca[10];
    char modelo[15];
    char estado[3];
}tcarro;
//fprintf e fscanf pra texto
// fread e fwrite ler e escrever
int main(void){
    FILE * arq;
    FILE * fout;
    tcarro c;
    arq = fopen("base.txt","r");
    fout = fopen("base.bin","wb");
    while(!feof(arq)){
        fscanf(arq,"%s  %s %d %s %s %s ",c.opcao, c.placa, &c.ano, c.marca, c.modelo, c.estado);
        fwrite(&c, sizeof(char), sizeof(tcarro), fout);
    }
    fclose(arq);
    fclose(fout);
    return EXIT_SUCCESS;
}