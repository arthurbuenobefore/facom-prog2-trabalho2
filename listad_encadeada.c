
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>


#define SUCCESS 1
#define ERROR_MEMORY_FULL 2
#define ERROR_INVALID_POSITION 3
#define MAX 1000001


typedef int ttipo;

typedef struct {
    char opcao[1];
    char placa[20];
    int ano;
    char marca[10];
    char modelo[15];
    char estado[3];
}tcarro;

typedef struct _node{
    tcarro * carro;
    struct _node *proximo;
    struct _node *anterior;
}tnode;

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

tcarro* busca_estrutura(char query_placa[8]){
    FILE * arq;
    FILE * arq_base;
    tpos p;
    tcarro c;
    int resultado;
    int achou;
    int i, j;
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

    if(achou && resultado != 0)
        return retorno;
    
    
    free(vetor);
    free(vetor_base);
    free(retorno);
    fclose(arq);
    fclose(arq_base);
}

void listad_cria(tnode ** lista){
    *lista = NULL;
}

int listad_insere_n(tnode ** lista, int pos, tcarro * val){
    int ret = SUCCESS;
    tnode * novo;
    tnode * atual;
    int i;

    novo = (tnode *)malloc(sizeof(tnode));
    if (novo == NULL){
        ret = ERROR_MEMORY_FULL; 
    }else{
        novo->carro = val; 
        if (*lista == NULL){
            novo->proximo = NULL;
            novo->anterior = NULL;
            *lista = novo;
        }else if (pos == 0){
            novo->proximo = NULL;
            novo->anterior = *lista;
            (*lista)->proximo = novo;
            *lista = novo;
        }else{
            atual = *lista;
            pos--;
            i = 0;
            while(atual->anterior != NULL){
                if (i < pos){
                    atual = atual->anterior;
                    i++;
                }else{
                    break;
                }
            }
            if (i!=pos){ /* posicao incorreta*/
                ret = ERROR_INVALID_POSITION;
            }else{
                /*insercao a direita*/
                novo->proximo = atual;
                novo->anterior = atual->anterior;
                if (atual->anterior != NULL) atual->anterior->proximo = novo;
                atual->anterior = novo;
            }
        }
    }
    return ret;
}

int listad_remove_n(tnode ** lista, int pos){
    int ret = SUCCESS;
    int i;
    tnode *atual;
    atual = *lista;
    if (*lista == NULL){
        ret = ERROR_INVALID_POSITION;
    }else{
        if ((atual->anterior == NULL) && (atual->proximo == NULL) && pos == 0){ /*tem somente um node*/
            free(atual);
            *lista = NULL;
        }else{ /* tem pelos menos um node */ 
            i = 0;
            while(atual->anterior != NULL){
                if (i < pos){
                    atual = atual->anterior;
                    i++;
                }else
                    break;
            }
            if (i != pos){ /* nao chegou na posicao correta */
                ret = ERROR_INVALID_POSITION;
            }else{
                if (atual->proximo != NULL) atual->proximo->anterior = atual->anterior;
                if (atual->anterior != NULL) atual->anterior->proximo = atual->proximo;
                if (pos == 0) *lista = atual->anterior;
                free(atual);
            }
        }
    }
    return ret;
     
}

tcarro* busca (tnode *l, char placa[20]) {
    tnode * p;
    for (p = l; p != NULL; p = p->proximo)
        if (strcmp(p->carro->placa, placa))
            return p->carro;
}

int main(void){
    tcarro carro;
    tcarro * carro_encontrado;
    tnode * lista;
    char type;
    int i = 0;
    char placa[20];
    int ano;
    char marca[10];
    char modelo[15];
    char estado[3];
    listad_cria(&lista);

    while(scanf("%c", &type) != EOF){
        scanf("%s ", placa);
        switch (type) {
            case 114:
                scanf("%d %s %s %s", &ano, marca, modelo, estado);
                carro.ano = ano;
                strcpy(carro.estado, estado);
                strcpy(carro.marca, marca);
                strcpy(carro.modelo, modelo);
                strcpy(carro.placa, placa);
                listad_insere_n(&lista, i, &carro);
                printf("carro %s %d %s %s %s foi roubado! \n", carro.placa, carro.ano, carro.marca, carro.modelo, carro.estado);
                break;
            case 99:
                //carro_encontrado = busca_estrutura(placa);
                //carro_encontrado = busca(&lista, placa);
                //printf("%s\n",  carro_encontrado->placa);
                // if(listad_remove_n(&lista, i)){
                //     printf("carro %s %d %s %s %s foi roubado! \n", carro.placa, carro.ano, carro.marca, carro.modelo, carro.estado);
                // }else {
                //     printf("carro %s nao consta na lista\n", placa);
                // }
                break;
        }
        i++;
    }
    
    free(lista);

    return EXIT_SUCCESS;
}

