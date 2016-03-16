#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DB "db.txt"
#define CLEAR "clear" //clear for unix, cls for windows
#define HEADER_DB "INDICE\t VALOR\t SERIE\t ERRO\t POT.\t QTD \n"

// estrutura global
struct resistor {
	float			vlr,
					err;
	char	 		sre[3];
	float			pot;
	unsigned int 	qtd;
};

void loadfile(struct resistor *resistor_db_tmp, int *tamanho_db);
void listtmpdb(struct resistor *resistor_db_tmp, int *tamanho_db);
void printline(struct resistor *resistor_db_tmp, unsigned int index);
void modtmpdb(struct resistor *resistor_db_tmp, int *tamanho_db);

void main(){
	printf("Inicio. Pressione <Enter> para carregar.\n");
	getchar();
	struct resistor resistor_db_tmp[100];
	int tamanho_db;
	char opcao_menu = 0;

	// inicializa
	loadfile(resistor_db_tmp, &tamanho_db);
	getchar();

	// MENU
	do {
		system(CLEAR);
		printf("Escolha uma das funções abaixo: \n\t\t\t");
		printf("<1> Listar estoque \n\t\t\t");
		printf("<2> Modificar a quantidade de um item \n\t\t\t");
		printf("<3> Incluir novo valor no estoque \n\t\t\t");
		printf("<4> Remover um valor do estoque \n\t\t\t");
		printf("<5> Gravar alterações \n\t\t\t");
		printf("<6> Sair \n");
		printf("Digite o número da opção para selecionar e pressione <Enter>: ");
		opcao_menu = getchar();
		getchar(); //para limpar o buffer
		switch (opcao_menu) {
		case '0':
			break;
		case '1':
			listtmpdb(resistor_db_tmp, &tamanho_db);			
			getchar();
			break;
		case '2':
			modtmpdb(resistor_db_tmp, &tamanho_db);
			getchar();
			break;
		default:
			getchar();
			break;
		}
	} while (1);

}

void listtmpdb(struct resistor *resistor_db_tmp, int *tamanho_db){
	printf(HEADER_DB);
	unsigned int i;
	for(i=0;i<=*tamanho_db;i++){	
		printline(resistor_db_tmp, i);
	}
}

void modtmpdb(struct resistor *resistor_db_tmp, int *tamanho_db){
	unsigned int index, num;

	printf("Entre com o INDICE desejado para modifica-lo\n");
	do{
		scanf("%u", &index);
	} while(index >= *tamanho_db +2);
	index--;
	printf(HEADER_DB);
	printline(resistor_db_tmp, index);
	printf("Qual a nova quantidade? \n");
	scanf("%u", &resistor_db_tmp[index].qtd);
	printf(HEADER_DB);
	printline(resistor_db_tmp, index);
}

void printline(struct resistor *resistor_db_tmp, unsigned int index){
	printf("%u \t %.2f \t %s \t %.2f \t %.2f \t %u \n",
			index+1,
			resistor_db_tmp[index].vlr,
			resistor_db_tmp[index].sre,
			resistor_db_tmp[index].err,
			resistor_db_tmp[index].pot,
			resistor_db_tmp[index].qtd);
}

void loadfile(struct resistor *resistor_db_tmp, int *tamanho_db){
	system(CLEAR);
	FILE *fp;
	unsigned char i = 0;
	struct resistor resistor_tmp;
	fp = fopen(DB, "r+");
	if (fp == NULL){
		printf("Banco de Dados não encontrado");
		exit(-1);
	}else{
		printf("Bando de Dados encontrado\n");

		while(!feof(fp)){
			fscanf(fp, "%f %s %f %f %u",
				&resistor_tmp.vlr,
				resistor_tmp.sre,
				&resistor_tmp.err,
				&resistor_tmp.pot,
				&resistor_tmp.qtd);

			resistor_db_tmp[i].vlr = resistor_tmp.vlr;
			resistor_db_tmp[i].err = resistor_tmp.err;
			resistor_db_tmp[i].pot = resistor_tmp.pot;
			resistor_db_tmp[i].qtd = resistor_tmp.qtd;
			strcpy(resistor_db_tmp[i].sre, resistor_tmp.sre);
			*tamanho_db = i;
			// printline(resistor_db_tmp,i);
			i++;
		}
	}

}