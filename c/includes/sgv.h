#ifndef SGV_H
#define SGV_H

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "vendas.h"
#include "clientes.h"
#include "produtos.h"
#include "produtosaux.h"

#define SIZE 26

typedef struct sgv* sgv;


sgv initSGV(sgv);

sgv Querie1(sgv);

sgv Querie1B(sgv,char*,char*,char*);

struct view* Querie2(sgv,char*,struct view*);

struct list* Querie3(sgv,int, char*,struct list*);

struct list* Querie31(sgv,int, char*,struct list*);

struct list* Querie4(sgv,struct list*);

struct multiView** Querie41(sgv,struct multiView**);

struct view* Querie5(sgv,struct view*);

struct list* Querie6(sgv,struct list*);

struct list* Querie7(sgv,char*,struct list*);

struct list* Querie8(sgv,int,int,struct list*);

struct list* Querie9(sgv,int,char*,struct list*);

struct list* Querie10(sgv,int,char*,struct list*);

struct list* Querie11(sgv,int, struct list*);

struct list* Querie12(sgv,char*,int, struct list*);

struct list* Querie13(sgv,struct list*);

#endif
