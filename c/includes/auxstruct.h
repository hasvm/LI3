#ifndef AUXSTRUCT_H
#define AUXSTRUCT_H

#include "view.h"

/*estruturas auxiliares para as queries 11 e 12*/
typedef struct aux* aux;
typedef struct aux2* aux2;

/*calculo do código hash*/
int hashCodeAll(char*);

/*inicialização da estrutura*/
struct aux** initAux(struct aux**,int);
 
/*criação de um elemento*/
struct aux* newAux(char* ,int, int);

/*calculo do tamanho do array/hashtable*/
int getSize(struct aux** ret,int n,int k);

/*insere os elementos de um venda*/
struct aux** insertAll(struct aux**,char*,int,int);

/* construi os n máximos elementos na estrutura auxiliar limitando n por cada filial*/
struct aux** buildNMax(struct aux**,int,int,struct aux*);

/*adiciona a estrutura a uma view*/
struct list* addAuxToList(struct list*,struct aux**,int,int);

/*destroi a estrutura*/
void destroyAux(struct aux**,int);

/*esvazia os elementos da estrutura*/
void emptyAux(struct aux**,int);

/*insere os elementos de um venda*/
struct aux2** insertAll2(struct aux2**,char*,float);

/*hash function*/
int hashCodeAll2(char*);

/*inicialização da estrutura*/
struct aux2** initAux2(struct aux2**,int);

/*criacao de um nodo*/
struct aux2* newAux2(char*, float);

/* construi os n máximos elementos na estrutura auxiliar limitando n por cada filial*/
struct aux2** buildNMax2(struct aux2**,int,int,struct aux2*);

/*calculo do tamanho do array/hashtable*/
int getSize2(struct aux2**,int,int);

/*adiciona a estrutura a uma view*/
struct list* addAuxToList2(struct list*,struct aux2**,int, int);

/*destroi a estrutura*/
void destroyAux2(struct aux2**,int);

#endif
