#ifndef CLIENTES_H
#define CLIENTES_H

#include<stdio.h>
#include"view.h"

/*estrutura da arvore*/
typedef struct Node* Clientes;

/*funçao de altura da arvore*/
int heightClientes(struct Node*);

/*funcao que determina o maior entre dois elementos da arvore*/
int maxClientes(int, int);

/*funçao de criaçao do novo nodo*/
struct Node* newNodeClientes(char*);

/*funçoes de rotaçao*/
struct Node* rightRotateClientes(struct Node*);
struct Node* leftRotateClientes(struct Node*);

/*funçao de verificaçao do balanço*/
int getBalanceClientes(struct Node*);

/*funçao de inserçao na arvore*/
struct Node* insertClientes(struct Node*, char*);

/*funçao de verificaçao se existe ou não*/
int existsClientes(struct Node*,char*);

/*funçao de update da arvore*/
void updateClientes(struct Node*,int);

/*funcao que cria do ficheiro valido*/
void printToFileClientes(struct Node*,FILE*);

/*funçao que apaga a arvore*/
void deleteClientes(struct Node*);

/*funcao que procura e devolve um nodo da árvore*/
struct Node* searchClt(struct Node*,char*);

/*funçao que insere clientes numa lista ordenada*/
struct list* insertClientesInList(struct Node*, struct list*);

/*devolve os clientes numa lista ordenada que nunca compraram isto de ve ser dos produtos*/
struct list* neverBoughtClientes(struct Node*,struct list*,int*);

/*calcula o número de clientes que nunca compraram*/
void neverBoughtNumberClientes(struct Node*,struct list*,int*);

/*devolve a lista ordenada dos clientes que compraram em todas as filiais*/
struct view* compraramEmFiliais(struct Node*, struct view*,int*);

/*funçao auxiliar para o cálculo dos clientes que compraram em todas as filiais*/
int comprouEmTodas(struct Node*);

/*funçao de inicializaçao dos clientes*/
Clientes initClt(Clientes);

/*funçao que carrega os clientes*/
Clientes loadC(Clientes, char*,int*);

#endif
