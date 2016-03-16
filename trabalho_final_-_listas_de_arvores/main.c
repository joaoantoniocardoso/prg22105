#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "lib/menu.h" //onde estão as funções que integram o menu
#include "lib/data.h" //onde a struct é definida
#include "lib/list.h" //a biblioteca para listas duplamente encadiadas heterogeneas
#include "lib/file.h" //onde estão as funções que trabalham com arquivos
#include "lib/tree.h" //onde estão as funções que trabalham com árvores
#include "lib/typedef.h" //onde os typedefs estão definidos

/**
 * Obviously the program stars here
 * @method main
 * @return spects 0, error otherwise (not implementd yet)
 */
int main()
{
	// TODO: cria a lista de resistores
	lheader_t *lres1 = createList();
	
	// TODO: carrega o arquivo
	loadFile(lres1); 
	getchar();

	char opcao_menu = 0;
	// Main menu:
	do{
		system(CLEAR);
		printf("Escolha uma das funções abaixo: \n");
		printf("\t\t\t<L> Listar estoque \n");
		printf("\t\t\t<B> Busca filtrada \n");
		printf("\t\t\t<M> Mudar a quantidade de um item \n");
		printf("\t\t\t<I> Incluir novo valor no estoque \n");
		printf("\t\t\t<R> Remover um valor do estoque \n");
		printf("\t\t\t<S> Salvar alterações \n");
		printf("\t\t\t<Q> Quit \n");
		printf("Digite a opção que deseja e pressione <Enter>: ");
		opcao_menu = getchar();
		getchar(); // cleans buffer
		system(CLEAR); // cleans screen
		
		switch(opcao_menu){
			case 'L':
			case 'l':
				// menu_L(lres1);
				break;
			case 'B':
			case 'b':
				// menu_B(lres1);
				break;
			case 'M':
			case 'm':
				// menu_M(lres1);
				break;
			case 'I':
			case 'i':
				// menu_I(lres1);
				break;
			case 'R':
			case 'r':
				// menu_R(lres1);
				break;
			case 'S':
			case 's':
				// menu_S(lres1);
				break;
			case 'Q':
			case 'q':
				menu_Q(lres1);
				break;
			default:
				printf("Opção inválida\n");
				break;
		}
		getchar();
	}while(1);

	return 0;
}