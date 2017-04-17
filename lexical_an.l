%{

#include<stdio.h>
#include "lexical_an.h"

int type = -1;

%}

%%
[\n|\t|\r|" "] {};
"if" { return PALAVRA_RESERVADA;}
[0-9]*[.][0-9]+ {return NUMERO_REAL;}
[0-9]+ {return NUMERO_INTEIRO;}
[a-zA-Z][a-zA-Z0-9]* { return IDENTIFICADOR;}
[0-9]+[a-zA-Z|.]+[a-zA-Z0-9|.]* { return NUMERO_MALFORMATADO;}
"(" { type = ABRE_PAREN; return SIMBOLO;}
";" { type = PONTO_VIRGULA; return SIMBOLO;}
"." { type = PONTO; return SIMBOLO;}
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
	printf("=================\n");
	return 0;
}
