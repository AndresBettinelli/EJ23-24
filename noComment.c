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
		if(c == '"'){ // encuentra el comienzo de un string
			fprintf(afin,"%c", c);
			fscanf(acom,"%c",&c);
			while(c != '"'){
				fprintf(afin,"%c", c);
				fscanf(acom,"%c",&c);
				if(c == '\\'){
					fprintf(afin,"%c", c);
					fscanf(acom,"%c",&c);
					fprintf(afin,"%c", c);
					fscanf(acom,"%c",&c);
				}
			}
			fprintf(afin,"%c", c);
		}
		
		else if(c == '\''){
			fprintf(afin,"%c", c);
			fscanf(acom,"%c",&c);
			while(c != '\''){
				fprintf(afin,"%c", c);
				fscanf(acom,"%c",&c);
				if(c == '\\'){
					fprintf(afin,"%c", c);
					fscanf(acom,"%c",&c);
					fprintf(afin,"%c", c);
					fscanf(acom,"%c",&c);
				}
			}
			fprintf(afin,"%c", c);
		}
		
		else if(c == '/'){ // encuentra un / 
			fscanf(acom,"%c",&c);
			if(c == '/'){ // encuentra otro / delante del anterior /
				while(c != '\n' && !feof(acom)){
				fscanf(acom,"%c",&c);
				}
				fprintf(afin,"%c", c);
			} else if(c == '*'){
				fscanf(acom,"%c",&c);
				while(c != '*'){
					fscanf(acom,"%c",&c);
					if(c == '*'){
						fscanf(acom,"%c",&c);
						if(c == '/'){
							break; // no me gusta usar esto
						}
					}
				}
			}
			else{
				fprintf(afin,"/%c", c);
			}
		}
		
		else{fprintf(afin,"%c", c);} // sino encontro ", ' o /
		fscanf(acom,"%c",&c);
	}
}
