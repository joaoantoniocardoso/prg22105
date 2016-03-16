#ifndef __file_h
#define __file_h

#define CLEAR "clear" //clear for unix, cls for windows
#define DB "db.txt" //o arquivo do banco de dados
#define VERBOSE //mostra diversos dialogos intermediarios

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h" //onde estão as funções que integram o menu
#include "data.h" //onde a struct é definida
#include "list.h" //a biblioteca para listas duplamente encadiadas heterogeneas
// #include "file.h" //onde estão as funções que trabalham com arquivos
#include "tree.h" //onde estão as funções que trabalham com árvores
#include "typedef.h" //onde os typedefs estão definidos

int loadFile(lheader_t *resistor_db_tmp);
void *vfprintf_resistor(void *dado, int n, va_list vargs);
int saveFile(lheader_t *resistor_db_tmp);

#endif