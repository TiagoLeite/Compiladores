#define PALAVRA_RESERVADA 1
#define IDENTIFICADOR 2
#define SIMBOLO 3
#define NUMERO_INTEIRO 4
#define NUMERO_REAL 5
#define ERRO 6

#define ABRE_PAREN 0
#define FECHA_PAREN 1
#define PONTO_VIRGULA 2
#define VIRGULA 3
#define PONTO 4
#define DOIS_PONTOS 5

#define NUM_MAL_FORM 0
#define NAO_REC 1

char *names[] = {NULL, "palavra reservada", "identificador", "simbolo", "numero inteiro", "numero real",
"erro"};

char *simbolos[] = {"abre parenteses", "fecha parenteses", "ponto e virgula", "virgula", "ponto", "dois pontos"};

char *erros[] = {"numero mal formatado", "caracter nao reconhecido"};

