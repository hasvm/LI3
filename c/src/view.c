#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define FILIAIS 3
#define SIZE 32000

/*estrutura da view*/
struct list{
	char* line;
	int size;
	struct list* next;
};

struct view{
	char** list;
	int size;
	int pos;
};


struct multiView{
	char** list;
	int totais;
	int size;
	int pos;
};


char* strdup(char *src){
    char *str;
    char *p;
    int len = 0;

    while (src[len])
        len++;
    str = malloc(len + 1);
    p = str;
    while (*src)
        *p++ = *src++;
    *p = '\0';
    return str;
}

char *strndup(char *s, size_t n) {
    char *p = memchr(s, '\0', n);
    if (p != NULL)
        n = p - s;
    p = malloc(n + 1);
    if (p != NULL) {
        memcpy(p, s, n);
        p[n] = '\0';
    }
    return p;
}

struct view* initView(struct view* view){
	view = NULL;
	return view;
}

struct view* insertView(struct view* view,char* str){

	if(view==NULL){
		view = malloc(sizeof(struct view));
		view->list = malloc(sizeof(char*)*SIZE);
		view->pos=2;
		view->size = SIZE;
		view->list[0]=NULL;
		view->list[1] = strdup(str);
		return view;
	}

	int pos= view->pos;
	int size = view->size;

	if(pos==size){
		char** aux = realloc(view->list,sizeof(char*)*size*2);
		view->list = aux;
		view->size = size*2;
	}

	view->list[pos] = strdup(str);
	view->pos +=1;

	return view;
}

struct multiView* insertMultiView(struct multiView* view,char* str){

	if(view==NULL){
		view = malloc(sizeof(struct multiView));
		view->list = malloc(sizeof(char*)*SIZE);
		view->totais = 1;
		view->pos=2;
		view->size = SIZE;
		view->list[0]=NULL;
		view->list[1] = strdup(str);
		return view;
	}

	int pos= view->pos;
	int size = view->size;

	if(pos==size){
		printf("REa\n");
		char** aux = realloc(view->list,sizeof(char*)*size*2);
		view->list = aux;
		view->size = size*2;
	}

	view->list[pos] = strdup(str);
	view->totais +=1;
	view->pos +=1;

	return view;
}

struct view* addToHeadView(struct view* view,char* str){
	view->list[0] = strdup(str);
	return view;
}


struct multiView** initMultiView(struct multiView** view){
	view = malloc(sizeof(struct multiView)*FILIAIS);
	int i;
	for(i=0;i<FILIAIS;i++){
		*(view+i)=NULL;
	}
	return view;
}

void displayMultiView(struct multiView** view){

	int i,j,k,a,size,flag;
	
	for(k=0;k<FILIAIS;k++){

		flag = 1;
		printf("Filial: %d\n",k+1);

		printf("Total de produtos não comprados: %d\n",(*(view+k))->totais);

		size = (*(view+k))->pos;

		for(i=1;i<size && flag==1;){
				for(j=0;j<10 && i<size;j++){
					printf("%s\n",(*(view+k))->list[i]);
					i++;
					}
		if(i<size){
			do {
				printf("Ver próxima página prima: 1\n");
				printf("Ver próxima filial: 2\n");
				printf("Voltar ao menu anterior prima: 3\n");
				scanf("%d",&a);
				
			switch(a) {

				case 2: flag=0;
					break;

				case 3: return; break;

				}
			 }while(a>3);
		}
	}
	}


}

void destroyMultiView(struct multiView** view){
	int i;
	for(i=0;i<FILIAIS;i++){
		free(*(view+i));
	}
}


void displayView(struct view* view){

	int i,j,a;
	for(i=0;i<view->pos;){
		if(*(view->list+i)==NULL) i++;
		for(j=0;j<10 && i<view->pos;j++){
			printf("%s\n",*(view->list+i));
			i++;
		}
		if(i<view->pos){
			do {
				printf("Ver próxima página prima: 1\n");
				printf("Voltar ao menu anterior prima: 2\n");
				scanf("%d",&a);
				
			switch(a) {
				case 2: return; break;

			}
			}while(a!=1);
		}
	}
		printf("%s\n",view->list[i]);

}

