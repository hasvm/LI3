#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auxstruct.h"

#define SIZE 500000
#define SIZE2 50000

/*estruturas auxiliares para as queries 11 e 12*/
struct aux {
   int total;
   int clientes;
   char* key;
};

struct aux2{
   char* key;
   float total;
};

/*calculo do código hash*/
int hashCodeAll(char *str)
{
    unsigned long hash = 9;
    int c;

    while ((c = *str++))
        hash = ((hash << 6) + hash) + c; 

    return (hash%SIZE);
}

/*insere os elementos na venda*/
struct aux** insertAll(struct aux** hashArray,char* key,int clientes,int total) {
   struct aux* item = (struct aux*) malloc(sizeof(struct aux));
    
   int hashIndex = hashCodeAll(key);


   while((*(hashArray + hashIndex)) != NULL && (*(hashArray + hashIndex))->key != NULL && strcmp((*(hashArray + hashIndex))->key,key)!=0) {

      ++hashIndex;

      hashIndex %= SIZE;
   }

   if((*(hashArray + hashIndex))==NULL){
	item->key = strdup(key);
	item->total = total;
	item->clientes = clientes;
	(*(hashArray + hashIndex)) = item;
   }
   else {
	(*(hashArray + hashIndex))->total += total;
	(*(hashArray + hashIndex))->clientes +=clientes;
   }
	return hashArray;
}

/*inicialização da estrutura*/
struct aux** initAux(struct aux** ht,int n){
    int i;
    for(i=0;i<n;i++){
	(*(ht + i)) = NULL;
    }
	return ht;
}

/*criação de um elemento*/
struct aux* newAux(char* key,int clientes, int total){
	struct aux* aux = malloc(sizeof(struct aux));
	aux->total = total;
	aux->clientes = clientes;
	aux->key = strdup(key);
	return aux;
}

/* construi os n máximos elementos na estrutura auxiliar limitando n por cada filial*/
struct aux** buildNMax(struct aux** ret,int n,int k,struct aux* aux){
	int i,j,size;

	size = getSize(ret,n,k);

	if(size == 0){
		*(ret+n*k) = newAux(aux->key,aux->clientes,aux->total);
		return ret;
	}
	if(size>=n) size = n;

	for(i=k*n;i<size+k*n && (*(ret+i))->total > aux->total;i++){}

	if(i==n+k*n)
		return ret;

	if(size==n) size--;

	for(j=size+k*n;j>i;j--){
		*(ret+j) = *(ret + j-1);
	}

	*(ret + j) = newAux(aux->key,aux->clientes,aux->total);
	return ret;
}

/*calculo do tamanho do array/hashtable*/
int getSize(struct aux** ret,int n,int k){
	int i;
	for(i = n*k; (*(ret+i)) !=NULL;i++){}
	i-=n*k;
	return i;
}

/*adiciona a estrutura a uma view*/
/*remover o k uma vez que é apenas n*/
struct list* addAuxToList(struct list* list,struct aux** ret,int n, int k){
	int i;
	list = addToList(list,"Filial: 1");
	int x=n;
	int s=2;
	for(i=0;i<n*k;i++){
		if(i==x){
			list = stringBuilderStrInt("Filial: ",&s,list);
			s++;
			x+=n;
		}
		if((*(ret+i))!=NULL){
			list = stringBuilderStrIntInt((*(ret+i))->key,&((*(ret+i))->total),&((*(ret+i))->clientes),list);
		}else list = addToList(list,"Não tem mais clientes");
	}
	return list;
}

/*destroi a estrutura*/
void destroyAux(struct aux** aux,int n){
	int i;
	for(i=0;i<n;i++)
		free(*(aux+i));
}

/*esvazia os elementos da estrutura*/
void emptyAux(struct aux** aux,int n){
	int i;
	for(i=0;i<n;i++)
		*(aux+i) = NULL;
}


int hashCodeAll2(char *str)
{
    unsigned long hash = 9;
    int c;

    while ((c = *str++))
        hash = ((hash << 6) + hash) + c; 

    return (hash%SIZE2);
}

/*insere os elementos de uma venda*/
struct aux2** insertAll2(struct aux2** hashArray,char* key,float total) {
   struct aux2* item = (struct aux2*) malloc(sizeof(struct aux2));
    
   int hashIndex = hashCodeAll2(key);

   while((*(hashArray + hashIndex)) != NULL && (*(hashArray + hashIndex))->key != NULL && strcmp((*(hashArray + hashIndex))->key,key)!=0) {

      ++hashIndex;

      hashIndex %= SIZE2;
   }

   if((*(hashArray + hashIndex))==NULL){
	item->key = strdup(key);
	item->total = total;
	(*(hashArray + hashIndex)) = item;
   }
   else {
	(*(hashArray + hashIndex))->total += total;
   }
	return hashArray;
}

/*inicialização da estrutura*/
struct aux2** initAux2(struct aux2** ht,int n){
    int i;
    for(i=0;i<n;i++){
	(*(ht + i)) = NULL;
    }
	return ht;
}

/*criacao de um nodo*/
struct aux2* newAux2(char* key, float total){
	struct aux2* aux = malloc(sizeof(struct aux2));
	aux->total = total;
	aux->key = strdup(key);
	return aux;
}

/* construi os n máximos elementos na estrutura auxiliar limitando n por cada filial*/
struct aux2** buildNMax2(struct aux2** ret,int n,int k,struct aux2* aux){
	int i,j,size;

	size = getSize2(ret,n,k);

	if(size == 0){
		*(ret+n*k) = newAux2(aux->key,aux->total);
		return ret;
	}
	if(size>=n) size = n;

	for(i=k*n;i<size+k*n && (*(ret+i))->total > aux->total;i++){}

	if(i==n+k*n)
		return ret;

	if(size==n) size--;

	for(j=size+k*n;j>i;j--){
		*(ret+j) = *(ret + j-1);
	}

	*(ret + j) = newAux2(aux->key,aux->total);
	return ret;
}

/*calculo do tamanho do array/hashtable*/
int getSize2(struct aux2** ret,int n,int k){
	int i;
	for(i = n*k; (*(ret+i))!=NULL;i++){}
	i-=n*k;
	return i;
}

/*adiciona a estrutura a uma view Aduicionar a outra variável*/
struct list* addAuxToList2(struct list* list,struct aux2** ret,int n, int k){
	int i;
	for(i=0;i<n*k;i++){
		if(*(ret+i)!=NULL){
			list = stringBuilderStrFlt((*(ret+i))->key,&((*(ret+i))->total),list);
		}else list = addToList(list,"Não tem mais produtos");
	}
	return list;
}

/*destroi a estrutura*/
void destroyAux2(struct aux2** aux,int n){
	int i;
	for(i=0;i<n;i++)
		free(*(aux+i));
}

