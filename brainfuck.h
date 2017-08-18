#ifndef BRAINFUCK_H
#define BRAINFUCK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct BFData
{
	char *instructions;
	char *buffer;
	int bufferlength;
	char **callstack;
	int callstackelements;
} BFData;

int isvalidsyntax(char *i);
int execute(BFData *data);
int brainfuck(char *instructions, int buffersize, int maxnestinglevel);

#endif