#include "brainfuck.h"

int isvalidsyntax(char *i)
{
	int b = 0;
	if (i)
	{
		while (*i)
		{
			if (*i == '[') {b++;}
			else if (*i == ']') {b--;}
			i++;
		}
	}
	return b == 0;
}

int execute(BFData *data)
{
	char *ip = data->instructions; // puntero a instrucciones
	char *bp = data->buffer; // puntero al buffer
	char *lastbufferelemnt = data->buffer + data->bufferlength;
	char **cp = data->callstack; // puntero al stack de llamadas
	char **lastcallstackelement = data->callstack + data->callstackelements;
	
	int brackets = 0; // cuenta que tan adentro del bucle estamos
	
	while (*ip)
	{
		// salimos si se desborda la memoria
		if (bp >= lastbufferelemnt || cp >= lastcallstackelement) {return -1;}

		// estamos recorriendo las instrucciones normalmente
		if (brackets == 0)
		{
			// incrementa el puntero a los datos
			if (*ip == '>') {bp++;} 
			// decrementa el puntero a los datos
			else if (*ip == '<') {bp--;} 
			// incrementa el valor apuntado
			else if (*ip == '+') {(*bp)++;} 
			// decrementa el valor apuntado
			else if (*ip == '-') {(*bp)--;} 
			// escribe el valor apuntado
			else if (*ip == '.') {putchar(*bp);}
			// lee el valor apuntado
			else if (*ip == ',') {*bp = getchar();}
			// estamos ingresando a un bucle
			else if (*ip == '[')
			{
				// valor != 0, se guarda dirección de inicio del bucle
				if (*bp) {*cp++ = ip;}
				// se cuentan anidaciones para saber donde termina el bucle
				else {brackets++;}
			}
			// estamos saliendo de un bucle
			else if (*ip == ']')
			{
				// valor != 0, se vuelve al inicio del bucle
				if (*bp) {ip = *(cp - 1);}
				// se sale del bucle y se olvida su punto de entrada
				else {cp--;}
			}
		}
		// estamos recorriendo el bucle hasta el final sin ejecutar nada
		else
		{
			if (*ip == '[') {brackets++;}
			else if (*ip == ']') {brackets--;}
		}
		ip++; // siguente instrucción
	}
	return 0;
}

int brainfuck(char *instructions, int buffersize, int maxnestinglevel)
{
	if (isvalidsyntax(instructions))
	{
		char *buffer = calloc(buffersize, sizeof(char));
		if (buffer)
		{
			char **stack = calloc(maxnestinglevel, sizeof(char *));
			if (stack)
			{
				BFData data;
				data.instructions = instructions;
				data.buffer = buffer;
				data.bufferlength = buffersize;
				data.callstack = stack;
				data.callstackelements = maxnestinglevel;
				
				return execute(&data);

				free(stack);
			}
			free(buffer);
		}
	}
	return -1;
}