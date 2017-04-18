%{

#include<stdio.h>
#include "lexical_an.h"

int type = -1;

%}

%%

[\n|\t|\r|" "] { };

"{"([^("}"|\n)]*)"}" { };

"{"([^("}"|"\n")]*) { type = COMENTARIO_NAO_FECHADO; return ERRO; };

([^("{"|"\n")]*)"}" {  type = COMENTARIO_NAO_ABERTO; return ERRO; } 

"if"|"program"|"begin"|"end"|"const"|"var"|"real"|"integer"|"procedure"|"else"|"while"|"do"|"if"|"then"|"for"|"to"|"read"|"write" { return PALAVRA_RESERVADA;}

[0-9]+[.][0-9]+ { return NUMERO_REAL;}
 
[0-9]+ { return NUMERO_INTEIRO;}

[a-zA-Z][a-zA-Z0-9]* { return IDENTIFICADOR;}

"(" { type = ABRE_PAREN;    return SIMBOLO;}
")" { type = FECHA_PAREN;   return SIMBOLO;}
";" { type = PONTO_VIRGULA; return SIMBOLO;}
"." { type = PONTO;         return SIMBOLO;}
"," { type = VIRGULA;       return SIMBOLO;}
":" { type = DOIS_PONTOS;   return SIMBOLO;}


"+" { type = SOMA;          return ARIT_OP;}
"-" { type = SUBTRACAO;     return ARIT_OP;}
"*" { type = MULTIPLICACAO; return ARIT_OP;}
"/" { type = DIVISAO;       return ARIT_OP;}

":=" { return ATRIB_OP;}

"="  { type = IGUAL;       return REL_OP;}
"<>" { type = DIFERENTE;   return REL_OP;}
">"  { type = MAIOR;       return REL_OP;}
"<"  { type = MENOR;       return REL_OP;}
">=" { type = MAIOR_IGUAL; return REL_OP;}
"<=" { type = MENOR_IGUAL; return REL_OP;}


[0-9]+[a-zA-Z|.]+[a-zA-Z0-9|.]* { type = NUM_MAL_FORM; return ERRO; }

. {type = NAO_REC; return ERRO; }

%%

int yywrap()
{
	return 1;
}

int main(void)
{
	int ntoken = yylex();
	printf("==========================================================\n");
	while(ntoken)
	{
		printf("%s - %s", yytext, names[ntoken]);
		switch(ntoken)
		{
			case SIMBOLO:
				printf(" %s\n", simbolos[type]);
				break;
			case ERRO:
				printf(" (%s)\n", erros[type]);
				break;
			case ARIT_OP:
				printf(" %s\n", arit_ops[type]);
				break;
			case REL_OP:
				printf(" %s\n", rel_ops[type]);
				break;
			default:
				printf("\n");
		}
		ntoken = yylex();
	}
	printf("==========================================================\n");
	return 0;
}




