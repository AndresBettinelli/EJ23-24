#include <stdio.h>

// se asume que el programa a borrar los comentarios no tiene errores sintácticos
/*
Ejercicio 1-23. Escriba un programa para eliminar todos los comentarios de un
programa en C. No olvide manejar apropiadamente las cadenas entre comillas y
las constantes de carácter. Los comentarios de C no se anidan.
*/
// en ningún lado dice que va leer archivos, no sé de donde lee el texto, corríjanlo.

void analizarComillas();
void analizarApostrofes();
void analizarComentarios();

int main (void) {
    /* FILE * acom;
    acom = fopen("prueba.txt","r");
    FILE * afin;
	afin = fopen("Sin Comentarios.txt", "wt");
	*/
	char c = getchar();
	
	// fscanf(acom,"%c",&c);
	while(!EOF){
		if(c == '"'){ 
			putchar(c);
			analizarComillas();
		}
		else if(c == '\''){
			putchar(c);
			analizarApostrofes();
		}
		else if(c == '/'){
			analizarComentarios();
		}
		else {
			putchar(c);
		}
		c = getchar();
	}
}

void analizarComillas() {
	char c = getchar();
	// fscanf(origen,"%c",&c);
	while(c != '"') {
		putchar(c);
		c = getchar();
		// fprintf(destino,"%c", c);
		// fscanf(origen,"%c",&c);
		if (c == '\\') {
			// fprintf(destino,"%c", c);
			putchar(c);
			// fscanf(origen,"%c",&c);
			c = getchar();
			// fprintf(destino,"%c", c);
			putchar(c);
			// fscanf(origen,"%c",&c);
			c = getchar();
		}
	}
	// fprintf(destino,"%c", c);
	putchar(c);
}

void analizarApostrofes() {
	char c = getchar();
	while(c != '\'') {
		//fprintf(destino,"%c", c);
		putchar(c);
		// fscanf(origen,"%c",&c);
		c = getchar();
		if(c == '\\') {
			// fprintf(destino,"%c", c);
			putchar(c);
			// fscanf(origen,"%c",&c);
			c = getchar();
			// fprintf(destino,"%c", c);
			putchar(c);
			// fscanf(origen,"%c",&c);
			c = getchar();
		}
	}
	putchar(c);
}

void analizarComentarios() {
	char c = getchar();
	// fscanf(origen,"%c",&c);
	if(c == '/') {
		while(c != '\n' && !EOF) {
			// fscanf(origen,"%c",&c);
			c = getchar();
		}
		// fprintf(destino,"%c", c);
		putchar(c);
	} else if(c == '*'){
		c = getchar();
		while(c != '*'){
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
		putchar(c);
	}
}
