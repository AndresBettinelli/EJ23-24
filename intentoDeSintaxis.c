#include <stdio.h>
#include <assert.h>

/* Enunciado
Ejercicio 1-24. Escriba un programa para revisar los errores de sintaxis rudimentarios
de un programa en C, como paréntesis, llaves y corchetes no alineados. No
olvide las comillas ni los apóstrofos, las secuencias de escape y los comentarios.
(Este programa es difícil si se hace completamente general.).
*/

/* no se como mierda hacer esto, no entiendo la consigna... improvise algo por improvisar. Además falta poco para tener que entregarlo.
Se supone que tengo que leer un archivo con código? se lo ingresa por pantalla todo el codigo? me acuerdo que estaba el getchar 
y el putchar pero no entiendo que hacer.
Espero que al menos sirva la logica y que puedan adecuarlo. 
---------------
Por el momento termina cuando encuentra un error.
Tendriamos que analizar si lo ideal sería que leyera todo el código y vaya tirando los errores o que aborte cuando encuentre uno.
Lo ideal sería que dijera donde está el error, quise poner el assert pero no funcionó
---------------
Otra duda que tengo es que es un error rudimentario de sintaxis. Por ej usar una variable sin declararla es un error de sintaxis pero
no creo que eso sea rudimentario. Por el momento considero que hay que tener en cuenta lo sig:

-Ingresar un \n antes de cerrar unas comillas o apóstrofe (o apóstrofes?) es un error de sintaxis
-Que termine el código antes de cerrar unas comillas o apóstrofes es un error de sintaxis
-Tener en cuenta las secuencias de escape. Ej: '\'', "\"", '\\'
-No hay que analizar errores de sintaxis en los comentarios
-Cuando se abre un comentario del tipo /*, debe cerrarse. No necesariamente en estos comentarios si se encuentra un * o un / tiene que terminar
-No puede haber algo como: [ ( ] )
-No puede terminar el código sin cerrar llaves, corchetes o parentesis
-Un parentesis, corchetes o llaves pueden tener adentro unas comillas o apostrofes que deben estar sintacticamente bien.
-Algo como:
if(
	true // lalalalala
)
... es sintacticamente correcto
-No creo que tengamos que preocuparnos de analizar si cada sentencia (o como se llamen) termina con un ';', no estaba en el enunciado. 
No sé que opinan.

...
Si se me escapó alguno avisen.
*/

void analizarComillas(FILE *origen);
void analizarApostrofes(FILE *origen); //cambien el nombre si les molesta como suena
void analizarComentarios(FILE *origen);
void analizarParentesis(FILE *origen);
void analizarCorchetes(FILE *origen);
void analizarLlaves(FILE *origen);
char devuelveSigLetraSiHay(FILE *origen);

int main(){
 	FILE * acom;
    acom = fopen("prueba.txt","r");
	char c;
	
	fscanf(acom,"%c",&c);
	while(!feof(acom)){
		switch(c){
			case ')':
				printf("No se han abierto correctamente los parentesis");
				abort(); // no me gusta usar esto
			case ']':
				printf("No se han abierto correctamente los corchetes");
				abort();
			case '}':
				printf("No se han abierto correctamente las llaves");
				abort();
			case '(':
				analizarParentesis(acom);
				break;
			case '[':
				analizarCorchetes(acom);
				break;
			case '{':
				analizarLlaves(acom);
				break;
			case '"':
				analizarComillas(acom);
				break;
			case '\'':
				analizarApostrofes(acom);
				break;
			case '/':
				analizarComentarios(acom);
				break;
		}
		fscanf(acom,"%c",&c);
	}
	printf("Sin errores rudimentarios de sintaxis");
}

char devuelveSigLetraSiHay(FILE *origen){
	char letra;
	fscanf(origen,"%c",&letra);
	if(feof(origen)){
			printf("Se ha encontrado fin de archivo antes de lo esperado");
			abort();
	}
	return letra;
}

void analizarParentesis(FILE *origen){
	char letra;
	fscanf(origen,"%c",&letra);
	while(letra != ')'){
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
		letra = devuelveSigLetraSiHay(origen);
	}
}

void analizarCorchetes(FILE *origen){
	char letra;
	fscanf(origen,"%c",&letra);
	while(letra != ']'){
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
		letra = devuelveSigLetraSiHay(origen);
	}
}

void analizarLlaves(FILE *origen){
	char letra;
	fscanf(origen,"%c",&letra);
	while(letra != '}'){
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
		letra = devuelveSigLetraSiHay(origen);
	}
}

void analizarComillas(FILE *origen){
	char c;
	c = devuelveSigLetraSiHay(origen);
	while(c != '"'){
		if(c == '\\'){
			fscanf(origen,"%c",&c);
			if(c == '\n' || feof(origen)){
				printf("No se han cerrado correctamente las comillas");
				abort();
			}
		} else if(c == '\n' || feof(origen)){
			printf("No se han cerrado correctamente las comillas");
			abort();
		}
		c = devuelveSigLetraSiHay(origen);
	}
}

void analizarApostrofes(FILE *origen){
	char c;
	c = devuelveSigLetraSiHay(origen);
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
		c = devuelveSigLetraSiHay(origen);
	}
}

void analizarComentarios(FILE *origen){
	char c;
	fscanf(origen,"%c",&c);
	if(c == '/'){ 
		while(c != '\n' && !feof(origen)){
		fscanf(origen,"%c",&c);
		}
	}
	else if(c == '*'){
		c = devuelveSigLetraSiHay(origen);
		while(c != '*'){
			c = devuelveSigLetraSiHay(origen);
			while(c == '*'){
				c = devuelveSigLetraSiHay(origen);
				if(c == '/'){
					return;
				}
			}	
		}
		while(c == '*'){
			c = devuelveSigLetraSiHay(origen);
			if(c == '/'){
				return;
			}
			while(c != '*'){
				c = devuelveSigLetraSiHay(origen);
			}
		}	
	}
}
