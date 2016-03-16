#ifndef __arquivos_h
#define __arquivos_h

#define CLEAR "clear" //clear for unix, cls for windows
#define DB "db.txt" //o arquivo do banco de dados
#define VERBOSE //mostra diversos dialogos intermediarios

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista-duplamente-encadiada-heterogenea.h"
#include "data.h" //onde a struct é definida

int loadfile(struct lista *resistor_db_tmp);
void *vfprintf_resistor(void *dado, int n, va_list vargs);
int savefile(struct lista *resistor_db_tmp);

#endif