#ifndef PRODUTOS_H
#define PRODUTOS_H

#include<stdio.h>
#include"produtosaux.h"
#include"produtosaux.h"
#include "view.h"

/*estrutura dos produtos*/
typedef struct DataItem* Produtos;

/*estrutura da hashTable*/
typedef struct DataItem* Produtos;

/*funçao de inicializaçao da hashTable*/
struct DataItem** initProdutos(struct DataItem**);

/*funçao que realiza o hashing*/
int hashCode(char*);

/*funçao de procura na hashTable*/
Produtos searchProdutos(Produtos*,char*);

/*funçao de verificaçao de existencia*/
Produtos* insertProdutos(Produtos*,char* key);

/*funçao de inserçao na hashTable*/
void printToFileProdutos(Produtos*,FILE*);

/*funçao de criaçao do ficheiro valido*/
int existsProdutos(Produtos*, char*);

/*Devolve aŕvore de produtos começados por uma letra*/
struct view* getProdutosStartingWithProdutos(Produtos*, char*,struct view*);

/*Devolve o produto da árvore de uma posição da hashtable*/
ProdutosAux searchAuxProdutos(Produtos*, char*);

struct list* neverBoughtProdutos(Produtos*,struct list*);

struct list* neverBoughtNumberProdutos(Produtos*,struct list*);

/*funçao de inicializaçao dos produtos*/
Produtos* initPrd(Produtos*);

/*funçao de carregar os produtos */
Produtos* loadP(Produtos*, char*,int*);

struct multiView** naoComprouProduto(Produtos*,struct multiView**);

#endif
