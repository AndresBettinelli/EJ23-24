/*
 TP FINAL SSL
 2016
 */

/*Nota respecto a getc y ungetc
 User getc en lugar de getchar() porque ungetch no existe en C.
 usar getc y ungetc me permiten trabajar sobre el flujo stdin,
 que creo que es lo que se busca.*/

#include <stdio.h>

#define PILA_MAX_SIZE 1000000

void push(char caracter);
char pop();

int main(int argc, const char * argv[]) {
    
    push('$'); //Inicializo la pila
    
    char c;
    
    switch(c = getc(stdin)){
        case '"':
            goto LITERAL_CADENA;
        case EOF:
            goto END;
            break;
        default:
            ungetc(c, stdin);
            goto CODIGO;
            break;
    }
    
CODIGO:
    switch(getchar()){
        case '{':
            push('}');
        case '}':
            if(pop() == '}')
                goto CODIGO;
            else
                //error
                case '(':
                push(')');
        case ')':
            if(pop() == ')')
                goto CODIGO;
            else
                //error
                case '[':
                push(']');
        case ']':
            if(pop() == ']')
                goto CODIGO;
            else
                //error
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
            //ERROR
            break;
        default:
            goto LITERAL_CADENA;
            break;
    }
    
END:
    if(pop(pila)!='$')
        //error
    else
        //CORRECTO
    return 0;
}

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
        printf("Error: pila vacía, no se puede realizar un pop");
        return 'e';
    }
}
