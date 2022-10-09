#include"produtos.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"produtos.h"
#include"produtosaux.h"
#include "view.h"

#define SIZE 26
#define FILIAIS 3
#define MES 12

/*estrutura principal dos produtos*/
struct DataItem {
   ProdutosAux data;
   int total;   
   char* key;
};

/* função de cálculo do hashcode*/
int hashCode(char *str)
{
    unsigned long hash = 4;
    int c;

    while ((c = *str++))
        hash = ((hash << 1) + hash) + c; 

    return (hash%SIZE);
}

/*função que inicializa o catálogo de produtos*/
struct DataItem** initProdutos(struct DataItem** ht){
    int i;
    ht = malloc(sizeof(struct DataItem)*SIZE);
    for(i=0;i<SIZE;i++){
	*( ht + i) = NULL;
    }
    
	return ht;
}

/* Procura a posição dos produtos que começam por uma determinada letra*/
Produtos searchProdutos(Produtos* hashArray,char* key) {

   char* aux;
   aux = strndup(key,1);
   int hashIndex = hashCode(aux);  
	
   while((*(hashArray + hashIndex)) != NULL) {
	
      if(strcmp((*(hashArray + hashIndex))->key,aux)==0){
	free(aux);
         return (*(hashArray + hashIndex)); 
      }	

      ++hashIndex;	

      hashIndex %= SIZE;
   }        
	
   return NULL;        
}

/* Verifica se um produto existe no catálogo de produtos*/
int existsProdutos(Produtos* hashArray, char* key){

   char* aux;
   aux = strndup(key,1);
   int hashIndex = hashCode(aux);  
	
   while((*(hashArray + hashIndex)) != NULL) {
	
      if(strcmp((*(hashArray + hashIndex))->key,aux)==0){
	 free(aux);
         return existsProdutosAux((*(hashArray + hashIndex))->data,key); 
      }
      ++hashIndex;
		

      hashIndex %= SIZE;	
   }
   return 0;
}

/*Devolve a estrutura secundária que contêm a informação relativa a um produto*/
ProdutosAux searchAuxProdutos(Produtos* hashArray, char* key){

   char* aux;
   aux = strndup(key,1);
   int hashIndex = hashCode(aux);  
	
   while((*(hashArray + hashIndex)) != NULL) {
	
      if(strcmp((*(hashArray + hashIndex))->key,aux)==0){
	 free(aux);
         return searchProdutosAux((*(hashArray + hashIndex))->data,key); 
      }
      ++hashIndex;
		

      hashIndex %= SIZE;	
   }
   return NULL;
}         

/*insere no catálogo de produtos*/
Produtos* insertProdutos(Produtos* hashArray,char* key) {

   Produtos item = (Produtos) malloc(sizeof(struct DataItem));
   char* aux;
   aux = strndup(key,1);
    
   int hashIndex = hashCode(aux);


   while((*(hashArray + hashIndex)) != NULL && (*(hashArray + hashIndex))->key != NULL && strcmp((*(hashArray + hashIndex))->key,aux)!=0) {

      ++hashIndex;

      hashIndex %= SIZE;
   }

   if((*(hashArray + hashIndex))==NULL){
	item->key = strdup(aux);
	item->total =1;
	item->data = newProdutosAux(key);
	(*(hashArray + hashIndex)) = item;
   }
   else {
	(*(hashArray + hashIndex))->data = insertProdutosAux((*(hashArray + hashIndex))->data,key);
	(*(hashArray + hashIndex))->total +=1;
   }
   free(aux);
	return hashArray;
}


/*devolve a lista ordenada dos produtos que começam por uma determinada letra*/
struct view* getProdutosStartingWithProdutos(Produtos* hashArray, char* key,struct view* view) {
   
   int hashIndex = hashCode(key);  
   char total[40];
   while((*(hashArray + hashIndex)) != NULL) {
	
      if(strcmp((*(hashArray + hashIndex))->key,key)==0){
	 sprintf(total,"%s: %d","Número total de produtos",(*(hashArray + hashIndex))->total);
	 view = insertProdutosAuxInList((*(hashArray + hashIndex))->data,view);
	 view = addToHeadView(view,(char*)total);
	 return view;
      }
      ++hashIndex;
		

      hashIndex %= SIZE;	
   }
	return view;
}

/*imprime o catálogo de produtos para um ficheiro*/
void printToFileProdutos(Produtos* hashArray,FILE* f){
	int i;
	printToFile((*(hashArray + 25))->data,f);

	for(i=0;i<SIZE-1;i++){
		printToFile((*(hashArray + i))->data,f);
	}
}

/*devolve a lista dos produtos que nunca foram comprados*/
struct list* neverBoughtProdutos(Produtos* hashArray,struct list* list){
	int i,total;
	total = 0;
	char res[50];
	list = neverBoughtProdutosAux((*(hashArray + 25))->data,list,&total);

	for(i=0;i<SIZE-1;i++){
		list = neverBoughtProdutosAux((*(hashArray + i))->data,list,&total);
	}
	sprintf(res,"Número de produtos nunca comprados: %d",total);
	list = addToHeadList(list,(char*)res);
	return list;
}

/*devolve o número de produtos que nunca foram comprados*/
struct list* neverBoughtNumberProdutos(Produtos* hashArray,struct list* list){
	int i,total;
	total = 0;
	char res[50];
	neverBoughtNumberProdutosAux((*(hashArray + 25))->data,&total);

	for(i=0;i<SIZE-1;i++){
		neverBoughtNumberProdutosAux((*(hashArray + i))->data,&total);
	}
	sprintf(res,"Número de produtos nunca comprados: %d",total);
	list = addToList(list,(char*)res);
	return list;
}

/* valida, insere e imprime no final o catálogo de produtos para um ficheiro */
Produtos* loadP(Produtos* ht, char* fl,int* total){

	char str[60],*aux;
	FILE* f;

	f = fopen(fl,"r");


        if(!f) {
                printf("Erro a ler ficheiro\n");
                return 0;
        }

        while(fgets(str,10,f) != NULL){

		aux = strtok(str,"\r\n");

		if(aux[0]>='A' && aux[0]<='Z' && aux[1]>='A' && aux[1]<='Z')
			if(atoi(aux+2)>=1000 && atoi(aux+2)<=9999){
	                	ht = insertProdutos(ht,aux);
				*(total) +=1;
			}

        }
	
	fclose(f);
   
	f = fopen("P.txt","w+");

	printToFileProdutos(ht,f);

	fclose(f);
	return ht;
}

/*inicialização do catálogo de produtos*/
Produtos* initPrd(Produtos* ht){
    int i;
    for(i=0;i<SIZE;i++)
	(*(ht + i)) = NULL;
    return ht;
}

/*devolve a lista dos produtos que nunca foram comprados filial a filial*/
struct multiView** naoComprouProduto(Produtos* hashArray,struct multiView** view){
	int i;

	view = naoComprouEmFiliaisAux((*(hashArray + 25))->data,view);

	for(i=0;i<SIZE-1;i++){
		view = naoComprouEmFiliaisAux((*(hashArray + i))->data,view);
	}
	return view;
}
