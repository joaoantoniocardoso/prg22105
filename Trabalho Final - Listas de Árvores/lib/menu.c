#include "menu.h"

#define RESISTORCABECALHO "\tRESISTENCIA\tSERIE\tERRO\tPOT.\tQTD\n"
#define DEBUG

#ifdef DEBUG 
	int breakpointiterator = 0;
	#define BREAKPOINT printf(":::breakpoint: %i:::", ++breakpointiterator); \
						getchar(); 
#else
	#define BREAKPOINT
#endif

//listar
// void menu_L(lheader_t *mlH){
// 	printf("O estoque atual é: \n");
// 	printf(RESISTORCABECALHO);
// 	percorre_lista(mlH, &imprimir_resistor, 0);
// }

//buscar com filtros
//fazer uma copia da lista com cada filtro aplicado, depois free!
// void menu_B(lheader_t *mlH){
// 
// 	char opcao_menu = 0;
// 	do {
// 		system(CLEAR);
// 		printf("Selecione um filtro para sua busca:\n");
// 		printf("\t\t\t<R> Resistencia \n");
// 		printf("\t\t\t<S> Serie \n");
// 		printf("\t\t\t<E> Erro \n");
// 		printf("\t\t\t<P> Potencia \n");
// 		printf("\t\t\t<Q> Voltar ao menu principal \n");
// 		printf("Digite a opção que deseja e pressione <Enter>: ");
// 		opcao_menu = getchar();
// 		getchar(); //para limpar o buffer
// 		// system(CLEAR);
// 		switch (opcao_menu) {
// 			case 'R':
// 			case 'r':
// 				// comparacao_vlr_sre_err_pot_resistor
// 				break;
// 			case 'S':
// 			case 's':
// 				break;
// 			case 'E':
// 			case 'e':
// 				break;
// 			case 'P':
// 			case 'p':
// 				break;
// 			case 'Q':
// 			case 'q':
// 				opcao_menu = ';';
// 				break;
// 			default:
// 				printf("Opção inválida\n");
// 				break;
// 		}
// 		getchar();
// 	} while (opcao_menu!=';');
// 	
// 
// }
// 
// // FIXME: modificar(?)
// void menu_M(lheader_t *mlH){
// 	struct resistor *rtmp;
// 	float vlr, err, pot;
// 	unsigned int sre, qtd;
// 
// 	//recebe os dados entrados
// 	printf("Entre com o item que deseja alterar no formato <RES> <SERIE> <ERRO> <POT>:\n");
// 	scanf("%f %u %f %f", &vlr, &sre, &err, &pot);
// 	printf("Dado a ser procurado: \n");
// 	printf(RESISTORCABECALHO);
// 	printf("\t%.2f\t\tE%u\t%.2f\t%.2f\t%s\n", vlr, sre, err, pot, "-");
// 	
// 	// faz uma busca pelo dado
// 	printf("Buscando...\n");
// 	rtmp = (struct resistor*)percorre_lista(mlH, &buscar_resistor, 4, vlr, sre, err, pot);
// 	if(rtmp!=NULL){
// 		printf("Resistor encontrado: \n");
// 		printf(RESISTORCABECALHO);
// 		printf("\t%.2f\t\tE%u\t%.2f\t%.2f\t%u\n", (*rtmp).vlr, (*rtmp).sre, (*rtmp).err, (*rtmp).pot, (*rtmp).qtd);
// 
// 		printf("O resistor encontrado tem atualmente %u unidades. Entre com a nova quantidade desejada: ", (*rtmp).qtd);
// 		scanf("%u", &qtd);
// 		rtmp = (struct resistor*)percorre_lista(mlH, &alterar_resistor, 4, vlr, sre, err, pot, qtd);
// 		if(rtmp!=NULL) printf("\nA quantidade foi alterada com sucesso.\n");
// 		else printf("\nFalha ao tentar alterar a quantidade.\n");
// 		
// 	}else printf("Resistor não encontrado.\n");
// 
// 	free(rtmp);
// 
// 	getchar();
// }

