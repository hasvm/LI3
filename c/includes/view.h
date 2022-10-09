#ifndef VIEW_H
#define VIEW_H

/*estrutura da view*/
typedef struct list* list;
typedef struct multiView** mView;
typedef struct view* view;

/*inicialização das views*/
struct list* initList(struct list*);
struct multiView** initMultiView(struct multiView**);
struct view* initView(struct view*);

/*strdup e strndup declarada*/
char* strdup(char*);
char *strndup(char*, size_t);

/*adicionar uma linha no final da view*/
struct list* addToList(struct list*, char*);
struct view* insertView(struct view*,char*);
struct multiView* insertMultiView(struct multiView*,char*);

/*Adicionar ordenadamenta linhas ordendas por uma palavra*/
struct list* addToListSortStr(struct list*, char*,char*);

/*Adiconar ordenadamente uma linha por um inteiro*/
struct list* addToListSortInt(struct list*, char*,int);

/*Adicionar de forma descendente uma linha ordenada por um inteiro*/
struct list* addToListSortIntDesc(struct list*, char*,int);

/*adiconar um elemento na cabeça da view*/
struct list* addToHeadList(struct list*,char*);
struct view* addToHeadView(struct view*,char*);

/*Adicionar um elemento para tabela de 3 elementos inteiros na view*/
struct list* addToLineList(struct list*,int*,int*,int*);

/*eliminar a view*/
void destroyList(struct list*);
void destroyMultiView(struct multiView**);
void destroyView(struct view*);

/*apresentar a view*/
void displayList(struct list*);
void displayView(struct view*);
void displayMultiView(struct multiView**);

/*Aidionar um elemento na view de uma string e um inteiro ordenado de forma descendente por um inteiro*/
struct list* stringBuilderStrIntSortDesc(char*,int*,struct list*);

/*Adicionar uma string e um inteiro como elemento da view*/
struct list* stringBuilderStrInt(char*,int*,struct list*);

/*Adicionar uma string e um float como elemento da view*/
struct list* stringBuilderStrFlt(char*,float*,struct list*);

/*Adicionar uma string e um string como elemento da view*/
struct list* stringBuilderStrStr(char*,char*,struct list*);

/*Adicionar uma string e 2 inteiros como elemento da view*/
struct list* stringBuilderStrIntInt(char*,int*,int*,struct list*);


#endif
