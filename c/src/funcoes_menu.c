#include "funcoes_menu.h"

sgv lerFicheiros(sgv compra){
	int tf;

	char str1[25],str2[20],str3[20];
	do{
		printf("Deseja colocar os nomes dos ficheiros? Sim (1) ou Nao (2).\n");
		scanf("%d",&tf);
		if(tf>2) printf("Introduza uma opcao correta\n");
	 }while(tf>2);
					if (tf==1){
						printf("Nomes do ficheiro dos clientes: \n");
						scanf("%s",str1);
						printf("Nomes do ficheiro dos produtos: \n");
						scanf("%s",str2);
						printf("Nomes do ficheiro das vendas: \n");
						scanf("%s",str3);
						compra = Querie1B(compra,str1,str2,str3);
						printf("A realizar leitura dos ficheiros...\n\n");
						printf("Leitura quase completa...\n\n");
						if(compra!= NULL){
							printf("Leitura completa!\n");
							return compra;
						}
						printf("Erro a ler ficheiros\n");
						
					}
					if (tf == 2){
						printf("A realizar leitura dos ficheiros...\n\n");
						compra = Querie1(compra);
						if(compra!=NULL){
							printf("Leitura completa!\n");
							return compra;
						}
						printf("Erro a ler ficheiros\n");

					}
					printf("Opcao invalida.");
					return compra;
					
}

void determinarListaM(sgv compra){
	char lm[20];
	int i=1;
	do{
		printf("Insira a letra maiuscula: \n");
		scanf("%s",lm);
		if(strcmp(lm,"A")!=0 && strcmp(lm,"Z")!=0){printf("Introduza Apenas uma letra\n"); i=0;}
	}while(i!=1);

		struct view* lista=NULL;
		lista = initView(lista);
		printf("A determinar a lista de produtos iniciados pela letra %s...\n",lm);
		lista = Querie2(compra,lm,lista);
		if(lista!=NULL){ displayView(lista); destroyView(lista);}
		else printf("Não houve resultados a mostrar\n");
	
}

void totalVendasFatu(sgv compra){

	int tf,m;
	char string[30];
	printf("Insira um numero de 1 a 12.\n"
		   "Mes: \n");
	scanf("%d",&m);
	if (m>=1 && m<=12){
		printf("Codigo do produto: \n");
		scanf("%s",string);
		if (strlen(string) == 6) {
			printf("Pretende em filiais (1) ou total (2)?");
			scanf(" %d",&tf);
			if (tf==1){
				printf("A determinar a lista de produtos por filiais...\n");
				struct list* lista=NULL;				
				lista = Querie31(compra,m,string,lista);
				displayList(lista);
				destroyList(lista);
			}
			else if (tf==2){
				struct list* lista=NULL;
				printf("A determinar a lista de produtos total...\n");
				lista = Querie3(compra,m,string,lista);
				displayList(lista);
				destroyList(lista);
			}
			else printf("Opcao invalida.\n");
		}
		else printf("Opcao invalida.\n");
	}
	else printf("Mes invalido.\n");
}

void listaOrdNComprou(sgv compra){
	int tf;
	printf("Pretende em filiais (1) ou total (2)?\n");
	scanf("%d",&tf);
	if (tf==1){
		printf("A determinar a lista ordenada de produtos por filiais...\n");
		struct multiView** lista=NULL;
		lista = initMultiView(lista);
		Querie41(compra,lista);
		if(lista!=NULL){
			displayMultiView(lista);
			destroyMultiView(lista);
		}
	}
	else if (tf==2){
		printf("A determinar a lista ordenada de produtos total...\n");
		struct list* lista=NULL;
		lista = Querie4(compra,lista);
		if(lista!=NULL){
			displayList(lista);
			destroyList(lista);
		}
	}
	else printf ("Opção invalida.\n");
}