// //inserir
// void menu_I(lheader_t *mlH){
// 	struct resistor *rtmp = (struct resistor*)malloc(sizeof(struct resistor)), *rtmp2;
// 	checkMalloc(rtmp);
// 	//recebe os dados entrados
// 	printf("Entre com o resistor que deseja inserir. Formato: <RES> <SERIE> <ERRO> <POT> <QTD> :\n");
// 	scanf("%f %u %f %f %u", &(*rtmp).vlr, &(*rtmp).sre, &(*rtmp).err, &(*rtmp).pot, &(*rtmp).qtd);
// 	getchar();
// 	//TODO: verificar se os dados sao coerentes com as normas consultando uma tabela dos valores possiveis
// 
// 	//verifica se ainda nao existe no estoque
// 	rtmp2 = (struct resistor*)percorre_lista(mlH, &buscar_resistor, 4, (*rtmp).vlr, (*rtmp).sre, (*rtmp).err, (*rtmp).pot);
// 	if(rtmp2==NULL){
// 		if (inserir_item_final(mlH, (void*)rtmp)!=NULL) printf("Resistor inserido com sucesso\n");
// 		// if (inserir_item_ordenado(mlH, (void*)rtmp, &comparar_resistor_A, (*rtmp).vlr, (*rtmp).sre, (*rtmp).err, (*rtmp).pot) != NULL) printf("Resistor inserido com sucesso\n");
// 		else printf("Houve uma falha e o resistor nao foi inserido. \n");
// 
// 	}else {
// 		char a;
// 		printf("Resistor ja existente no estoque. Deseja alterar sua quantidade? <S/N>\n");
// 		a = getchar();
// 		if ((a=='s') | (a=='S')){
// 			printf("Este resistor tem atualmente %u unidades. Entre com a nova quantidade desejada: ", (*rtmp2).qtd);
// 			scanf("%u", &(*rtmp).qtd);
// 			rtmp2 = (struct resistor*)percorre_lista(mlH, &alterar_resistor, 4, (*rtmp).vlr, (*rtmp).sre, (*rtmp).err, (*rtmp).pot, (*rtmp).qtd);
// 			if(rtmp2!=NULL) printf("\nA quantidade foi alterada com sucesso.\n");
// 			else printf("\nFalha ao tentar alterar a quantidade.\n");
// 		}else printf("O resistor nao foi alterado. \n");
// 		getchar();
// 	}
// }
// 
// //remover
// void menu_R(lheader_t *mlH){
// 	struct resistor *rtmp = (struct resistor*)malloc(sizeof(struct resistor)), *rtmp2;
// 	checkMalloc(rtmp);
// 	//recebe os dados entrados
// 	printf("Entre com o resistor que deseja remover. Formato: <RES> <SERIE> <ERRO> <POT>:\n");
// 	scanf("%f %u %f %f", &(*rtmp).vlr, &(*rtmp).sre, &(*rtmp).err, &(*rtmp).pot);
// 	getchar();
// 
// 	// faz uma busca pelo dado
// 	printf("Buscando...\n");
// 	rtmp = (struct resistor*)percorre_lista(mlH, &buscar_resistor, 4, (*rtmp).vlr, (*rtmp).sre, (*rtmp).err, (*rtmp).pot);
// 	if(rtmp!=NULL){
// 		char a;
// 		printf("Resistor encontrado no estoque. \n");
// 		printf(RESISTORCABECALHO);
// 		printf("\t%.2f\t\tE%u\t%.2f\t%.2f\t%u\n", (*rtmp).vlr, (*rtmp).sre, (*rtmp).err, (*rtmp).pot, (*rtmp).qtd);
// 		printf("Deseja realmente remover? ATENCAO: ESTA ACAO NAO PODE SER DESFEITA! <S/N>\n");
// 		a = getchar();
// 		if ((a=='s') | (a=='S')){
// 			// tenta remover o resistor e verifica se foi removido
// 			rtmp2 = remover_item(mlH, ((void *)rtmp));
// 			if (rtmp2!=NULL){
// 				printf("\nO resistor foi removido. \n");
// 			}else printf("O resistor não foi removido. \n");
// 		
// 		}else printf("O resistor não foi removido. \n");
// 	}else printf("O resistor buscado não foi encontrado no estoque. \n");
// 	getchar();
// }
// 
// TODO: limpar tudo!!!
void menu_Q(lheader_t *mlH){
	// freeList(mlH);
	exit(EXIT_SUCCESS);//encerra o programa
}
// 
// //salvar
// void menu_S(lheader_t *mlH){
// 	if(savefile(mlH)) printf("Arquivo salvo com sucesso.\n");
// 	else printf("Falha ao salvar o arquivo.\n");
// }
// 
// void *imprimir_resistor(void *dado, int n, va_list vargs){
// 	if(dado==NULL) return NULL;
// 	struct resistor *mdado = dado;
// 	printf("\t%.2f\t\tE%u\t%.2f\t%.2f\t%u\n", (*mdado).vlr,(*mdado).sre,(*mdado).err,(*mdado).pot,(*mdado).qtd);
// 	return NULL;
// }
// 
// // retorna 1 se maior, 0 se menor, 2 se igual
// void *comparar_resistor_A(void *dado, int n, va_list vargs){
// 	// if(dado==NULL) return NULL;
// 	int *i = (int*)malloc(sizeof(int)); 
// 	checkMalloc(i);
// 	*i = 0;
// 	struct resistor *mdado = dado;
// 
// 	//recebe os parametros em ordem
// 	float vlr = (float) va_arg(vargs, double);
// 	unsigned int sre = (unsigned int) va_arg(vargs, int);
// 	float err = (float) va_arg(vargs, double);
// 	float pot = (float) va_arg(vargs, double);
// 
// 	BREAKPOINT
// 
// 	//arvore de comparações: pot > err > sre > vlr
// 	if((*mdado).pot < pot) *i = 1;
// 	else if((*mdado).pot == pot){
// 		if((*mdado).err < err) *i = 1;
// 		else if((*mdado).err == err){
// 			if((*mdado).sre < sre) *i = 1;
// 			else if((*mdado).sre == sre){
// 				if((*mdado).vlr < vlr) *i = 1;
// 				else if((*mdado).vlr == vlr){
// 					*i = 2; //erro! itens iguais!
// 				}else *i = 0;
// 			}else *i = 0;
// 		}else *i = 0;
// 	}else *i = 0;
// 
// 	BREAKPOINT
// 	return (void *) i;
// }

