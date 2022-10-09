#include "funcoes_menu.h"
#include"sgv.h"

#define SIZE 26

int main(){


	sgv compra = NULL;
	int c;


	do {
		printf("0 - Sair do programa.\n"
			   "1 - Ler ficheiros.\n"
			   "2 <codigo letra> - Determinar a lista e o numero total de produtos.\n"
			   "3 <mes> <codigo produto> - Determinar e apresentar o numero total de vendas e o total faturado.\n"
			   "4 <filiais/totais> - Determinar a lista ordenada dos produtos que ninguem comprou e o seu total.\n"
			   "5 - Determinar a lista ordenada de codigos de clientes que realizaram compras em todas as filiais.\n"
			   "6 - Determinar o numero de clientes registados que nao realizaram compras e o numero de produtos que ninguem comprou.\n"
			   "7 <codigo cliente> - Criar uma tabela com o numero total de produtos comprados, mes a mes.\n"
			   "8 <intervalo de meses> - Determinar o total de vendas registadas e o total faturado.\n"
			   "9 <codigo produto> <filial> - Determinar os codigos dos clientes e o numero total de clientes que o compraram.\n"
			   "10 <codigo cliente> <mes> - Determinar a lista de codigos de produtos que o cliente mais comprou.\n"
			   "11 - Criar uma lista dos N produtos mais vendidos em todo o ano.\n"
			   "12 <codigo cliente> - Determinar quais os codigos dos N produtos em que gastou mais dinheiro durante o ano.\n"
			   "13 - Apresentar os resultados da leitura dos ficheiros da query1.\n"
			   "Instrucao a realizar: \n");
		scanf("%d",&c);
		switch (c){
			case 0:
				printf ("A sair do programa.\n");
				break;
			case 1:
				compra = initSGV(compra);
				compra = lerFicheiros(compra);
				break;
			case 2:	if(compra==NULL) printf("Sem dados a ler\n");
				if(compra!=NULL) determinarListaM(compra);
					
				break;
			case 3: if(compra==NULL) printf("Sem dados a ler\n");
				if(compra!=NULL) totalVendasFatu(compra);
				break;

			case 4: if(compra==NULL) printf("Sem dados a ler\n");
				if(compra!=NULL) listaOrdNComprou(compra);
				break;

			case 5: if(compra==NULL) printf("Sem dados a ler\n");
				if(compra!=NULL) listaOrdCCTFil(compra);
				break;

			case 6: if(compra==NULL) printf("Sem dados a ler\n");
				if(compra!=NULL) numeroCNCPNC(compra);
				break;

			case 7: if(compra==NULL) printf("Sem dados a ler\n");
				if(compra!=NULL) tabelaPCM(compra);
				break;

			case 8: if(compra==NULL) printf("Sem dados a ler\n");
				if(compra!=NULL) determinaVRF(compra);
				break;

			case 9: if(compra==NULL) printf("Sem dados a ler\n");
				if(compra!=NULL) determinaCCNCC(compra);
				break;

			case 10: if(compra==NULL) printf("Sem dados a ler\n");
				 if(compra!=NULL) determinaCPCMC(compra);
				 break;

			case 11: if(compra==NULL) printf("Sem dados a ler\n");
				 if(compra!=NULL) listaPVA(compra);
				 break;

			case 12: if(compra==NULL) printf("Sem dados a ler\n");
				 if(compra!=NULL) determinarCNPGM(compra);
				 break;

			case 13: if(compra==NULL) printf("Sem dados a ler\n");
				if(compra!=NULL) resultadosL(compra);
				break;

			default:
				system("clear");
                printf("Instrucao nao disponivel.\n");
				break;
		}
	} while (c != 0);

	return 0;
}
