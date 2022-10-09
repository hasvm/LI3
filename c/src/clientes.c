#include"clientes.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"clientes.h"

#define FILIAIS 3

/*struct Node* struct*/
struct Node { 
    char* key;
    struct Node* left; 
    struct Node* right; 
    int height;
    int comprou;
    int filiais[FILIAIS];
};

/*Altura da arvore*/
int heightClientes(struct Node* N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
/*Máximo de dois int*/
int maxClientes(int a, int b) 
{ 
    return (a > b)? a : b; 
} 
  
/*Criação de um nodo*/
struct Node* newNodeClientes(char* key){
    int i; 
    struct Node* node = (struct Node*) malloc(sizeof(struct Node)); 
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
  
/*Rotação à direita */
struct Node* rightRotateClientes(struct Node* y) 
{ 
    struct Node* x = y->left; 
    struct Node* T2 = x->right; 
  
    x->right = y; 
    y->left = T2; 
  
    y->height = maxClientes(heightClientes(y->left), heightClientes(y->right))+1; 
    x->height = maxClientes(heightClientes(x->left), heightClientes(x->right))+1; 
  
    return x; 
} 
  
/*Rotação à esquerda*/
struct Node* leftRotateClientes(struct Node* x) 
{ 
    struct Node* y = x->right; 
    struct Node* T2 = y->left; 
  
    y->left = x; 
    x->right = T2; 
  
    x->height = maxClientes(heightClientes(x->left), heightClientes(x->right))+1; 
    y->height = maxClientes(heightClientes(y->left), heightClientes(y->right))+1; 
  
    return y; 
} 
  
/*Balanço da árvore*/
int getBalanceClientes(struct Node* N) 
{ 
    if (N == NULL) 
        return 0; 
    return heightClientes(N->left) - heightClientes(N->right); 
} 
  
/*Inserção de um nodo na árvore*/
struct Node* insertClientes(struct Node* node, char* key) 
{ 

    if (node == NULL) 
        return(newNodeClientes(key)); 
  
    if (strcmp(key,node->key)<0) 
        node->left  = insertClientes(node->left, key); 
    else if (strcmp(key,node->key)>0) 
        node->right = insertClientes(node->right, key); 
    else 
        return node;
  

    node->height = 1 + maxClientes(heightClientes(node->left), 
                           heightClientes(node->right)); 
  

    int balance = getBalanceClientes(node); 
  
    if (balance > 1 && strcmp(key,node->left->key)<0) 
        return rightRotateClientes(node); 
  
    if (balance < -1 && strcmp(key,node->right->key)>0) 
        return leftRotateClientes(node); 
  
    if (balance > 1 && strcmp(key,node->left->key)>0) 
    { 
        node->left =  leftRotateClientes(node->left); 
        return rightRotateClientes(node); 
    } 
  
    if (balance < -1 && strcmp(key,node->right->key)<0) 
    { 
        node->right = rightRotateClientes(node->right); 
        return leftRotateClientes(node); 
    } 
  
    return node; 
}

int existsClientes(struct Node* a,char* key){
	if(a==NULL) return 0;
	if(strcmp(a->key,key)==0) return 1;
	if(strcmp(a->key,key)<0) return existsClientes(a->right,key);
	return existsClientes(a->left,key);
}

/*Imprimir para ficheiro*/
void printToFileClientes(struct Node* a, FILE* f){
	if(a==NULL) return;
	printToFileClientes(a->left,f);
	fputs(a->key,f);
	fputs("\n",f);
	printToFileClientes(a->right,f);
}


/*Insert AVL into List*/
struct list* insertClientesInList(struct Node* a, struct list* list){
	if(a==NULL) return list;
	insertClientesInList(a->left,list);
	list = addToList(list, a->key);
	insertClientesInList(a->right,list);
	return list;
}

/*Remover a árvore*/
void deleteClientes(struct Node* a){
	if(a==NULL) return;
	deleteClientes(a->left);
	free(a);
	deleteClientes(a->right);
}

/*Procura Nodo na árvore*/
struct Node* searchClt(struct Node* node, char* key){
	if(node==NULL) return NULL; 
	if(strcmp(node->key,key)==0) return node;
	if(strcmp(node->key,key)>0) return searchClt(node->left,key);
	return searchClt(node->right,key);
}

/*Update Nodo para comprado ou comrpou*/
void updateClientes(struct Node* node,int filial){
	node->comprou=1;
	node->filiais[filial] = 1;
}

/*devolve a lista dos clientes que nunca compraram*/
struct list* neverBoughtClientes(struct Node* node,struct list* list,int* total){
	if(node==NULL) return list;
	list = neverBoughtClientes(node->left,list,total);
	if(node->comprou==0){list = addToList(list,node->key); *(total)+=1;}
	list = neverBoughtClientes(node->right,list,total);
	return list;
}

/*função auxiliar para o cálculo dos clientes que nunca compraram*/
void neverBoughtNumberClientes(struct Node* node,struct list* list,int* total){
	if(node!=NULL){
		neverBoughtNumberClientes(node->left,list,total);
		if(node->comprou==0) *(total)+=1;
		neverBoughtNumberClientes(node->right,list,total);
	}
}

/*devolve a lista dos clientes que compraram em todas as filiais*/
struct view* compraramEmFiliais(struct Node* node, struct view* view,int* a){

	if(node == NULL) return view;

	view = compraramEmFiliais(node->left,view,a);
	if((comprouEmTodas(node))==1) {*a +=1; view = insertView(view,node->key);}
	view = compraramEmFiliais(node->right,view,a);

	return view;
}

/*função auxiliar para o cálculo dos clientes que compraram em todas as filiais*/
int comprouEmTodas(struct Node* node){
	int i=0;
	for(i=0;(i<FILIAIS && (node->filiais[i]==1));i++){}
	if(i==FILIAIS) return 1;
	return 0;
}

/*função que lê o ficheiro do clientes e carrega a informação no catálogo dos clientes*/
Clientes loadC(Clientes tree, char* fl,int* total){

	char str[60],*aux;
	FILE* f;

	f = fopen(fl,"r");

	if(!f) {
		printf("Erro a ler ficheiro\n");
		return 0;
	}


	while(fgets(str,10,f) != NULL){
		aux = strtok(str,"\r\n");
		if(aux[0]>='A' && aux[0]<='Z')
				if(atoi(aux+1) >=1000 && atoi(aux+1)<=5000){
					tree = insertClientes(tree,aux);
					*(total) +=1;
				}					
	}

	fclose(f);
	
	f = fopen("C.txt","w+");
	printToFileClientes(tree,f);

	return tree;
}

/*inicialização do catálogo de clientes*/
Clientes initClt(Clientes node){
	node = NULL;
	return node;
}
