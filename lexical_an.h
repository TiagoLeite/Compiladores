#define ABRE_PAREN 0
#define FECHA_PAREN 1
#define PONTO_VIRGULA 2
#define VIRGULA 3
#define PONTO 4
#define DOIS_PONTOS 5

#define PALAVRA_RESERVADA 1
#define NUMERO_INTEIRO 2
#define IDENTIFICADOR 3
#define SIMBOLO 4
#define NAO_RECONHECIDO 5
#define NUMERO_MALFORMATADO 6
#define NUMERO_REAL 7

char *names[] = {NULL, "palavra reservada", "numero inteiro", "identificador", "simbolo", "nao reconhecido", 
"numero mal formatado", "numero real"};
char *simbolos[] = {"abre parenteses", "fecha parenteses", "ponto e virgula", "virgula", "ponto", "dois pontos"};
