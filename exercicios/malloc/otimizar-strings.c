#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * removeAreaNaoUsada(char *s);

int main(int argc, char ** argv){
	char *s, *aux;

	s = (char*) malloc(sizeof(char) * 1000);

	printf("Insira uma frase (max 1000 caracteres): \n");
	scanf("%s",s);
	printf("Sua frase foi: '%s'\n", s);
	printf("Endereco do ponteiro s: %p\n", s);
	printf("Endereco do ponteiro aux: %p\n", aux);
	aux=s;
	s=removeAreaNaoUsada(s);
	
	printf("Endereco do ponteiro s: %p\n", s);
	printf("Endereco do ponteiro aux: %p\n", aux);
	free(aux);

}

char * removeAreaNaoUsada(char *s){
	char *nova, *origem, *destino;
	nova = (char*)malloc(sizeof(char)*(strlen(s)+1));
	origem=s;
	destino=nova;
	while(*origem!='\0'){
		*destino=*origem;
		destino++;
		origem++;
	}
	*destino=*origem;
	return nova;
}
