#include "arquivos.h"

int loadfile(struct lista *resistor_db_tmp){
	struct resistor *resistor_tmp;
	FILE *fp;
	fp = fopen(DB, "r");
	system(CLEAR);
	if (fp == NULL){
		#ifdef VERBOSE
			printf("Banco de Dados não encontrado.\n");
		#endif
		//TODO: criar banco de dados
		return -1;
	}else{
		#ifdef VERBOSE
			printf("Bando de Dados encontrado.\n");
		#endif
		while(!feof(fp)){
			//aloca o resistor
			resistor_tmp = (struct resistor*)malloc(sizeof(struct resistor));
			//carrega os dados do resistor
			fscanf(fp, "%f %u %f %f %u",
				&(*resistor_tmp).vlr,
				&(*resistor_tmp).sre,
				&(*resistor_tmp).err,
				&(*resistor_tmp).pot,
				&(*resistor_tmp).qtd);
			//insere ele na lista apenas se não for nulo
			if( ((*resistor_tmp).vlr==0) | ((*resistor_tmp).sre==0) | ((*resistor_tmp).err==0) | ((*resistor_tmp).pot==0))
				free(resistor_tmp);
			else inserir_elemento_final(resistor_db_tmp, resistor_tmp);
		}
	}
	return 0;
}

void *vfprintf_resistor(void *dado, int n, va_list vargs){
	if(dado==NULL) return NULL;
	struct resistor *mdado = (struct resistor*)dado;
	FILE *fp;
	fp = fopen(DB, "a");
	fprintf(fp, "%f %u %f %f %u \n",
		(*mdado).vlr,
		(*mdado).sre,
		(*mdado).err,
		(*mdado).pot,
		(*mdado).qtd);
	fclose(fp);
	return NULL;
}

int savefile(struct lista *resistor_db_tmp){
	struct resistor *rtmp;
	system(CLEAR);
	
	FILE *fp;
	fp = fopen(DB, "w");
	if (fp == NULL){
		#ifdef VERBOSE
			printf("Banco de Dados não encontrado.\n");
		#endif
		fclose(fp);
		return -1;
	}else{
		#ifdef VERBOSE
			printf("Bando de Dados encontrado.\n");
		#endif
		rtmp = (struct resistor*)percorre_lista(resistor_db_tmp, &vfprintf_resistor, 0);
		fclose(fp);
		return 1; //ok
	}
}

