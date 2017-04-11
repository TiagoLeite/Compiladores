%{

#include<stdio.h>
#define ABRE_PAREN 0
#define PTO_VIRGULA 1

#define PALAVRA_RESERVADA 1
#define NUMERO_INTEIRO 2
#define IDENTIFICADOR 3
#define SIMBOLO 4
#define NAO_RECONHECIDO 5

char *names[] = {NULL, "palavra reservada", "numero inteiro", "identificador", "simbolo", "nao reconhecido"};
char *simbolos[] = {"abre parenteses", "ponto e virgula"};
int type = -1;

%}

%%
[\n|\t|\r] {};
"if" { return PALAVRA_RESERVADA;}
(-)?[0-9]+ {return NUMERO_INTEIRO;}
[a-zA-Z][a-zA-Z0-9]* { return IDENTIFICADOR;}
"(" { type = ABRE_PAREN; return SIMBOLO;}
";" { type = PTO_VIRGULA; return SIMBOLO;}
. {return NAO_RECONHECIDO;}
%%

int yywrap()
{
	return 1;
}

int main(void)
{
	int ntoken = yylex();
	printf("=================\n");
	while(ntoken)
	{
		printf("%s - %s", yytext, names[ntoken]);
		if(ntoken == SIMBOLO)
			printf(" %s", simbolos[type]);
		printf("\n");
		ntoken = yylex();
	}
	printf("\n=================\n");
}
