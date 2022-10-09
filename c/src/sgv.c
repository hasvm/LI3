#include "sgv.h"

#define SIZE 26
#define FILIAIS 3


struct sgv{
	Clientes clientes;
	Produtos* produtos;
	AVLS* faturacao;
	AVLS* filial;
	int c;
	int p;
	int v;
};


sgv initSGV(sgv compra){
	compra = malloc(sizeof(struct sgv));
	compra->clientes = initClt(compra->clientes);
	compra->produtos = initProdutos(compra->produtos);
	compra->faturacao = initFaturacao(compra->faturacao);
	compra->filial = initFil(compra->filial);
	
	return compra;
}

sgv Querie1(sgv compra){

	char* clts = "./docs/Clientes.txt";
	char* prods = "./docs/Produtos.txt";
	
	char* vendas="./docs/Vendas_1M.txt";

	int total=0;

	compra->clientes = loadC(compra->clientes,clts,&total);
	compra->c = total;

	total =0;

	compra->produtos = loadP(compra->produtos,prods,&total);
	compra->p = total;

	total =0;

	compra->faturacao = loadFFasts(compra->faturacao,compra->filial,compra->clientes,compra->produtos,vendas,&total);
	compra->v = total;

	return compra;
}

sgv Querie1B(sgv compra,char* clts,char* prods,char* vendas){

	char res[50];
	sprintf(res,"./docs/%s",clts);
	char* str;
	str = strdup(res);
	
	int total=0;

	compra->clientes = loadC(compra->clientes,str,&total);
	compra->c = total;

	free(str);

	char res1[50];
	sprintf(res1,"./docs/%s",prods);
	str = strdup(res1);

	total =0;

	compra->produtos = loadP(compra->produtos,str,&total);
	compra->p = total;

	free(str);

	char res2[50];
	sprintf(res2,"./docs/%s",vendas);
	str = strdup(res2);

	total =0;

	compra->faturacao = loadFFasts(compra->faturacao,compra->filial,compra->clientes,compra->produtos,str,&total);
	compra->v = total;

	free(str);

	return compra;
}

struct view* Querie2(sgv compra,char* letra,struct view* list){

	list = getProdutosStartingWithProdutos(compra->produtos,letra,list);

	return list;
}


struct list* Querie3(sgv compra,int mes, char* produto,struct list* list){
	
	list = getTotalMesProduto(compra->faturacao,mes,produto,list);

	return list;

}


struct list* Querie31(sgv compra,int mes, char* produto,struct list* list){
	
	list = getTotalMesProdutoFiliais(compra->filial,mes,produto,list);

	return list;

}

struct list* Querie4(sgv compra,struct list* list){
	
	list = neverBoughtProdutos(compra->produtos,list);

	return list;

}


struct multiView** Querie41(sgv compra,struct multiView** view){

	naoComprouProduto(compra->produtos,view);

	return view;

}


struct view* Querie5(sgv compra,struct view* view){
	
	int a=0;
	view = compraramEmFiliais(compra->clientes,view,&a);
	char res[80];
	sprintf(res,"Número de clientes que compraram em todas as filiais: %d",a);
	char* str;
	str = strdup(res);
	view = addToHeadView(view,str);
	free(str);

	return view;

}


struct list* Querie6(sgv compra,struct list* list){
	
	int a=0;
	neverBoughtNumberClientes(compra->clientes,list,&a);
	char res[50];
	sprintf(res,"Número de clientes que nunca compraram: %d",a);
	char* str;
	str = strdup(res);
	list = addToList(list,str);
	free(str);

	list = neverBoughtNumberProdutos(compra->produtos,list);

	return list;

}


struct list* Querie7(sgv compra,char* clt,struct list* list){

	list = getTotalVendasMes(compra->filial,clt,list);

	return list;
}


struct list* Querie8(sgv compra,int mes1,int mes2,struct list* list){

	list = salesFromTo(compra->faturacao,mes1,mes2,list);

	return list;
}



struct list* Querie9(sgv compra,int filial,char* produto,struct list* list){

	list = getClientesFilialProduto(compra->filial,filial,produto,list);

	return list;
}


struct list* Querie10(sgv compra,int mes,char* clt,struct list* list){

	list = getMaxBuy(compra->faturacao,mes,clt,list);

	return list;
}


struct list* Querie11(sgv compra,int n, struct list* list){

	list = getMaxAll(compra->filial,n,list);

	return list;
}



struct list* Querie12(sgv compra,char* clt,int n, struct list* list){

	list = getMaxNForClient(compra->faturacao,clt,n,list);

	return list;
}


struct list* Querie13(sgv compra,struct list* list){

	list = stringBuilderStrInt("Número de clientes válidos: ",&(compra->c),list);
	list = stringBuilderStrInt("Número de produtos válidos: ",&(compra->p),list);
	list = stringBuilderStrInt("Número de vendas válidass: ",&(compra->v),list);

	return list;
}
