#include <stdio.h>

/* Enunciado
Ejercicio 1-24. Escriba un programa para revisar los errores de sintaxis rudimentarios
de un programa en C, como paréntesis, llaves y corchetes no alineados. No
olvide las comillas ni los apóstrofos, las secuencias de escape y los comentarios.
(Este programa es difícil si se hace completamente general.).
*/

/* no sé como mierda hacer esto, no entiendo la consigna... improvise algo por improvisar. Además falta poco para tener que entregarlo.
Se supone que tengo que leer un archivo con código? me acuerdo que estaba el getchar y el putchar pero no entiendo que hacer.
Espero que al menos sirva la lógica y que puedan adecuarlo.
---------------
Por el momento termina cuando encuentra un error.
Tendríamos que analizar si lo ideal sería que leyera todo el código y vaya tirando los errores o que aborte cuando encuentre uno.
---------------
Otra duda que tengo es que es un error rudimentario de sintaxis. Por ej usar una variable sin declararla es un error de sintaxis pero
no creo que eso sea rudimentario. Por el momento considero que hay que tener en cuenta lo sig:

-Ingresar un \n antes de cerrar unas comillas o apóstrofe (o apóstrofes?) es un error de sintaxis
-Que termine el código antes de cerrar unas comillas o apóstrofes es un error de sintaxis
-Tener en cuenta las secuencias de escape. Ej: '\'', "\"", '\\'
-No hay que analizar errores de sintaxis en los comentarios
-Cuando se abre un comentario del tipo /*, debe cerrarse. No necesariamente en estos comentarios si se encuentra un * o un / tiene que terminar
-No puede haber algo como: [ ( ] )
-No puede terminar el código sin cerrar llaves, corchetes o paréntesis
-Un paréntesis, corchetes o llaves pueden tener adentro unas comillas o apostrofes que deben estar sintácticamente bien.
-Algo como:
if(
	true // lalalalala
)
... es sintácticamente correcto
-No creo que tengamos que preocuparnos de analizar si cada sentencia (o como se llamen) termina con un ';', no estaba en el enunciado. 
No sé que opinan.

...
Es bastante obvio lo que dije, pero se me pudo haber escapado algo. Si ven algo, avisen.
*/

void analizarComillas(FILE *origen);
void analizarApostrofes(FILE *origen);
void analizarComentarios(FILE *origen); //cambien el nombre si les molesta como suena
void analizarParentesis(FILE *origen);
void analizarCorchetes(FILE *origen);
void analizarLlaves(FILE *origen);

int main(){
 	FILE * acom;
    acom = fopen("prueba.txt","r");
	char c;
	
	fscanf(acom,"%c",&c);
	while(!feof(acom)){
		
		switch(c){
			case ')':
				printf("No se han abierto correctamente los parentesis");
				abort();
			case ']':
				printf("No se han abierto correctamente los corchetes");
				abort();
			case '}':
				printf("No se han abierto correctamente las llaves");
				abort();
		}
		
		// encuentra unas comillas
		if(c == '"'){
			analizarComillas(acom);
		}
		
		// encuentra un apóstrofe
		else if(c == '\''){
			analizarApostrofes(acom);
		}
		
		// encuentra comentarios
		else if(c == '/'){ // encuentra un / 
			analizarComentarios(acom);
		}
		
		else if(c == '('){
			analizarParentesis(acom);
		}
		fscanf(acom,"%c",&c);
	}
	printf("Sin errores rudimentarios de sintaxis");
}




void analizarParentesis(FILE *origen){
	char letra;
	fscanf(origen,"%c",&letra); // lee el sig del (
	while(letra != ')'){
		fscanf(origen,"%c",&letra);
		if(feof(origen)){
			printf("No se han cerrado correctamente los parentesis");
			abort(); // esto no me gusta, estoy cansado y bueno...
		}
		switch(letra){
			case '(':
				analizarParentesis(origen);
				break;
			
			case '[':
				analizarCorchetes(origen);
				break;
			
			case '{':
				analizarLlaves(origen);
				break;
			case '"':
				analizarComillas(origen);
				break;
			case '\'':
				analizarApostrofes(origen);
				break;
			case '/':
				analizarComentarios(origen);
				break;
			case ']':
				printf("No se han abierto correctamente los corchetes");
				abort();
				break;
			case '}':
				printf("No se han abierto correctamente las llaves");
				abort();
				break;
		}
	}
}