// void *buscar_resistor(void *dado, int n, va_list vargs){
// 	if(dado==NULL) return NULL;
// 	int a=0;
// 
// 	struct resistor *mdado = dado;
// 	
// 	//recebe os parametros em ordem
// 	float vlr = (float) va_arg(vargs, double);
// 	unsigned int sre = (unsigned int) va_arg(vargs, int);
// 	float err = (float) va_arg(vargs, double);
// 	float pot = (float) va_arg(vargs, double);
// 
// 	//começa a comparação
// 	if(vlr == (*mdado).vlr ) a++;
// 	// printf("(%i,", a);
// 	if((*mdado).sre == sre) a++;
// 	// printf("%i,", a);
// 	if((*mdado).err == err) a++;
// 	// printf("%i,", a);
// 	if((*mdado).pot == pot) a++;
// 	// printf("%i)\n", a);
// 
// 	//retorna
// 	if(a>=4) return mdado;
// 	else return NULL;
// }
// 
// //obs: va_list passa obrigatoriamente os 5 argumentos da struct resistor
// void *alterar_resistor(void *dado, int n, va_list vargs){
// 	if(dado==NULL) return NULL;
// 
// 	struct resistor *mdado = dado;
// 	
// 	//recebe os parametros em ordem e retorna caso uma comparacao falhe
// 	float vlr = (float) va_arg(vargs, double);
// 	if((*mdado).vlr != vlr) return NULL;
// 	unsigned int sre = (unsigned int) va_arg(vargs, int);
// 	if((*mdado).sre != sre) return NULL;
// 	float err = (float) va_arg(vargs, double);
// 	if((*mdado).err != err) return NULL;
// 	float pot = (float) va_arg(vargs, double);
// 	if((*mdado).pot != pot) return NULL;
// 	
// 	//recebe o ultimo parametro se tiver encontrado e retorna
// 	float qtd = (unsigned int) va_arg(vargs, int);
// 	(*mdado).qtd = qtd;
// 	return mdado;
// }