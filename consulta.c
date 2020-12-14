#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

int busca_binaria(char p[8], tpos *ps, int N, int offset)
{
    if(N < 1) return 0;

    int xN = N / 2;

    int x = strcmp(p, ps[xN].placa);

    if(x == 0) return offset + xN + 1;

    else if( x < 0 ) return busca_binaria(p, ps, xN, offset);

    else return busca_binaria(p, ps + xN + 1, N - xN - 1, offset + xN + 1);
}

int main(){
    FILE * arq;
    FILE * arq_base;
    tpos p;
    tcarro c;
    int resultado;
    int achou;
    int i, j;
    char query_placa[8];
    char comando;
    i = 0;
    j = 0;
    achou = 0;
    arq = fopen("index.bin","rb");
    arq_base = fopen("base.bin", "rb");
    tpos *vetor;
    tcarro *retorno;
    tcarro *vetor_base;
    vetor = (tpos *)malloc(sizeof(tpos) * MAX);
    vetor_base = (tcarro *)malloc(sizeof(tcarro) * MAX);
    retorno = (tcarro *)malloc(sizeof(tcarro) * MAX);

    while(!feof(arq)){
        fseek(arq,i*sizeof(tpos),SEEK_SET);
        fread(&p, sizeof(char), sizeof(tpos), arq);
        strcpy(vetor[i].placa, p.placa);
        vetor[i].rrn = i;
        i++;
    }

    while(scanf("%s %s",&comando, query_placa) != EOF){
        resultado = busca_binaria(query_placa, vetor, MAX, 0);
        achou = 1;
        j = 0;

        while(!feof(arq_base)){
            fseek(arq_base,j*sizeof(tcarro),SEEK_SET);
            fread(&c, sizeof(char), sizeof(tcarro), arq_base);
            strcpy(vetor_base[j].placa, c.placa);
            strcpy(vetor_base[j].modelo, c.modelo);
            strcpy(vetor_base[j].marca, c.marca);
            strcpy(vetor_base[j].estado, c.estado);
            vetor_base[j].ano = c.ano;
            // OCD7972
            // NPH7302
            j++;
        }

        for(i = 0; i < MAX; i++){
            if(resultado > 0){
                if(strcmp(vetor[resultado - 1].placa, vetor_base[i].placa) == 0){
                    strcpy(retorno->estado, vetor_base[i].estado);
                    strcpy(retorno->modelo, vetor_base[i].modelo);
                    strcpy(retorno->marca, vetor_base[i].marca);
                    strcpy(retorno->placa, vetor_base[i].placa);
                    retorno->ano = vetor_base[i].ano;
                    achou = 1;
                }
            }else {
                achou = 0;
            }
        }

        if(achou && resultado != 0){
            printf("carro %s %d %s %s %s eh roubado! \n", retorno->placa, retorno->ano, retorno->marca, retorno->modelo, retorno->estado);
        }else {
            printf("carro %s nao consta na lista\n", query_placa);
        }
    }
    
    free(vetor);
    free(vetor_base);
    free(retorno);
    fclose(arq);
    fclose(arq_base);
    return EXIT_SUCCESS;
}