void analizarCorchetes(FILE *origen){
	char letra;
	fscanf(origen,"%c",&letra); // lee el sig del (
	while(letra != ']'){
		fscanf(origen,"%c",&letra);
		if(feof(origen)){
			printf("No se han cerrado correctamente los corchetes");
			abort();
		}
		switch(letra){
			case '(':
				analizarParentesis(origen);
				break;
			
			case '[':
				analizarCorchetes(origen);
				break;
			
			case '{':
				analizarLlaves(origen);
				break;
			case '"':
				analizarComillas(origen);
				break;
			case '\'':
				analizarApostrofes(origen);
				break;
			case '/':
				analizarComentarios(origen);
				break;
			case ')':
				printf("No se han abierto correctamente los parentesis");
				abort();
			case '}':
				printf("No se han abierto correctamente las llaves");
				abort();
		}
	}
}
void analizarLlaves(FILE *origen){
	char letra;
	fscanf(origen,"%c",&letra); // lee el sig del (
	while(letra != '}'){
		fscanf(origen,"%c",&letra);
		if(feof(origen)){
			printf("No se han cerrado correctamente las llaves");
			abort();
		}
		switch(letra){
			case '(':
				analizarParentesis(origen);
				break;
			
			case '[':
				analizarCorchetes(origen);
				break;
			
			case '{':
				analizarLlaves(origen);
				break;
			case '"':
				analizarComillas(origen);
				break;
			case '\'':
				analizarApostrofes(origen);
				break;
			case '/':
				analizarComentarios(origen);
				break;
			case ')':
				printf("No se han abierto correctamente los parentesis");
				abort();
			case ']':
				printf("No se han abierto correctamente los corchetes");
				abort();
		}
	}
}



void analizarComillas(FILE *origen){
	char c;
	fscanf(origen,"%c",&c);
	if(feof(origen)){
		printf("No se han cerrado correctamente las comillas");
		abort();
	}
	while(c != '"'){
		if(c == '\\'){
			fscanf(origen,"%c",&c);
			if(c == '\n' || feof(origen)){
				printf("No se han cerrado correctamente las comillas");
				abort();
			}
		} else if(c == '\n' || feof(origen)){
			printf("No se han cerrado correctamente las comillas");
			abort(); // por el momento uso esto, puede que un assert sea mejor. Como estoy leyendo de un archivo no importa.
		}
		fscanf(origen,"%c",&c);
		if(feof(origen)){
			printf("No se han cerrado correctamente las comillas");
			abort();
		}
	}
}


void analizarApostrofes(FILE *origen){
	char c;
	fscanf(origen,"%c",&c);
	if(feof(origen)){
		printf("No se han cerrado correctamente los apostrofos");
		abort();
	}
	while(c != '\''){
		if(c == '\\'){
			fscanf(origen,"%c",&c);
			if(c == '\n' || feof(origen)){
				printf("No se han cerrado correctamente los apostrofos");
				abort();
			}
		} else if(c == '\n' || feof(origen)){
			printf("No se han cerrado correctamente los apostrofos");
			abort();
		}
		fscanf(origen,"%c",&c);
		if(feof(origen)){
			printf("No se han cerrado correctamente los apostrofos");
			abort();
		}
	}
}

void analizarComentarios(FILE *origen){
	char c;
	fscanf(origen,"%c",&c);
	if(c == '/'){ // encuentra otro / delante del anterior /
		while(c != '\n' && !feof(origen)){
		fscanf(origen,"%c",&c);
		}
	} else if(c == '*'){
		fscanf(origen,"%c",&c);
		if(feof(origen)){
			printf("No se han cerrado correctamente los comentarios");
			abort();
		}
		while(c != '*'){
			fscanf(origen,"%c",&c);
			if(c == '*'){
				fscanf(origen,"%c",&c);
				if(c == '/'){
					break; // no me gusta usar esto
				} else if(feof(origen)){
					printf("No se han cerrado correctamente los comentarios");
					abort();
				}
			} else if(feof(origen)){
				printf("No se han cerrado correctamente los comentarios");
				abort();
			}
		}
	}
}
