#ifndef PRODUTOSAUX_H
#define PRODUTOSAUX_H

#include<stdio.h>
#include"view.h"

/*estrutura auxiliar do catálogo de produtos*/
typedef struct ProdutosAux* ProdutosAux;

/*funçao inicializaçao da estrutura auxiliar*/
struct ProdutosAux* initProdutosAux(struct ProdutosAux*);

/*funçao de altura da arvore*/
int heightProdutosAux(struct ProdutosAux*);

/*funcao que determina o maior entre dois elementos da arvore*/
int maxProdutosAux(int, int);

/*funçao de criaçao do novo nodo*/
struct ProdutosAux* newProdutosAux(char*);

/*funçoes de rotaçao*/
struct ProdutosAux* rightRotateProdutosAux(struct ProdutosAux*);
struct ProdutosAux* leftRotateProdutosAux(struct ProdutosAux*);

/*funçao de verificaçao do balanço*/
int getBalanceProdutosAux(struct ProdutosAux*);

/*funçao de inserçao na arvore*/
struct ProdutosAux* insertProdutosAux(struct ProdutosAux*, char*);

/*funçao de verificaçao se existe ou não*/
int existsProdutosAux(struct ProdutosAux*,char*);

/*funçao de update da arvore*/
void updateProdutosAux(struct ProdutosAux*,int);

/*funcao que cria ficheiro dos produtos validos*/
void printToFile(struct ProdutosAux*,FILE*);

/*funçao que apaga a arvore*/
void deleteProdutosAux(struct ProdutosAux*);

/*funcao que procura e devolve um nodo da árvore*/
struct ProdutosAux* searchProdutosAux(struct ProdutosAux*,char*);

/* Insert ProdutosAux into List*/
struct view* insertProdutosAuxInList(struct ProdutosAux*, struct view*);

/*função auxiliar para a função que calcula os produtos que nunca foram comprados em produtos.c*/
struct list* neverBoughtProdutosAux(struct ProdutosAux*,struct list*,int*);

/*calculo do número de produtos que nunca foram comprados*/
void neverBoughtNumberProdutosAux(struct ProdutosAux*,int*);

/*função auxiliar para o cálculo de produtos que nunca foram comprados filial a filail em produtos.c*/
struct multiView** naoComprouEmFiliaisAux(struct ProdutosAux*,struct multiView**);

#endif
