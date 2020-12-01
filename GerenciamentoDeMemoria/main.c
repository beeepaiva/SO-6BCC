#include <stdio.h>
#include <string.h>
#include <stddef.h>

char memoria[50*1024*1024]; 

typedef struct area {
  int livre; 
  size_t tam;
  struct area *prox; 
} _area;

_area *areaMemoria = (void *)memoria;

void iniciaMemoria() {
    areaMemoria->livre = 1;
    areaMemoria->tam = sizeof(memoria) - sizeof(_area);
    areaMemoria->prox = NULL;
}

void *aloca(size_t qtdBytes) {
    
    _area *posAtual;
    posAtual = areaMemoria;
    while((posAtual->tam < qtdBytes || posAtual->livre == 0) && posAtual->prox != NULL) { 
        posAtual = posAtual->prox;
    }

    if(posAtual->tam == qtdBytes) {
        posAtual->livre = 0;
        void *posicao = ++posAtual;
        printf("Alocada na posição: '%p'\n", posicao);
        return posicao;

    } else if(posAtual->tam > qtdBytes) { 

        _area *novaArea = (void *)(posAtual + sizeof(_area) + qtdBytes); 
        novaArea->livre = 1;
        novaArea->tam = posAtual->tam - sizeof(_area) - qtdBytes;
        novaArea->prox = posAtual->prox; 
        posAtual->livre = 0; 
        posAtual->tam = qtdBytes + sizeof(_area); 
        posAtual->prox = novaArea; 
        void *posicao = ++posAtual; 
        printf("Alocada na posição: '%p'\n", posicao);
        return posicao;

    } else {
        printf("Sem memoria para alocar\n");
        return NULL;
    }
}

void libera(void *p) {
    if(p >= (void *) memoria && p <= (void *) (memoria + sizeof(memoria))) {
        _area *posAtual = p;
        printf("Liberada na posição: '%p'\n", (void *)posAtual);
        posAtual--; 
        posAtual->livre = 1; 
    } else {
        printf("Null\n");
    }
}

void mostraArea() {

    printf("\n");
    _area *section = areaMemoria;
    int counter = 1;
    while (section != NULL) {
        printf("Area %d tem tamanho: %lu (livre: %d)\n", counter, section->tam, section->livre);
        section = section->prox;
        counter++;
    }
}

int main(void) {

    iniciaMemoria();

    int *p = (int *) aloca(sizeof(int));
    mostraArea();
    *p = 500;

    char *q = (char *) aloca(1024);
    mostraArea();
    strcpy(q, "Armazenando");

    printf("\nEndereço de p: '%p'\n", (void *)p);
    printf("Endereço de q: '%p'\n\n", (void *)q);

    libera(q);
    libera(p);
}

