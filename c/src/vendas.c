#include"vendas.h"

#define SIZE 26
#define MAX 500000
#define MAX2 50000
#define MES 12
#define FILIAIS 3

/* AVLS structs*/
struct sales {
    char* key;
    float faturadoP;
    float faturadoN;
    int quantP;
    int quantN;
    int vendasP;
    int vendasN;
    int height;
    struct sales* left;
    struct sales* right;
};

struct total {
	int vendasN;
	int quantN;
	float faturadoN;
	int quantP;
	int vendasP;
	float faturadoP;
};

struct Sale { 
    char* key;
    struct sales* produtos;
    struct total* totais;
    struct Sale* left; 
    struct Sale* right;
    int height;
};


/*inicialização das estruturas de dados para faturcao e filiais*/
AVLS* initFaturacao(AVLS* xpto){
	int i=0;
	xpto = malloc(sizeof(struct Sale)*MES);
	for(i=0;i<MES;i++){
			*(xpto+i) = NULL;
	}
	return xpto;
}

AVLS* initFil(AVLS* xpto){
	int i=0;
	xpto = malloc(sizeof(struct Sale)*(MES*FILIAIS));
	for(i=0;i<MES*FILIAIS;i++){
			*(xpto+i) = NULL;
	}
	return xpto;
}



/* Altura da arvore*/
int height(AVLS N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
}

