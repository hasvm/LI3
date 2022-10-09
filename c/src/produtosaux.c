#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include"produtosaux.h"
#include"view.h"

#define FILIAIS 3

/*struct ProdutosAux* struct*/

struct ProdutosAux { 
    char* key;
    struct ProdutosAux* left; 
    struct ProdutosAux* right; 
    int height;
    int comprou;
    int filiais[FILIAIS];
};


struct ProdutosAux* initProdutosAux(struct ProdutosAux* node){
	node = NULL;
	return node;
}

/* Altura da arvore*/
int heightProdutosAux(struct ProdutosAux* N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
/* Máximo de dois int*/
int maxProdutosAux(int a, int b) 
{ 
    return (a > b)? a : b; 
} 
  
/*Criação de um nodo*/
struct ProdutosAux* newProdutosAux(char* key){
    int i; 
    struct ProdutosAux* node = (struct ProdutosAux*) malloc(sizeof(struct ProdutosAux)); 
    node->key   = strdup(key); 
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;
    node->comprou = 0;
    for(i=0;i<FILIAIS;i++){
	node->filiais[i]=0;
	}
    return(node); 
} 
  
/* Rotação à direita*/
struct ProdutosAux* rightRotateProdutosAux(struct ProdutosAux* y) 
{ 
    struct ProdutosAux* x = y->left; 
    struct ProdutosAux* T2 = x->right; 
  
    x->right = y; 
    y->left = T2; 
  
    y->height = maxProdutosAux(heightProdutosAux(y->left), heightProdutosAux(y->right))+1; 
    x->height = maxProdutosAux(heightProdutosAux(x->left), heightProdutosAux(x->right))+1; 
  
    return x; 
} 
  
/* Rotação à esquerda*/
struct ProdutosAux* leftRotateProdutosAux(struct ProdutosAux* x) 
{ 
    struct ProdutosAux* y = x->right; 
    struct ProdutosAux* T2 = y->left; 
  
    y->left = x; 
    x->right = T2; 
  
    x->height = maxProdutosAux(heightProdutosAux(x->left), heightProdutosAux(x->right))+1; 
    y->height = maxProdutosAux(heightProdutosAux(y->left), heightProdutosAux(y->right))+1; 
  
    return y; 
} 
  
/* Balanço da árvore*/
int getBalanceProdutosAux(struct ProdutosAux* N) 
{ 
    if (N == NULL) 
        return 0; 
    return heightProdutosAux(N->left) - heightProdutosAux(N->right); 
} 
  
/* Inserção de um nodo na árvore*/
struct ProdutosAux* insertProdutosAux(struct ProdutosAux* node, char* key) 
{ 

    if (node == NULL) 
        return(newProdutosAux(key)); 
  
    if (strcmp(key,node->key)<0) 
        node->left  = insertProdutosAux(node->left, key); 
    else if (strcmp(key,node->key)>0) 
        node->right = insertProdutosAux(node->right, key); 
    else 
        return node;
  

    node->height = 1 + maxProdutosAux(heightProdutosAux(node->left), 
                           heightProdutosAux(node->right)); 
  

    int balance = getBalanceProdutosAux(node); 
  
    if (balance > 1 && strcmp(key,node->left->key)<0) 
        return rightRotateProdutosAux(node); 
  
    if (balance < -1 && strcmp(key,node->right->key)>0) 
        return leftRotateProdutosAux(node); 
  
    if (balance > 1 && strcmp(key,node->left->key)>0) 
    { 
        node->left =  leftRotateProdutosAux(node->left); 
        return rightRotateProdutosAux(node); 
    } 
  
    if (balance < -1 && strcmp(key,node->right->key)<0) 
    { 
        node->right = rightRotateProdutosAux(node->right); 
        return leftRotateProdutosAux(node); 
    } 
  
    return node; 
}

int existsProdutosAux(struct ProdutosAux* a,char* key){
	if(a==NULL) return 0;
	if(strcmp(a->key,key)==0) return 1;
	if(strcmp(a->key,key)<0) return existsProdutosAux(a->right,key);
	return existsProdutosAux(a->left,key);
}

/* Imprimir para ficheiro*/
void printToFile(struct ProdutosAux* a, FILE* f){
	if(a==NULL) return;
	printToFile(a->left,f);
	fputs(a->key,f);
	fputs("\n",f);
	printToFile(a->right,f);
}


/* Insert ProdutosAux into List*/
struct view* insertProdutosAuxInList(struct ProdutosAux* a, struct view* view){
	if(a==NULL) return view;
	view = insertProdutosAuxInList(a->left,view);
	view = insertView(view, a->key);
	view = insertProdutosAuxInList(a->right,view);
	return view;
}

/* Remover a árvore*/
void deleteProdutosAux(struct ProdutosAux* a){
	if(a==NULL) return;
	deleteProdutosAux(a->left);
	free(a);
	deleteProdutosAux(a->right);
}

/*Procura Nodo na árvore*/
struct ProdutosAux* searchProdutosAux(struct ProdutosAux* node, char* key){
	if(node==NULL) return NULL; 
	if(strcmp(node->key,key)==0) return node;
	if(strcmp(node->key,key)>0) return searchProdutosAux(node->left,key);
	return searchProdutosAux(node->right,key);
}

/*Update Nodo para comprado ou comrpou*/
void updateProdutosAux(struct ProdutosAux* node,int filial){
	node->comprou=1;
	node->filiais[filial]=1;
}

/*função auxiliar para a função que calcula os produtos que nunca foram comprados em produtos.c*/
struct list* neverBoughtProdutosAux(struct ProdutosAux* node,struct list* list,int* total){
	if(node==NULL) return list;
	list = neverBoughtProdutosAux(node->left,list,total);
	if(node->comprou==0){list = addToList(list,node->key); *(total)+=1;}
	list = neverBoughtProdutosAux(node->right,list,total);
	return list;
}

/*calculo do número de produtos que nunca foram comprados*/
void neverBoughtNumberProdutosAux(struct ProdutosAux* node,int* total){
	if(node!=NULL){
		neverBoughtNumberProdutosAux(node->left,total);
		if(node->comprou==0) *(total)+=1;
		neverBoughtNumberProdutosAux(node->right,total);
	}
}

/*função auxiliar para o cálculo de produtos que nunca foram comprados filial a filail em produtos.c*/
struct multiView** naoComprouEmFiliaisAux(struct ProdutosAux* node,struct multiView** view){

	if(node == NULL) return view;

	view = naoComprouEmFiliaisAux(node->left,view);
	int i;
	for(i=0;i<FILIAIS;i++){
		if(node->filiais[i]==0){
			*(view+i) = insertMultiView(*(view+i),node->key);
		}
	}
	view = naoComprouEmFiliaisAux(node->right,view);
	return view;
}
