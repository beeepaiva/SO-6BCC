// Beatriz Paiva - BCC
// Referencias http://mtm.ufsc.br/~azeredo/cursoC/aulas/c960.html

// gcc -pthread -o contador contador.c
// ./contador arquivo1.txt arquivo2.txt arquivo3.txt

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *contador(char *arq){
    FILE *f;
    f = fopen(arq, "r");

    char carac;
    int qtdPalavras=0;

    //forma de se verificar se o final do arquivo foi atingido: comparar o caractere lido por fgetc com EOF. 
    while((carac=fgetc(f)) != EOF ){
    //Verificar char a char se é um espaço ou uma letra e incrementar o contador quando ating um espaço.
        if(carac==' ' || carac=='\n' )
            qtdPalavras++;
    }

    printf("%s : %d palavras \n", arq, qtdPalavras);

    fclose(f);
    return NULL;
}


int main(int argc, char *argv[]) {
    pthread_t t[argc - 1];

    for (int i = 1; i < argc; i++) {
        pthread_create(&t[i - 1], NULL, (void *)contador, argv[i]);
    }

    for(int i = 0; i < argc; i++) {
        pthread_join(t[i], NULL);
    }

    return 0;
}