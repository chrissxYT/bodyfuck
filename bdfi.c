#include <stdio.h>
#include <stdlib.h>

#define TAPE_LEN 1024 * 1024 * 50
#define START_POS TAPE_LEN / 2

char *t;
int tp = START_POS;
long jp;

void call_jp(FILE *i);

void interpret(int op, FILE *i)
{
	switch(op)
	{
		case '+': t[tp]++; break;
		case '-': t[tp]--; break;
		case '<': tp--; break;
		case '>': tp++; break;
		case '[': do{while((op=fgetc(i))!=']')interpret(op,i);}while(t[tp]); break;
		case ',': t[tp] = getchar();
			  fflush(stdout); break;
		case '.': putchar(t[tp]);fflush(stdout);break;
		case '#': printf("%8x-%2x\n",tp,t[tp]);
		case '*': printf("^I%x^\n", t[tp]);
		case '1':jp=jp&0x00ffffffffffffff|t[tp];break;
		case '2':jp=jp&0xff00ffffffffffff|t[tp]>>8;break;
		case '3':jp=jp&0xffff00ffffffffff|t[tp]>>16;break;
		case '4':jp=jp&0xffffff00ffffffff|t[tp]>>24;break;
		case '5':jp=jp&0xffffffff00ffffff|t[tp]>>32;break;
		case '6':jp=jp&0xffffffffff00ffff|t[tp]>>40;break;
		case '7':jp=jp&0xffffffffffff00ff|t[tp]>>48;break;
		case '8':jp=jp&0xffffffffffffff00|t[tp]>>56;break;
		case '=': call_jp(i); break;
	}
}

void call_jp(FILE *i)
{
	int op;
	long rtn = ftell(i);
	fseek(i, jp, SEEK_SET);
	while((op = fgetc(i)) != ']')
	{
		interpret(op,i);
	}
	fseek(i, rtn, SEEK_SET);
}

int main(int argc, char **argv)
{
	FILE *i = fopen(argv[1], "r");
	int c;
	t = malloc(TAPE_LEN);
	while((c = fgetc(i)) != EOF)
	{
		interpret(c, i);
	}
	free(t);
	fclose(i);
}
