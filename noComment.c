#include <stdio.h>

/*
Ejercicio 1-23. Escriba un programa para eliminar todos los comentarios de un
programa en C. No olvide manejar apropiadamente las cadenas entre comillas y
las constantes de carácter. Los comentarios de C no se anidan.
*/

void analizarComillas();
void analizarApostrofes();
void analizarComentarios();

int main (void) {
	char c = getchar();
	
	while(c != EOF) {
		if(c == '"'){ 
			putchar(c);
			analizarComillas();
		}
		else if(c == '\''){
			putchar(c);
			analizarApostrofes();
		}
		else if(c == '/') {
			analizarComentarios();
		}
		else {
			putchar(c);
		}
		if (c != EOF) {
			c = getchar();
		}
	}
}

void analizarComillas() {
	char c = getchar();
	while(c != '"') {
		putchar(c);
		c = getchar();
		if (c == '\\') {
			putchar(c);
			c = getchar();
			putchar(c);
			c = getchar();
		}
	}
	putchar(c);
}

void analizarApostrofes() {
	char c = getchar();
	while(c != '\'') {
		putchar(c);
		c = getchar();
		if(c == '\\') {
			putchar(c);
			c = getchar();
			putchar(c);
			c = getchar();
		}
	}
	putchar(c);
}

void analizarComentarios() {
	char c = getchar();
	if(c == '/') {
		while(c != '\n' && c != EOF) {
			c = getchar();
		}
		if (c != EOF) {
			putchar(c);
		}
	} else if (c == '*'){
		c = getchar();
		while(c != '*' && c != EOF){
			c = getchar();
			if(c == '*'){
				c = getchar();
				if(c == '/'){
					return;
				}
			}
		}
	}
	else {
			putchar('/');
		if (c != EOF) {
			putchar(c);
		}
	}
}
