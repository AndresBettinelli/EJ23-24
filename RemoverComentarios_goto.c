#include <stdio.h>

/*
 TP FINAL SSL
 Ejercicio 1-23: Remover Comentarios
 Grupo: 4
 2016
 */

main(){
	
	int c;

CODIGO:	
	c=getchar();
	switch(c)
	{
		case '/':
			c=getchar();
			if (c=='/'){
				goto COMENTARIO_LINEA;
			}else if (c=='*'){
				goto COMENTARIO_BLOQUE;
			} break;
        
		case EOF:
     		goto END;			
		
		case '\'':
			putchar(c);
			goto LITERAL_CARACTER;
			
		case '"':
			putchar(c);
			goto LITERAL_CEDENA;
	
		default:
            	putchar(c);
		goto CODIGO;					
	}  
			
COMENTARIO_BLOQUE:

	switch(getchar())
	{
		case '*':
			c=getchar();
			if (c=='/'){
				goto CODIGO;
				} break;
		default:
            	goto COMENTARIO_BLOQUE;	 
			
	}		

COMENTARIO_LINEA:

	switch(getchar())
	{
		case '\n':
			goto CODIGO;
			break;
		
		default:
            	goto COMENTARIO_LINEA;	 
	}
			
END:
    printf("\nLa ejecución fue exitosa");
    return 0;
    
ERROR:
	printf("\nLa ejecucion NO fue exitosa");
	return 0;
	    
LITERAL_CEDENA:

    switch(c=getchar())
    {
        case '\\':
            //Omito el caracter escapado
            getchar();
            goto LITERAL_CEDENA;
            break;
        case '"':
            putchar(c);
	    goto CODIGO;
            break;
        case '\n':
            goto ERROR;
            break;
 
        default:
            putchar(c);
	    goto LITERAL_CEDENA;
            break;
    }
LITERAL_CARACTER:

	switch(c=getchar())
    {
        case '\\':
            //Omito el caracter escapado
            getchar();
            goto LITERAL_CARACTER;
            break;
        case '\'':
            putchar(c);
	    goto CODIGO;
            break;
        case '\n':
            goto ERROR;
            break;
        default:
            putchar(c);
	    goto LITERAL_CARACTER;
            break;
    }   		
}
