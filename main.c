/*Desenvolva um programa, em Linguagem C, que seja capaz de ler uma lista de nomes 
digitados pelo usuário da aplicação e os inclua em uma lista encadeada criada dinamicamente. 
Ao final da digitação do usuário, este nomes devem ser apresentados na 
ordem inversa em que foram digitados.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct N{
  char* nome;
  struct N* prox;
  struct N* ant;
} No;

void inverte(No* final){
  No* var;
  var = final;

  printf("\nInvertendo: \n");

  while(var != NULL){
    printf("Nome: %s\n", var->nome);
    var=var->ant;
  }
}

int main(){
  No* primeiro = NULL;
  No* final = NULL;
  No* no;

  while(1){
    char *var;
    var = malloc(20);
    
    printf("Digite o nome ou 0 para encerrar o programa: ");
    scanf("%s", var);

    if (strncmp(var, "0", 20) == 0){
      inverte(final);
      return 0;
    } 

    no = (No*)malloc(sizeof(No));
    no->nome = var;
    no->ant = final;
    no->prox = NULL;

    if (primeiro == NULL) 
      primeiro = no; 
    else 
      final->prox = no;
    final = no;
  }
}