void destroyView(struct view* view){
	free(view->list);
	free(view);
}



/*inicialização da view*/
struct list* initList(struct list* list){
	list = NULL;
	return list;
}



/*adicionar uma linha no final da view*/
struct list* addToList(struct list* list, char* line){

	if(list==NULL){
		struct list* aux = (struct list*) malloc(sizeof(struct list));
		aux->line = strdup(line);
		aux->size = 1;
		aux->next = NULL;
		return aux;
	}
	struct list * aux = list;
	while(aux->next!=NULL){
		aux = aux->next;
	}
	aux->next = malloc(sizeof(struct list));
	aux->next->line = strdup(line);
	aux->next->next = NULL;
	list->size +=1;
	return list;
}

/*Adicionar ordenadamenta linhas ordendas por uma palavra*/
struct list* addToListSortStr(struct list* list, char* line,char* key){

	if(list==NULL){
		struct list* aux = (struct list*) malloc(sizeof(struct list));
		aux->line = strdup(line);
		aux->size = 1;
		aux->next = NULL;
		return aux;
	}

	if(strcmp(list->line,key)>0){
		struct list* aux = (struct list*) malloc(sizeof(struct list));
		aux->line = strdup(line);
		aux->size = list->size+1;
		aux->next = list;
		return aux;
	}

	struct list * aux = list;

	while(aux->next!=NULL && strcmp(aux->next->line,key)<0)
		aux = aux->next;

	if(aux==list){
		struct list* node = malloc(sizeof(struct list));
		node->line = strdup(line);
		node->next = list->next;
		list->size +=1;
		list->next = node;
		return list;
	}

	struct list* aux2 = malloc(sizeof(struct list));
	aux2->next = aux->next;
	aux2->line = strdup(line);
	list->size +=1;
	aux->next = aux2;
	return list;
}

/*Adiconar ordenadamente uma linha por um inteiro*/
struct list* addToListSortInt(struct list* list, char* line,int key){

	if(list==NULL){
		struct list* aux = (struct list*) malloc(sizeof(struct list));
		aux->line = strdup(line);
		aux->size = 1;
		aux->next = NULL;
		return aux;
	}
	int tmp;
	char* str;
	char* keep;
	keep = strdup(list->line);
	str = strtok(keep," ");
	tmp = atoi(str);
	if(tmp>key){
		free(keep);
		struct list* aux = (struct list*) malloc(sizeof(struct list));
		aux->line = strdup(line);
		aux->size = list->size+1;
		aux->next = list;
		return aux;
	}
	free(keep);
	if(list->next==NULL){
		list->next = malloc(sizeof(struct list));
		list->next->line = strdup(line);
		list->next->next = NULL;
		list->size += 1;
		return list;
	}

	struct list * aux = list;
	keep = strdup(aux->next->line);
	str = strtok(keep," ");
	tmp = atoi(str);
	while(aux->next!=NULL && tmp<key){
		free(keep);
		aux = aux->next;
		if(aux->next!=NULL){
			keep = strdup(aux->next->line);
			str = strtok(keep," ");
			tmp = atoi(str);
		}
	}
	
	if(aux==list){
		struct list* node = malloc(sizeof(struct list));
		node->line = strdup(line);
		node->next = list->next;
		list->size +=1;
		list->next = node;
		return list;
	}
	struct list* aux2 = malloc(sizeof(struct list));
	aux2->next = aux->next;
	aux2->line = strdup(line);
	list->size +=1;
	aux->next = aux2;
	return list;
}

/*Adicionar de forma descendente uma linha ordenada por um inteiro*/
struct list* addToListSortIntDesc(struct list* list, char* line,int key){

	if(list==NULL){
		struct list* aux = (struct list*) malloc(sizeof(struct list));
		aux->line = strdup(line);
		aux->size = 1;
		aux->next = NULL;
		return aux;
	}

	int tmp;
	char* str;
	char* keep;
	keep = strdup(list->line);
	str = strtok(keep," ");
	tmp = atoi(str);
	free(keep);