/* Altura da árvore secundária*/
int heightS(struct sales* N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
/* Máximo de dois int*/
int max(int a, int b) 
{ 
    return (a > b)? a : b;
}

/*criacao de um nodo secundário*/
struct sales* newSaleNode(char* prod,float price,int quant,char tipo){

    struct sales* s = (struct sales*) malloc(sizeof(struct sales));
    s->key = strdup(prod);
    s->left = NULL;
    s->right = NULL;
    s->height = 1;
    if(tipo=='N') {
	    s->vendasN = 1;
	    s->quantN = quant;
	    s->faturadoN = price*quant;
	    s->quantP = 0;
	    s->vendasP = 0;
	    s->faturadoP = 0;
    }
    if(tipo=='P'){
	    s->vendasP = 1;
	    s->quantP = quant;
	    s->faturadoP = price*quant;
	    s->vendasN = 0;
	    s->quantN = 0;
	    s->faturadoN =0;
    }
    return s;
}
  
/*Criação de um nodo*/
AVLS newNode(char* clt,char* prod,float price,int quant,char tipo) 
{ 

    AVLS node = (AVLS) malloc(sizeof(struct Sale)); 
    node->key   = strdup(clt);
    node->produtos = newSaleNode(prod,price,quant,tipo);
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;
    node->totais = (struct total*)  malloc(sizeof(struct total));
   
    if(tipo=='N') {
	    node->totais->vendasN = 1;
	    node->totais->quantN = quant;
	    node->totais->faturadoN = price*quant;
	    node->totais->quantP = 0;
	    node->totais->vendasP = 0;
	    node->totais->faturadoP =0;
    }
    if(tipo=='P'){
	    node->totais->vendasP = 1;
	    node->totais->quantP = quant;
	    node->totais->faturadoP = price*quant;
	    node->totais->vendasN = 0;
	    node->totais->quantN = 0;
	    node->totais->faturadoN =0;
    }
    return(node); 
}

/* Rotação à direita*/ 
AVLS rightRotate(AVLS y) 
{ 
    AVLS x = y->left; 
    AVLS T2 = x->right; 
  
    x->right = y; 
    y->left = T2; 
  
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
  
    return x; 
}

/*Rotacao a direita da árvore secundária*/
struct sales* rightRotateS(struct sales* y) 
{ 
    struct sales* x = y->left; 
    struct sales* T2 = x->right; 
  
    x->right = y; 
    y->left = T2; 
  
    y->height = max(heightS(y->left), heightS(y->right))+1; 
    x->height = max(heightS(x->left), heightS(x->right))+1; 
  
    return x; 
}
  
/* Rotação à esquerda*/
AVLS leftRotate(AVLS x) 
{ 
    AVLS y = x->right; 
    AVLS T2 = y->left; 
  
    y->left = x; 
    x->right = T2; 
  
    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
  
    return y; 
}

/* Rotação à esquerda da árvore secundária*/
struct sales* leftRotateS(struct sales* x) 
{ 
    struct sales* y = x->right; 
    struct sales* T2 = y->left; 
  
    y->left = x; 
    x->right = T2; 
  
    x->height = max(heightS(x->left), heightS(x->right))+1; 
    y->height = max(heightS(y->left), heightS(y->right))+1; 
  
    return y; 
} 
  
/* Balanço da árvore*/
int getBalance(AVLS N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
}

/* Balanço da árvore secundária*/
int getBalanceS(struct sales* N) 
{ 
    if (N == NULL) 
        return 0; 
    return heightS(N->left) - heightS(N->right); 
}

/*Inserção na segunda árvore*/
struct sales* insertS(struct sales* node, char* key,float price,int quant,char tipo) 
{ 
    if (node == NULL) 
        return(newSaleNode(key,price,quant,tipo));

    if (strcmp(key,node->key)==0){
	if(tipo=='P'){
		node->vendasP += 1;
		node->quantP +=quant;
		node->faturadoP += price*quant;
		return node;
	}
	node->vendasN += 1;
	node->quantN += quant;
	node->faturadoN += price*quant;
	return node;
    }
    if (strcmp(key,node->key)<0) 
        node->left  = insertS(node->left, key,price,quant,tipo); 
    else if (strcmp(key,node->key)>0) 
        node->right = insertS(node->right, key,price,quant,tipo); 
    else 
        return node; 
  

    node->height = 1 + max(heightS(node->left), 
                           heightS(node->right)); 
  

    int balance = getBalanceS(node); 
  
    if (balance > 1 && strcmp(key,node->left->key)<0) 
        return rightRotateS(node); 
  
    if (balance < -1 && strcmp(key,node->right->key)>0) 
        return leftRotateS(node); 
  
    if (balance > 1 && strcmp(key,node->left->key)>0) 
    { 
        node->left =  leftRotateS(node->left); 
        return rightRotateS(node); 
    } 
  
    if (balance < -1 && strcmp(key,node->right->key)<0) 
    { 
        node->right = rightRotateS(node->right); 
        return leftRotateS(node); 
    } 
  
    return node; 
}

/*Inserir totais de faturacao de um produto*/
struct total* insertTotais(struct total* node,float price,int quant,char tipo){
	if(tipo=='P'){
		node->vendasP += 1;
		node->quantP +=quant;
		node->faturadoP += price*quant;
		return node;
	}
	node->vendasN += 1;
	node->quantN += quant;
	node->faturadoN += price*quant;
	return node;

}

/* Inserção de um nodo na árvore*/
AVLS insert(AVLS node, char* key,char* clt,float price,int quant,char tipo) 
{ 
    if (node == NULL) 
        return(newNode(key,clt,price,quant,tipo));

    if(strcmp(key,node->key)==0){
	node->produtos = insertS(node->produtos,clt,price,quant,tipo);
    	node->totais = insertTotais(node->totais,price,quant,tipo);
    }
    if (strcmp(key,node->key)<0) 
        node->left  = insert(node->left, key,clt,price,quant,tipo); 
    else if (strcmp(key,node->key)>0) 
        node->right = insert(node->right, key,clt,price,quant,tipo); 
    else 
        return node; 
  

    node->height = 1 + max(height(node->left), 
                           height(node->right)); 
  

    int balance = getBalance(node); 
  
    if (balance > 1 && strcmp(key,node->left->key)<0) 
        return rightRotate(node); 
  
    if (balance < -1 && strcmp(key,node->right->key)>0) 
        return leftRotate(node); 
  
    if (balance > 1 && strcmp(key,node->left->key)>0) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    if (balance < -1 && strcmp(key,node->right->key)<0) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
  
    return node; 
}

/*função que devolve as vendas relativas a um produto(apontador para a árvore secundária)*/
struct Sale* searchT(struct Sale* a,char* key){
	if(a!=NULL){
	if(strcmp(a->key,key)==0) return a;
	if(strcmp(a->key,key)<0) return searchT(a->right,key);
	if(strcmp(a->key,key)>0) return searchT(a->left,key);
	}
	return NULL;
}

/*função que procura um cliente na árvore secundária*/
struct sales* searchClientes(struct Sale* a,char* key){
	if(a!=NULL) {	
	if(strcmp(a->key,key)==0) return a->produtos;
	if(strcmp(a->key,key)<0) searchClientes(a->right,key);
	if(strcmp(a->key,key)>0) searchClientes(a->left,key);
	}
	return NULL;
}

/*funçao que devolve um nodo da árvore secundária*/
struct sales* searchSub(struct sales* node,char* key){
	if(node!=NULL){
		if(strcmp(node->key,key)==0) return node;
		if(strcmp(node->key,key)<0) searchSub(node->right,key);
		if(strcmp(node->key,key)>0) searchSub(node->left,key);
	}
	return node;
}


/*3*/
/*Faturação total*/
/*devolve a lista com os totais de vendas e faturado de produto para um determinado mês difirenciando os totais em N e P*/
struct list* getTotalMesProduto(struct Sale** xpto,int mes, char* produto, struct list* list){

	struct Sale* xp = NULL;
	int vendasN=0;
	int vendasP=0;
	int quantN=0;
	int quantP=0;
	float totalN=0.0;
	float totalP=0.0;
	mes = mes-1;

	       	xp = searchT(*(xpto+mes),produto);
		if(xp!=NULL){
		vendasN = xp->totais->vendasN;
		vendasP = xp->totais->vendasP;
		totalN = xp->totais->faturadoN;
		totalP = xp->totais->faturadoP;
		quantN = xp->totais->quantN;
		quantP = xp->totais->quantP;
		}

	int total = vendasN + vendasP;
	float totalf = totalN + totalP;
	list = stringBuilderStrInt("Total de vendas: ",&total,list);
	list = stringBuilderStrFlt("Total faturado: ",&totalf,list);
	total = quantN+quantP;
	list = stringBuilderStrInt("Total quantidades vendidas: ",&total,list);
	list = stringBuilderStrInt("Total de vendas com desconto: ",&vendasP,list);
	list = stringBuilderStrFlt("Total faturado com desconto: ",&totalP,list);
	list = stringBuilderStrInt("Total quantidades vendidas com desconto: ",&quantP,list);
	list = stringBuilderStrInt("Total de vendas sem desconto: ",&vendasN,list);
	list = stringBuilderStrFlt("Total faturado sem desconto: ",&totalN,list);
	list = stringBuilderStrInt("Total quantidades vendidas sem desconto: ",&quantN,list);
	return list;
}

/*filias*/
/*devolve a lista com os totais de vendas e faturado de produto para um determinado mês difirenciando os totais em N e P*/
struct list* getTotalMesProdutoFiliais(struct Sale** xpto,int mes, char* produto, struct list* list){

	struct Sale* xp = NULL;
	int vendasN=0;
	int vendasP=0;
	int quantN=0;
	int quantP=0;
	float totalN=0.0;
	float totalP;
	mes = mes-1;
	int i,s;
	s=1;
		for(i=0;i<FILIAIS;i++){
		       	xp = searchT(*(xpto + (mes + i*MES)),produto);
			totalP=0.0;
			vendasN=0;
			vendasP=0;
			quantN=0;
			quantP=0;
			totalN=0.0;

			if(xp!=NULL){
				vendasN = xp->totais->vendasN;
				vendasP = xp->totais->vendasP;
				totalN = xp->totais->faturadoN;
				totalP = xp->totais->faturadoP;
				quantN = xp->totais->quantN;
				quantP = xp->totais->quantP;
				}
	int total = vendasN+vendasP;
	float totalf = totalN+totalP;
	list = stringBuilderStrInt("Filial: ",&s,list);
	list = stringBuilderStrInt("Total de vendas: ",&total,list);
	list = stringBuilderStrFlt("Total faturado: ",&totalf,list);
	total = quantN+quantP;
	list = stringBuilderStrInt("Total quantidades vendidas: ",&total,list);
	list = stringBuilderStrInt("Total de vendas com desconto: ",&vendasP,list);
	list = stringBuilderStrFlt("Total faturado com desconto: ",&totalP,list);
	list = stringBuilderStrInt("Total quantidades vendidas com desconto: ",&quantP,list);
	list = stringBuilderStrInt("Total de vendas sem desconto: ",&vendasN,list);
	list = stringBuilderStrFlt("Total faturado sem desconto: ",&totalN,list);
	list = stringBuilderStrInt("Total quantidades vendidas sem desconto: ",&quantN,list);
	s++;
	}

	return list;
}

/*7*/
/*dado um cliente devolve a tabela com os totais de quantidades de produtos comprados por filial e mês a mês*/
struct list* getTotalVendasMes(struct Sale** fil,char* clt,struct list* list){
	
	int total1,total2,total3,i;
	list = addToList(list,"Filial 1 | Filial 2 | Filial 3");
	for(i=0;i<12;i++){
		total1=0;
		total2=0;
		total3=0;
		getTotalQuantidades(*(fil + (i)),clt,&total1);
		getTotalQuantidades(*(fil + (i+12)),clt,&total2);
		getTotalQuantidades(*(fil + (i+24)),clt,&total3);
	list = addToLineList(list,&total1,&total2,&total3);
	}
	return list;
}

/*função auxiliar para o cálculo da função acima*/
void getTotalQuantidades(struct Sale* node,char* clt,int* total){
	if(node!=NULL){
		getTotalQuantidades(node->left,clt,total);
		getTotalQuantidadesSub(node->produtos,clt,total);
		getTotalQuantidades(node->right,clt,total);
	}
}

/*função auxiliar para o cálculo da função acima*/
void getTotalQuantidadesSub(struct sales* node,char* clt,int* total){
	struct sales* aux = NULL;
	aux = searchSub(node,clt);
	if(aux!=NULL){ *total += aux->quantN+aux->quantP;}
}


/*8*/
/*Dado dois meses devolve a lista dos totais vendidos e faturados nesse intervalo*/
struct list* salesFromTo(struct Sale** node,int mes1,int mes2,struct list* list){
	
	float total=0.0;
	int vendas = 0;
	int i,j;
	j=mes2-1;
	struct Sale* xp = NULL; 
	for(i=mes1-1;i<=j;i++){	
		xp = *(node + i);
		if(xp!=NULL){
			getFromTo(xp,&total,&vendas);
		}
	}
	list = stringBuilderStrInt("Total de vendas: ",&vendas,list);
	list = stringBuilderStrFlt("Total faturado: ",&total,list);
	return list;
}

/* função auxiliar para o cálculo da dunção acima*/
void getFromTo(struct Sale* node,float* total,int* vendas){
	if(node!=NULL){
		getFromTo(node->left,total,vendas);
		getFromTo(node->right,total,vendas);
		*total += node->totais->faturadoN + node->totais->faturadoP;
		*vendas += node->totais->vendasN + node->totais->vendasP;
	}
}


/*9*/
/*calculo dos clientes, que compraram um determinado produto numa determinada filial distinguindo valores em N e P*/
struct list* getClientesFilialProduto(struct Sale** node,int filial,char* prod,struct list* list){
		filial = filial-1;
		int a,b;
		a=0;
		b=0;
		struct sales* aux = NULL;
		int i;
		for(i=0;i<12;i++){
			aux = searchClientes(*(node + i+filial*12),prod);

			if(aux!=NULL){
				list = getClientesProduto(aux,&a,&b,list);
			}
		}
		char res[50];
		sprintf(res,"%s %d","Total de clientes N: ",a);
		list = addToHeadList(list,res);
		char res2[50];
		sprintf(res2,"%s %d","Total de clientes P: ",b);		
		list = addToHeadList(list,res2);
		return list;
}

/*função auxiliar para o cálculo da função acima*/
struct list* getClientesProduto(struct sales* node,int* a,int* b, struct list* list){

		if(node==NULL) return list;
		list = getClientesProduto(node->left,a,b,list);
		if(node->vendasN !=0 && node->vendasP !=0) {*a +=1; *b +=1; list = stringBuilderStrStr(node->key,": B",list);}
		else {
			if(node->vendasN !=0) {*a +=1; list = stringBuilderStrStr(node->key,": N",list);}
			if(node->vendasP !=0) {*b +=1; list = stringBuilderStrStr(node->key,": P",list);}
		}			
		list = getClientesProduto(node->right,a,b,list);
		return list;
}

/*10*/
/*cálculo dos códigos de produtos que um determinado cliente comprou num deterinado mês*/
struct list* getMaxBuy(struct Sale** node, int mes, char* clt,struct list* list){
		
	struct Sale* xp = *(node + mes-1);
	list = getMaxBuySub(xp,clt,list);
	return list;
}


/*função auxiliar para o cálculo da função acima*/
struct list* getMaxBuySub(struct Sale* node,char* clt,struct list* list){
	if(node==NULL) return list;
	list = getMaxBuySub(node->left,clt,list);
	int total=0;
	getMaxBuySubSub(node->produtos,clt,&total);
	if(total!=0){
		list = stringBuilderStrIntSortDesc(node->key,&total,list);	
	}
	list = getMaxBuySub(node->right,clt,list);
	return list;
}

/*função auxiliar para o cálculo da função acima*/
void getMaxBuySubSub(struct sales* node,char* clt,int* total){
	if(node==NULL) return;
	if(strcmp(node->key,clt)>0) getMaxBuySubSub(node->left,clt,total);
	if(strcmp(node->key,clt)==0) *total = node->quantP + node->quantN;
	getMaxBuySubSub(node->right,clt,total);

}

/*11*/
/*cria a lista dos produtos mais vendidos no ano indicando o total filial a filial*/
struct list* getMaxAll(struct Sale** node,int n,struct list* list){
	int i,j,k;
	int total;
	total = n*3;
	struct aux* rett[MAX];
	struct aux** ret = rett;
	ret = initAux(ret,MAX);
	struct aux* auxx[total];
	struct aux** aux = auxx;
	aux = initAux(aux,total);
	for(i=0;i<FILIAIS;i++){
		for(j=0;j<MES;j++){
			ret = getMaxAllSub(*(node+j+i*MES),ret);
		}
		for(k=0;k<MAX;k++){
			if(*(ret+k)!=NULL)
				aux = buildNMax(aux,n,i,*(ret+k));
		}
		emptyAux(ret,MAX);
	}
	list = addAuxToList(list,aux,n,FILIAIS);
	destroyAux(ret,MAX);
	destroyAux(aux,total);
	return list;
}

/*função auxuliar para o calculo da função anterior que acede aos totais de um nodo principal*/
struct aux** getMaxAllSub(struct Sale* node,struct aux** ret){

		if(node==NULL) return ret;
		ret = getMaxAllSub(node->left,ret);
		ret = getMaxAllSub(node->right,ret);
		int i=0;
		getTotalClientes(node->produtos,&i);
		int vendas = node->totais->quantN + node->totais->quantP;
		ret = insertAll(ret,node->key,i,vendas);
		return ret;
}

/*calcula o total de clientes que compraram um produto*/
void getTotalClientes(struct sales* node,int* count){
	if(node!=NULL){
		getTotalClientes(node->left,count);
		getTotalClientes(node->right,count);
		*count +=1;
	}
}

/*12*/
/*calculo dos n produtos e total gasto, por um cliente*/
struct list* getMaxNForClient(struct Sale** node,char* clt,int n,struct list* list){
	int i;
	struct aux2* rett[MAX2];
	struct aux2** ret = rett;
	ret = initAux2(ret,MAX2);
	struct aux2* auxx[n];
	struct aux2** aux = auxx;
	aux = initAux2(aux,n);


	for(i=0;i<FILIAIS;i++){
		ret = getMaxNForClientSub((*(node+i)),clt,ret);
	}

	for(i=0;i<MAX2;i++){
		if(*(ret+i)!=NULL)
			aux = buildNMax2(aux,n,0,*(ret+i));
	}

	list = addAuxToList2(list,aux,n,1);

	destroyAux2(ret,MAX2);
	destroyAux2(aux,n);
	return list;
}

/*precorre toda a estrutura principal chamando um função auxiliar para a estrutura secundária*/
struct aux2** getMaxNForClientSub(struct Sale* node,char* clt, struct aux2** ret){
		if(node==NULL) return ret;
		ret = getMaxNForClientSub(node->left,clt,ret);
		ret = getMaxNForClientSub(node->right,clt,ret);
		ret = getMaxNForClientSubSub(node->produtos,node->key,clt,ret);
		return ret;
}

/*insere na estrutura auxiliar da query toda a informação relativa à venda(informação na estrutura secundária)*/
struct aux2** getMaxNForClientSubSub(struct sales* node,char* prod, char* clt, struct aux2** ret){

		if(node!=NULL) {
			if(strcmp(node->key,clt)>0) ret = getMaxNForClientSubSub(node->left,prod,clt,ret);
			if(strcmp(node->key,clt)<0) ret = getMaxNForClientSubSub(node->right,prod,clt,ret);
			if(strcmp(node->key,clt)==0){
				float total = node->faturadoN + node->faturadoP;
				ret = insertAll2(ret,prod,total);
				return ret;
			}
		}
		return ret;
}


/*lê,valida, insere em sistema toda a informação relativa a uma venda tanto na faturação global e filiais*/
AVLS* loadFFasts(AVLS* xpto,AVLS* fil, Clientes tree,Produtos* ht, char* fl,int* total){

	char str[60],*aux,tipo,*prod,*clt;
	Clientes cliente=NULL;
	ProdutosAux produto = NULL;
	
	int mes,quant,filial;
	double preco;
	FILE* f;

	f = fopen(fl,"r");

        if(!f) {
                printf("Erro a ler ficheiro\n");
                return 0;
        }

 while(fgets(str,60,f) != NULL){
		aux = strtok(str," ");
		prod = strdup(aux);

			if((produto = (searchAuxProdutos(ht,prod)))!=NULL) {
				aux = strtok(NULL," ");

				if(aux!=NULL && atof(aux)>=0.0 && atof(aux)<=999.99){

					preco = atof(aux);
					aux = strtok(NULL," ");

					if(aux && atoi(aux)>=0 && atoi(aux)<=200){

						quant = atoi(aux);
						aux = strtok(NULL," ");

						if(aux[0]=='P' || aux[0] =='N'){
							
							tipo = aux[0];
							aux = strtok(NULL," ");
							clt = strdup(aux);

							if(aux!=NULL) {
									if((cliente = searchClt(tree,clt))!=NULL) {

										aux = strtok(NULL," ");

										if(aux!=NULL && atoi(aux)<=MES && atoi(aux)>0){

											mes = atoi(aux)-1;
											aux = strtok(NULL," ");

											if(aux!=NULL && atoi(aux)>0 && atoi(aux)<=FILIAIS){
												filial = atoi(aux)-1;
												*(total) +=1; 
												updateClientes(cliente,filial);
												updateProdutosAux(produto,filial);
												*(xpto + mes ) = insert(*(xpto + mes),prod,clt,preco,quant,tipo);
												*(fil + (mes + filial*MES)) = insert(*(fil + (mes + filial*MES)),prod,clt,preco,quant,tipo);
											}
										}
									}
								}
							}
						}
			}
		}
	}
	return xpto;
}


/*lê,valida, insere em sistema toda a informação relativa a uma venda tanto na faturação global*/
AVLS* loadFat(AVLS* xpto,Clientes tree,Produtos* ht, char* fl){

	char str[60],*aux,tipo,*prod,*clt;
	Clientes cliente=NULL;
	ProdutosAux produto = NULL;
	
	int mes,quant,filial;
	double preco;
	FILE* f;

	f = fopen(fl,"r");

        if(!f) {
                printf("Erro a ler ficheiro\n");
                return 0;
        }

 while(fgets(str,60,f) != NULL){
		aux = strtok(str," ");
		prod = strdup(aux);

			if((produto = (searchAuxProdutos(ht,prod)))!=NULL) {
				aux = strtok(NULL," ");

				if(aux!=NULL && atof(aux)>=0.0 && atof(aux)<=999.99){

					preco = atof(aux);
					aux = strtok(NULL," ");

					if(aux && atoi(aux)>=0 && atoi(aux)<=200){

						quant = atoi(aux);
						aux = strtok(NULL," ");

						if(aux[0]=='P' || aux[0] =='N'){
							
							tipo = aux[0];
							aux = strtok(NULL," ");
							clt = strdup(aux);

							if(aux!=NULL) {
									if((cliente = searchClt(tree,clt))!=NULL) {

										aux = strtok(NULL," ");

										if(aux!=NULL && atoi(aux)<=MES && atoi(aux)>0){

											mes = atoi(aux)-1;
											aux = strtok(NULL," ");

											if(aux!=NULL && atoi(aux)>0 && atoi(aux)<=FILIAIS){
												filial = atoi(aux)-1;  
												updateClientes(cliente,filial);
												updateProdutosAux(produto,filial);
												*(xpto + (mes )) = insert(*(xpto + (mes)),prod,clt,preco,quant,tipo);
											}
										}
									}
								}
							}
						}
			}
		}
	}
	return xpto;
}


/*lê,valida, insere em sistema toda a informação relativa a uma venda tanto na faturação global*/
AVLS* loadFil(AVLS* xpto,Clientes tree,Produtos* ht, char* fl){

	char str[60],*aux,tipo,*prod,*clt;
	Clientes cliente=NULL;
	ProdutosAux produto = NULL;
	
	int mes,quant,filial;
	double preco;
	FILE* f;

	f = fopen(fl,"r");

        if(!f) {
                printf("Erro a ler ficheiro\n");
                return 0;
        }

 while(fgets(str,60,f) != NULL){
		aux = strtok(str," ");
		prod = strdup(aux);

			if((produto = (searchAuxProdutos(ht,prod)))!=NULL) {
				aux = strtok(NULL," ");

				if(aux!=NULL && atof(aux)>=0.0 && atof(aux)<=999.99){

					preco = atof(aux);
					aux = strtok(NULL," ");

					if(aux && atoi(aux)>=0 && atoi(aux)<=200){

						quant = atoi(aux);
						aux = strtok(NULL," ");

						if(aux[0]=='P' || aux[0] =='N'){
							
							tipo = aux[0];
							aux = strtok(NULL," ");
							clt = strdup(aux);

							if(aux!=NULL) {
									if((cliente = searchClt(tree,clt))!=NULL) {

										aux = strtok(NULL," ");

										if(aux!=NULL && atoi(aux)<=MES && atoi(aux)>0){

											mes = atoi(aux)-1;
											aux = strtok(NULL," ");

											if(aux!=NULL && atoi(aux)>0 && atoi(aux)<=FILIAIS){
												filial = atoi(aux)-1;  
												*(xpto + (mes + filial*MES)) = insert(*(xpto + (mes + filial*MES)),prod,clt,preco,quant,tipo);
											}
										}
									}
								}
							}
						}
			}
		}
	}
	return xpto;
}
