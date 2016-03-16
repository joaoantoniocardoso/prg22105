#ifndef __data_h
#define __data_h

#include "menu.h" //onde estão as funções que integram o menu
// #include "data.h" //onde a struct é definida
#include "list.h" //a biblioteca para listas duplamente encadiadas heterogeneas
#include "file.h" //onde estão as funções que trabalham com arquivos
#include "tree.h" //onde estão as funções que trabalham com árvores
#include "typedef.h" //onde os typedefs estão definidos

struct resistor{
	unsigned int sre; //6 12 24 48 96 192
	float vlr,
		pot, //em mW (1/4W = 250mW)
		err; //algarismo 1000 vezes maior (5% = 5000)
	unsigned int qtd;
};

#endif