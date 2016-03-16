#ifndef __menu_h
#define __menu_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "menu.h" //onde estão as funções que integram o menu
#include "data.h" //onde a struct é definida
#include "list.h" //a biblioteca para listas duplamente encadiadas heterogeneas
#include "file.h" //onde estão as funções que trabalham com arquivos
#include "tree.h" //onde estão as funções que trabalham com árvores
#include "typedef.h" //onde os typedefs estão definidos

	void *comparar_resistor_A(void *dado, int n, va_list vargs);
	void *buscar_resistor(void *dado, int n, va_list vargs);
	void *imprimir_resistor(void *dado, int n, va_list vargs);
	void *alterar_resistor(void *dado, int n, va_list vargs);

	void menu_L(lheader_t *mlH);
	void menu_B(lheader_t *mlH);
	void menu_M(lheader_t *mlH);
	void menu_I(lheader_t *mlH);
	void menu_R(lheader_t *mlH);
	void menu_S(lheader_t *mlH);
	void menu_Q(lheader_t *mlH);

#endif