void listaOrdCCTFil(sgv compra){

	struct view* lista = NULL;
	lista = initView(lista);
	printf("A determinar a lista ordenada dos codigos dos clientes que realizaram compras em todos os filiais...\n");
	lista = Querie5(compra,lista);
	displayView(lista);
	destroyView(lista);
}

void numeroCNCPNC(sgv compra){

	list lista=NULL;
	lista = initList(lista);
	printf("A determinar o numero de clientes registados que não realizaram compras e a quantidade de produtos que ninguem comprou...\n");
	lista = Querie6(compra,lista);
	displayList(lista);
	destroyList(lista);
}

void tabelaPCM(sgv compra){
	char string[30];

	list lista=NULL;
	lista = initList(lista);
	printf("Codigo Cliente: \n");
	scanf("%s",string);
	if (strlen(string) == 5){
		printf("A criar a tabela organizada por filial...\n");
		lista = Querie7(compra,string,lista);
		displayList(lista);
		destroyList(lista);
	}
	else printf("Codigo invalido.\n");
}

void determinaVRF(sgv compra){
	int mes1,mes2;

	list lista=NULL;
	lista = initList(lista);
	printf("Insira numeros de 1 a 12.\n"
		   "Intervalo de meses: \n");
	scanf("%d",&mes1);
	scanf("%d",&mes2);
	if (mes1>=1 && mes1<=12 && mes2>=1 && mes2<=12 && mes1<mes2) {
	
			printf("A determinar o numero de vendas no internalo de meses %d - %d e o total faturado...\n",mes1,mes2);
			lista = Querie8(compra,mes1,mes2,lista);
			displayList(lista);
			destroyList(lista);
		}

	else printf("Intervalo invalido.\n");
}

void determinaCCNCC(sgv compra){
	char string[30];
	int tf;
	list lista=NULL;
	lista = initList(lista);
	printf("Codigo do produto:\n");
	scanf("%s",string);
	if (strlen(string) == 6) {
		printf("Filial:\n");
		scanf("%d",&tf);
		if (tf>=1 && tf<=3){
			printf("A determinar os codigos e o numero total de clientes que compraram o produto...\n");
			lista = Querie9(compra,tf,string,lista);
			displayList(lista);
			destroyList(lista);
		}
		else printf("A filial nao existe.\n");
	}
	else printf("Codigo invalido.\n");
}

void determinaCPCMC(sgv compra){
	char string[30];
	int m;
	list lista=NULL;
	lista = initList(lista);
	printf("Codigo do cliente:\n");
	scanf("%s",string);
	if (strlen(string) == 5){
		printf("Mes:\n");
		scanf("%d",&m);
		if (m>=1 && m<=12){
			printf("A determinar a lista de codigos de produtos que o cliente mais comprou...\n");
			lista = Querie10(compra,m,string,lista);
			displayList(lista);
			destroyList(lista);
		}
		else printf("Mes invalido.\n");
	}
	else printf("Codigo invalido.\n");
}

void listaPVA(sgv compra){
	printf("A derterminar a lista dos N produtos mais vendidos em todo o ano.\n");
	int n;
	scanf("%d",&n);
	struct list* lista=NULL;
	lista = Querie11(compra,n,lista);
	displayList(lista);
	destroyList(lista);
}

void determinarCNPGM(sgv compra){
	printf("Codigo Cliente:\n");
	char string[7];
	scanf("%s",string);
	if(strlen(string) == 5){
		printf("A determinar os codigos dos N produtos em que o cliente gastou mais dinheiro durante o ano.\n");
		int n;
		scanf("%d",&n);
		struct list* lista=NULL;
		lista = Querie12(compra,string,n,lista);
		displayList(lista);
		destroyList(lista);
	}
	else printf("Codigo invalido.\n");
}

void resultadosL(sgv compra){
	struct list* lista=NULL;
	lista = Querie13(compra,lista);
	displayList(lista);
	destroyList(lista);
}