	if(tmp<=key){
		struct list* aux = (struct list*) malloc(sizeof(struct list));
		aux->line = strdup(line);
		aux->size = list->size+1;
		aux->next = list;
		return aux;
	}
	
	if(list->next==NULL){
		list->next = malloc(sizeof(struct list));
		list->next->line = strdup(line);
		list->next->next = NULL;
		list->size += 1;
		return list;
	}

	struct list * aux = list;
	keep = strdup(aux->next->line);
	str = strtok(keep," ");
	tmp = atoi(str);
	while(aux->next!=NULL && tmp>=key){
		free(keep);
		aux = aux->next;
		if(aux->next!=NULL){
			keep = strdup(aux->next->line);
			str = strtok(keep," ");
			tmp = atoi(str);
		}
	}

	if(aux==list){
		struct list* node = malloc(sizeof(struct list));
		node->line = strdup(line);
		node->next = list->next;
		list->size +=1;
		list->next = node;
		return list;
	}
		
	struct list* aux2 = malloc(sizeof(struct list));
	aux2->next = aux->next;
	aux2->line = strdup(line);
	list->size +=1;
	aux->next = aux2;
	return list;
}

/*adiconar um elemento na cabeça da view*/
struct list* addToHeadList(struct list* list,char* line){
	struct list* aux = (struct list*) malloc(sizeof(struct list));
	aux->line = strdup(line);
	aux->size = list->size + 1;
	aux->next = list;
	return aux;
}

/*Adicionar um elemento para tabela de 3 elementos inteiros na view*/
struct list* addToLineList(struct list* list,int* total1,int* total2,int* total3){

	char res[50];
	sprintf(res,"  %d        %d          %d",*total1,*total2,*total3);
	char* lol = strdup(res);
	list = addToList(list,lol);
	free(lol);
	return list;
}

/*eliminar a view*/
void destroyList(struct list* list){
	
	free(list);
}

/*apresentar a view*/
void displayList(struct list* list){
	int i,j,a;

	if(list==NULL){
	printf("Sem resultados de pesquisa\n");
	return;
	}

	int size = list->size;
	for(i=0;i<size;){
			for(j=0;j<10 && i<size;j++){
				printf("%s\n",list->line);
				list = list->next;
				i++;
	}
	if(i<size){
		do {
			printf("Ver próxima página prima: 1\n");
			printf("Voltar ao menu anterior prima: 2\n");
			scanf("%d",&a);
			
		switch(a) {
			case 2: return; break;

		}
		}while(a!=1);
	}
	}
}

/*Aidionar um elemento na view de uma string e um inteiro ordenado de forma descendente por um inteiro*/
struct list* stringBuilderStrIntSortDesc(char* string,int* num,struct list* list){
	char res[50];
	sprintf(res,"%d : %s",*num,string);
	char* lol = strdup(res);
	list = addToListSortIntDesc(list,lol,*num);
	free(lol);
	return list;
}

/*Adicionar uma string e um inteiro como elemento da view*/
struct list* stringBuilderStrInt(char* string,int* num,struct list* list){
	char res[50];
	sprintf(res,"%s %d",string,*(num));
	char* lol = strdup(res);
	list = addToList(list,lol);
	free(lol);
	return list;
}

/*Adicionar uma string e um string como elemento da view*/
struct list* stringBuilderStrStr(char* string,char* str,struct list* list){
	strcat(string,str);
	char* lol = strdup(string);
	list = addToListSortStr(list,lol,string);
	free(lol);
	return list;
}

/*Adicionar uma string e um float como elemento da view*/
struct list* stringBuilderStrFlt(char* string,float* num,struct list* list){
	char res[50];
	sprintf(res,"%s %.2f",string,*(num));
	char* lol = strdup(res);
	list = addToList(list,lol);
	free(lol);
	return list;
}

/*Constroi uma string com uma string e 2 inteiros*/
struct list* stringBuilderStrIntInt(char* string,int* total,int* clt,struct list* list){

	char res[50];
	sprintf(res,"%s --Total: %d --CLientes: %d",string,*total,*clt);
	char* lol = strdup(res);
	list = addToList(list,lol);
	free(lol);

	return list;
}
