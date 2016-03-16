#include <stdio.h>
#include <stdarg.h>

/* print all args one at a time until a negative argument is seen;
	all args are assumed to be of int type */
void printargs(int arg1, ...){
	va_list ap;
	int i;

	va_start(ap, arg1); 
	for (i = arg1; i >= 0; i = va_arg(ap, int)) printf("%d ", i);
	va_end(ap);
	putchar('\n');
}

void MyPrintf(const char *format, ...){
	va_list args;
	char buffer[BUFSIZ];

	va_start(args, format);
	vsnprintf(buffer, sizeof buffer, format, args);
	va_end(args);
	printf("%s\n", buffer);
}

//numero 'n' de argumentos '...' a somar
int summate(int n, ...){
	va_list ap;
	int i = 0;

	va_start(ap, n);
	for (; n; n--)
		i += va_arg(ap, int);
	va_end(ap);
	return i;
}

int main(void){
	MyPrintf("teste: %c, %i", 'a', summate(4, 1, NULL, 3, 2));
	return 0;
}