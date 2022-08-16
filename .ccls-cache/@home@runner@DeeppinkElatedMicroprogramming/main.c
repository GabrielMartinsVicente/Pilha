// Trabalho-2-pilhas
/* Medir  o  tempo  para  inserção  de  1.000.000  milhão  de  inteiros  em  uma  estrutura  de  dados  e  o  tempo  para  percorrer  e  somar  1.000.000  
de  inteiros  em  uma  determinada  estrutura de dados, e o tempo para garantir que um determinado inteiro já está na pilha. 
Finalmente  você deverá medir estes tempos percorrendo a pilha em dois sentidos. De cima para baixo e de baixo  para cima. */

#include <stdio.h>
#include <time.h>   //clock_t
#include <stdlib.h> //função malloc
#include<stdbool.h> //função bool

struct Pilha{ //criação da estrutura de memória, onde vai conter informações importantes da minha pilha

  int topo;
  int tamanho;  //Tamanho de alocação
  int *pNumero; //O atributo *pNumero é um ponteiro onde aponta para o espaço reservado na memória RAM da pilha

};

void criar_Pilha(struct Pilha *p, int tamanho){ //Método construtor da pilha
  
  p->topo = -1; //topo = -1, pois a pilha esta "vazia" (pode conter lixo) na memória
  p->tamanho = tamanho;
  p->pNumero = (int*)malloc(tamanho*(sizeof(int))); /*Memory Allocation, a função malloc recebe como parâmetro o número de bytes
                                                    que irá alocar na memória (por isso o: "sizeof(int)""), porém como esta função retorna o 
                                                    endereço do bloco de memória, é necessário fazer um cast: (int*) para que um ponteiro de mesmo tipo 
                                                    receba esse endereço. */
  
  if(p->pNumero == NULL){
      printf("A alocação na memoria não funcionou, nao exite espaço na memória");
  }
  
};

bool estaVazia(struct Pilha *p){

  if(p->topo < -1){                  
                              
      return true;            //return 1 == true (pilha esta vazia)       
                              //return 0 == false (pilha não esta vazia)
  }
    
  else{return false;}

}

bool estaCheia(struct Pilha *p){

  if(p->topo > p->tamanho-1){                  
                                
        return true;            //return 1 == true (pilha esta cheia)       
                                //return 0 == false (pilha não esta cheia)
    }
    
  else{return false;}

}

void empilhar(struct Pilha *p, int valor){

  if(estaCheia(p) == false ){  //Verifica se a pilha esta cheia para empilhar

    p->topo++;
    p->pNumero [p->topo] = valor;

  }

    if(estaCheia(p) == true){

      printf("\nNao e possivel alocar um novo numero na pilha, pois esta cheia\n");

  }

}

void desempilhar(struct Pilha *p){

  if(estaVazia(p) == false){ //Verifica se a pilha esta vazia

    p->topo--; /*A remoção de um elemento da pilha é realizada apenas alterando a     
               informação da posição do topo. */

  }

  if(estaVazia(p) == true){

    printf("\nA pilha ja esta vazia\n");

  }

}

int buscarValor(struct Pilha *p, int posicao){ /*Método me retorna o número na posição desejada,
                                                 facilitando assim minha busca dos valores                                                                     pelo índice*/

  if(estaVazia(p) == true){            //Verifica se a pilha esta vazia, porque não existe valor para ser retornado
    printf("\nA pilha esta vazia\n");
    return 0;
  }
  else{return p->pNumero[posicao-1];} 
  
}

int main()
{    

  struct Pilha pilha;
  int tamanho, amostra;  //amostra é a variável de controle para a repetição das instruções
  double populacao[50];  //populacao é apenas o total operações de cada tipo
  clock_t tempo;
  double soma = 0; 
  
	printf( "\nQual o tamanho de locacao da pilha? " );
	scanf( "%i", &tamanho );

  criar_Pilha(&pilha,tamanho);

  //------------------- 1°: Tempo de inserção ----------------------------
  
  amostra = 0;
  while(amostra<50){
  
    tempo = clock();
  
    for(int i = 1;i<=tamanho;i++){
      
      empilhar(&pilha,i);
      
    }
  
    tempo = clock() - tempo;

    populacao[amostra] = ((double)tempo)/CLOCKS_PER_SEC;

    for(int i = 1;i<=tamanho;i++){ //Foi necessário desempilhar totalmente a pilha para depois repetir o processo
      
      desempilhar(&pilha);
      
    }
    
    amostra++;

    }

  soma = 0;
  for(int i = 0;i<50;i++){  //Somatório de todos os tempos para depois fazer a média
    soma += populacao[i];
  }

  printf("\nTempo para inserir: %fs\n\n",(double)((soma)/50));

  //------------------- 2°: Tempo para percorrer e somar ----------------------------

  amostra = 0;
  while(amostra<50){

    soma = 0;

    tempo = clock();
    
    for(int i = 1;i<=tamanho;i++){
      
      soma += buscarValor(&pilha,i);
      
    }

    tempo = clock() - tempo;

    populacao[amostra] = ((double)tempo)/CLOCKS_PER_SEC;

    amostra++;

  }

  soma = 0;
  for(int i = 0;i<50;i++){
    soma += populacao[i];
  }

  printf("\nTempo para percorrer e somar: %fs\n\n",(double)((soma)/50));


  //------------------- 3°: Tempo de busca ----------------------------

  amostra = 0;
  while(amostra<50){
  
    tempo = clock();
  
    for(int i = 1;i<=tamanho;i++){
      
      if(buscarValor(&pilha,i) != i){
        printf("\nO inteiro: %i nao esta na pilha",i);
        }
    }

    for(int i = tamanho;i>0;i--){
      
      if(buscarValor(&pilha,i) != i){
        printf("\nO inteiro: %i nao esta na pilha",i);
        }
    }
  
    tempo = clock() - tempo;

    populacao[amostra] = ((double)tempo)/CLOCKS_PER_SEC;
    
    amostra++;

    }
  
  soma = 0;
  for(int i = 0;i<50;i++){
    soma += populacao[i];
  }

  printf("\nTempo para verificar: %fs\n\n",(double)((soma)/50));

  return 0;
}