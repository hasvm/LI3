#ifndef VENDAS_H
#define VENDAS_H

#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include "auxstruct.h"
#include "clientes.h"
#include "produtos.h"
#include "produtosaux.h"

/*estruturas das vendas*/
typedef struct Sale* AVLS;
struct sales;
struct total;

/*funçao que inicializa uma AVLS*/
AVLS* initF(AVLS*);
AVLS* initFaturacao(AVLS*);
AVLS* initFil(AVLS*);

/*funçao que calcula a altura da arvore de vendas face aos clientes*/
int height(AVLS);

/*funçao que calcula a altura da arvore de determinado cliente nas vendas*/
int heightS(struct sales*);

/*funçao que calcula o maximo de dois inteiros*/
int max(int, int);

/*funçao que inicializa um novo cliente*/
struct sales* newSaleNode(char*,float,int,char);

/*funçao que inicializa uma nova venda*/
AVLS newNode(char*,char*,float,int,char);

/*funçao de rotaçao da arvore das vendas*/
AVLS rightRotate(AVLS);
AVLS leftRotate(AVLS);

/*funçao de rotaçao da arvore das vendas de determinado cliente*/
struct sales* rightRotateS(struct sales*);
struct sales* leftRotateS(struct sales*);

/*funçao que devolve o balanceamento da arvore vendas*/
int getBalane(AVLS);

/*funçao que devolve o balanceamento da arvore vendas de determinado cliente*/
int getBalanceS(struct sales*);

/*funçao que insere na arvore vendas*/
struct sales* insertS(struct sales*, char*,float,int,char);

/*funçao que insere na arvore vendas de determinado cliente*/
AVLS insert(AVLS, char*,char*,float,int,char);

/*função que procura um cliente dentro da árvore secundária*/
struct sales* searchClientes(struct Sale*,char*);

/*funçao que devolve um nodo da árvore secundária*/
struct sales* searchSub(struct sales*,char*);

/*funçao que conta o numero de vendas*/
void count(struct Sale*,int *);

/*funçao de procura na arvore vendas de determinado cliente*/
struct Sale* searchT(struct Sale*,char*);

/*Faturação total*/
/*devolve a lista com os totais de vendas e faturado de produto para um determinado mês difirenciando os totais em N e P*/
struct list* getTotalMesProduto(struct Sale**,int,char*,struct list*);

/*filias*/
/*devolve a lista com os totais de vendas e faturado de produto para um determinado mês difirenciando os totais em N e P*/
struct list* getTotalMesProdutoFiliais(struct Sale**,int, char*, struct list*);

/*dado um cliente devolve a tabela com os totais de quantidades de produtos comprados por filial e mês a mês*/
struct list* getTotalVendasMes(struct Sale**,char*,struct list*);

/*precorre estrutura principal e chama a árvore secundária*/
void getTotalQuantidades(struct Sale*,char*,int*);

/*calcula os totais de um cliente na árvore secundária*/
void getTotalQuantidadesSub(struct sales*,char*,int*);

/*Dado dois meses devolve a lista dos totais vendidos e faturados nesse intervalo*/
struct list* salesFromTo(struct Sale**,int,int,struct list*);

/* função auxiliar para o cálculo da dunção acima*/
void getFromTo(struct Sale*,float* total,int*);

/*calculo dos clientes, que compraram um determinado produto numa determinada filial distinguindo valores em N e P*/
struct list* getClientesFilialProduto(struct Sale**,int,char*,struct list*);

/*verifica se o cliente comprou o produto em N,P ou ambos e insere na lista*/
struct list* getClientesProduto(struct sales*,int*,int*,struct list*);

/*cálculo dos códigos de produtos que um determinado cliente comprou num deterinado mês*/
struct list* getMaxBuy(struct Sale**, int, char*,struct list*);

/*função auxiliar para o cálculo da função acima que precorre a árvore secundária*/
struct list* getMaxBuySub(struct Sale*,char*,struct list*);

/*função auxiliar para o cálculo da função acima que soma os totais de um nodo da árvore secundária*/
void getMaxBuySubSub(struct sales*,char*,int*);

void getCltNumb(struct sales*,int*);

/*cria a lista dos produtos mais vendidos no ano indicando o total filial a filial*/
struct list* getMaxAll(struct Sale**,int,struct list*);

/*função auxuliar para o calculo da função anterior que acede aos totais de um nodo principal*/
struct aux** getMaxAllSub(struct Sale*,struct aux**);

/*calcula o total de clientes que compraram um produto*/
void getTotalClientes(struct sales*,int*);

/*calculo dos n produtos e total gasto, por um cliente*/
struct list* getMaxNForClient(struct Sale**,char*,int,struct list*);

/*precorre toda a estrutura principal chamando um função auxiliar para a estrutura secundária*/
struct aux2** getMaxNForClientSub(struct Sale*,char*, struct aux2**);

/*insere na estrutura auxiliar da query toda a informação relativa à venda(informação na estrutura secundária)*/
struct aux2** getMaxNForClientSubSub(struct sales*,char*, char*, struct aux2**);

/*lê,valida, insere em sistema toda a informação relativa a uma venda tanto na faturação global e filiais*/
AVLS* loadFat(AVLS* xpto,Clientes tree,Produtos* ht, char* fl);
AVLS* loadFil(AVLS* xpto,Clientes tree,Produtos* ht, char* fl);
AVLS* loadFFasts(AVLS*,AVLS*, Clientes,Produtos*, char*,int*);

#endif
