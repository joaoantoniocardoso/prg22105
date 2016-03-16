#include "file.h"
#define DEBUG 1

void printAll(lheader_t *lh1)
{
	node_t *mtree;
	list_t 	*l1, *l2, *l3;
	if((*lh1).start) for(l1 = (*lh1).start; l1; l1 = (*l1).next){
		printf("%f:\n", (*l1).value);
		if((*l1).child) for(l2 = (*l1).child; l2; l2 = (*l2).next){
			printf("\t%f:\n", (*l2).value);
			if((*l2).child) for(l3 = (*l2).child; l3; l3 = (*l3).next){
				printf("\t\t%f:\n\t\t\t", (*l3).value);
				if((mtree = (node_t*)(*l3).child)){
					printTree(mtree);
					putchar('\n');
				}else printf("~err?\n");
			}
		}
	}
}

int loadFile(lheader_t *mlH){
	FILE *fp;
	fp = fopen(DB, "r");
	system(CLEAR);
	if (fp == NULL){
		#ifdef VERBOSE
			printf("Banco de Dados não encontrado.\n");
		#endif
		
		// TODO: criar banco de dados vazio pois ele não existe
		return -1;
	}else{
		#ifdef VERBOSE
			printf("Banco de Dados encontrado.\n");
		#endif

		// Estrutura de dados:
		// lheader sre > list sre > list err > list pot > btree val
		node_t *tval = NULL;
		lheader_t *lhsre = createList(),
							*lherr = createList(),
							*lhpwr = createList();
		
		// Variáveis para armazenamento temporário dos valores extraídos do arquivo.
		float val, err, pwr, sre, qtd;
		
		// Variáveis para armazenar as listas (referência temporária).
		list_t 	*lsre = NULL,
						*lerr = NULL,
						*lpwr = NULL,
						*ltmp = NULL;
						
		// Carrega os próximos resistores do arquivo.
		while(!feof(fp)){
			// Carrega os dados do resistor.
			fscanf(fp, "%f %f %f %f %f", &val, &sre, &err, &pwr, &qtd);
			
			// Insere ele na lista apenas se não for nulo.
			if(val && sre && err && pwr && qtd)
			{

				// Cria os dados na ordem inversa para conseguir linkar os filhos.
				// Os filhos são sempre listas ou árvores, mas mantém-se uma referência
				// para cada nível utilizando um cabeçalho de lista. No fim teremos
				// listas de listas de listas de árvores binárias, ou seja, uma árvore 
				// heterogênea ordenada, e possivelmente desbalanceada.
				getchar();
				
				if((ltmp = searchList(lherr, err))){							// Se err
					lerr = ltmp;																			// Seleciona a lista lerr
					printf("err:\n");
				}else{																						// Se !err
					lerr = insertList(lherr, err, lpwr);							// Insere nova sre
					printf("!err:\n");
				}	
				
				if((ltmp = searchList(lhpwr, pwr))){							// Se pwr
					lpwr = ltmp;																			// Seleciona a lista lpwr
					printf("pwr:\n");
				}else{																						// Se !pwr
					tval = NULL;																			// Força criação de nova árvore
					lpwr = insertList(lhpwr, pwr, tval);							// Insere nova pwr
					printf("!pwr:\n");
				}
				
				if((ltmp = searchList(lhsre, sre))){							// Se sre
					lsre = ltmp;																			// Seleciona a lista lsre
					printf("sre:\n");
				}else{																						// Se !sre
					lsre = insertList(lhsre, sre, lerr);							// Insere nova sre
					printf("!sre:\n");
				}
				
				tval = insertTree(tval, val, qtd);
				(*lpwr).child = tval;															// Associa tval à lpwr
				(*lerr).child = lpwr;															// Associa lpwr à lerr
				(*lsre).child = lerr;															// Associa lerr à lsre
				
				#ifdef DEBUG
				printf(": \t(lhsre)0x%016lx\t(lherr)0x%016lx\t(lhpwr)0x%016lx\n", (unsigned long)lhsre, (unsigned long)lherr, (unsigned long)lhpwr);
				printf(": \t(shsre)0x%016lx\t(sherr)0x%016lx\t(shpwr)0x%016lx\n", (unsigned long)(*lhsre).start, (unsigned long)(*lherr).start, (unsigned long)(*lhpwr).start);
				printf(": \t\t\t\t\t( lerr)0x%016lx\t( lpwr)0x%016lx\t( tval)0x%016lx\n", (unsigned long)lerr, (unsigned long)lpwr, (unsigned long)tval);
				printf(": \t(clsre)0x%016lx\t(clerr)0x%016lx\t(clpwr)0x%016lx\n", (unsigned long)(*lsre).child, (unsigned long)(*lerr).child, (unsigned long)(*lpwr).child);
				printf(": \t(  sre)%.2f\t\t\t(  err)%.2f\t\t\t(  pwr)%.2f\t\t\t(  val)%.2f\n", sre, err, pwr, val);
				
				printTree(tval);
				putchar('\n');
				printList(lhsre);
				printList(lherr);
				printList(lhpwr);
				#endif
				#ifdef VERBOSE
				printAll(lhsre);
				#endif
				
				lsre = lerr = lpwr = ltmp = NULL; // Zera as temporárias (precaução)
				// lherr = lhpwr = NULL;
				
			}
		}

		printAll(lhsre);	
		
		// #ifdef VERBOSE 
		// 	printf("lsre: \n");
		// 	printList(lsre);
		// 	printf("lerr: \n");
		// 	printList(lerr);
		// 	printf("lpwr: \n");
		// 	printList(lpwr);
		// #endif
		
		// associa o cabecalho da lista como a série
		mlH = lhsre;
	}
	#ifdef VERBOSE
		system(CLEAR);
		printf("Banco de Dados Carregado. Pressione <Enter> para continuar.\n");
	#endif
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

#undef DEBUG