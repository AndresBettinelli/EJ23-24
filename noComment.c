#include <stdio.h>

// se asume que el programa a borrar los comentarios no tiene errores sintácticos
/*
Ejercicio 1-23. Escriba un programa para eliminar todos los comentarios de un
programa en C. No olvide manejar apropiadamente las cadenas entre comillas y
las constantes de carácter. Los comentarios de C no se anidan.
*/
// en ningún lado dice que va leer archivos, no sé de donde lee el texto, corríjanlo.

int main(){
    FILE * acom;
    acom = fopen("prueba.txt","r");
    FILE * afin;
	afin = fopen("Sin Comentarios.txt", "wt");
	char c; // use fscanf y fprintf
	
	fscanf(acom,"%c",&c);
	while(!feof(acom)){
		if(c == '"'){ 
			fprintf(afin,"%c", c);
			analizarComillas(acom, afin);
		}
		else if(c == '\''){
			fprintf(afin,"%c", c);
			analizarApostrofes(acom, afin);
		}
		else if(c == '/'){
			analizarComentarios(acom, afin);
		}
		else{fprintf(afin,"%c", c);}
		fscanf(acom,"%c",&c);
	}
}

void analizarComillas(FILE *origen, FILE *destino){
	char c;
	fscanf(origen,"%c",&c);
	while(c != '"'){
		fprintf(destino,"%c", c);
		fscanf(origen,"%c",&c);
		if(c == '\\'){
			fprintf(destino,"%c", c);
			fscanf(origen,"%c",&c);
			fprintf(destino,"%c", c);
			fscanf(origen,"%c",&c);
		}
	}
	fprintf(destino,"%c", c);
}

void analizarApostrofes(FILE *origen, FILE *destino){
	char c;
	fscanf(origen,"%c",&c);
	while(c != '\''){
		fprintf(destino,"%c", c);
		fscanf(origen,"%c",&c);
		if(c == '\\'){
			fprintf(destino,"%c", c);
			fscanf(origen,"%c",&c);
			fprintf(destino,"%c", c);
			fscanf(origen,"%c",&c);
		}
	}
	fprintf(destino,"%c", c);
}

void analizarComentarios(FILE *origen, FILE *destino){
	char c;
	fscanf(origen,"%c",&c);
	if(c == '/'){
		while(c != '\n' && !feof(origen)){
		fscanf(origen,"%c",&c);
		}
		fprintf(destino,"%c", c);
	} else if(c == '*'){
		fscanf(origen,"%c",&c);
		while(c != '*'){
			fscanf(origen,"%c",&c);
			if(c == '*'){
				fscanf(origen,"%c",&c);
				if(c == '/'){
					return;
				}
			}
		}
	}
	else{
		fprintf(destino,"/%c", c);
	}
}
