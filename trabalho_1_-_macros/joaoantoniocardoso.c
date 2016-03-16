/*
	Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina - Campus Florianópolis
	João Antônio Cardoso - joao.maker@gmail.com
	09/10/2015
*/
#include <stdio.h>

#define	set_bit(var,bit)	var |= (1<<bit)
#define	clear_bit(var,bit)	var &= ~(1<<bit)
#define	cpl_bit(var,bit)	var ^= (1<<bit)

void mostra_bin(int num);
void teste_mostra_bin();
void teste_macros();

void main(){
	teste_mostra_bin();
	teste_macros();
}

void mostra_bin(int num){
	for (int i = (8*sizeof(num)-1); i >= 0; i--)
		printf("%i", ( num >> i) & 0x01 );
}

void teste_mostra_bin(){
	int i;
	printf(":: TESTE DA CONVERSAO PARA BINARIO ::\n");
	printf("Digite o numero inteiro (positivo ou negativo) que quiser ver em binario e pressione <Enter>: ");
	scanf("%i", &i);
	printf("%id = ", i);
	mostra_bin( i);
	printf("b\n");
	getchar();
}

void teste_macros(){
	int i, portC=0, size=8*sizeof(int);

	printf(":: TESTE DAS MACROS ::\n");
	printf("\nTestando a macro set_bit(var,bit): \n");
	getchar();
	for(i = 0; i < 2*size ; i++){
		mostra_bin(portC);
		printf("\t -> \t");
		mostra_bin(set_bit(portC,i));
		printf("\n");
	}

	printf("\nTestando a macro clear_bit(var,bit): \n");
	getchar();
	for(i = 0; i < 2*size; i++){
		mostra_bin(portC);
		printf("\t -> \t");
		mostra_bin(clear_bit(portC,i));
		printf("\n");
	}

	printf("\nTestando a macro cpl_bit(var,bit): \n");
	getchar();
	for(i = 0; i < 2*size; i++){
		mostra_bin(1<<i);
	printf("\t -> \t");
		mostra_bin(cpl_bit(portC,i));
		printf("\n");
	}

}
