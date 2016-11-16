/*
 TP FINAL SSL
 2016
 */

/*getchar() funciona como getc sobre el flujo stdin
  ungetc(stdin) es necesario porque ungetch no esta definido
 */

#include <stdio.h>

#define PILA_MAX_SIZE 1000000

void push(char caracter);
char pop();

int main(int argc, const char * argv[]) {
    
    push('$'); //Inicializo la pila
    
    char c;
    
CODIGO:
    switch(c = getchar()){
        case '"':
            goto LITERAL_CADENA;
        case '\'':
            goto LITERAL_CARACTER;
        case EOF:
            goto END;
        case '{':
            push('}');
            goto CODIGO;
        case '}':
            if(pop() == '}')
                goto CODIGO;
            else
                goto ERROR;
        case '(':
            push(')');
            goto CODIGO;
        case ')':
            if(pop() == ')')
                goto CODIGO;
            else
                goto ERROR;
        case '[':
            push(']');
            goto CODIGO;
        case ']':
            if(pop() == ']')
                goto CODIGO;
            else
                goto ERROR;
        // i es para test, para popear la pila
        case 'i':
            printf("%c", pop());
            goto CODIGO;
        default:
            goto CODIGO;
    }
    
LITERAL_CADENA:
    switch(getchar())
    {
        case '\\':
            //Omito el caracter escapado
            getchar();
            goto LITERAL_CADENA;
            break;
        case '"':
            goto CODIGO;
            break;
        case '\n':
            goto ERROR;
            break;
        default:
            goto LITERAL_CADENA;
            break;
    }
LITERAL_CARACTER:
    switch(getchar())
    {
        case '\\':
            //Omito el caracter escapado
            getchar();
            goto LITERAL_CARACTER;
            break;
        case '\'':
            goto CODIGO;
            break;
        case '\n':
            goto ERROR;
            break;
        default:
            goto LITERAL_CARACTER;
            break;
    }
    
END:
    if(pop()!='$')
        goto ERROR;
    else
        printf("La ejecución fue exitosa");
    return 0;
    
ERROR:
    printf("El lenguaje no es reconocido por el autómata");
    return 0;
}

/*Tratamiento de la pila como un array de tamaño fijo*/

int sp = 0; //Stack pointer
char pila[PILA_MAX_SIZE];

void push(char caracter){
    if(sp < PILA_MAX_SIZE){
        pila[sp++] = caracter;
    }
    else{
        printf("Error: pila llena, no se pudo efectuar push \n");
    }
}
char pop(){
    if(sp > 0){
        return pila[--sp];
    }
    else{
        printf("Error: pila vacía, no se puede realizar un pop \n");
        return 'e';
    }
}
