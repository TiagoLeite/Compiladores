#define PALAVRA_RESERVADA 1
#define IDENTIFICADOR 2
#define SIMBOLO 3
#define NUMERO_INTEIRO 4
#define NUMERO_REAL 5
#define ATRIB_OP 6
#define ARIT_OP 7
#define REL_OP 8
#define ERRO 9

#define ABRE_PAREN 0
#define FECHA_PAREN 1
#define PONTO_VIRGULA 2
#define VIRGULA 3
#define PONTO 4
#define DOIS_PONTOS 5

#define SOMA 0
#define SUBTRACAO 1
#define MULTIPLICACAO 2
#define DIVISAO 3

#define NUM_MAL_FORM 0
#define NAO_REC 1
#define COMENTARIO_NAO_FECHADO 2
#define COMENTARIO_NAO_ABERTO 3


#define IGUAL 0
#define DIFERENTE 1
#define MAIOR 2
#define MENOR 3
#define MAIOR_IGUAL 4
#define MENOR_IGUAL 5



char *names[] = {NULL, "palavra reservada", "identificador", "simbolo", "numero inteiro", "numero real",
"operador de atribuicao", "operador aritmetico", "operador relacional", "erro"};

char *simbolos[] = {"abre parenteses", "fecha parenteses", "ponto e virgula", "virgula", "ponto", "dois pontos"};

char *arit_ops[] = {"soma", "subtracao", "multiplicacao", "divisao"};

char *rel_ops[] = {"igual", "diferente", "maior", "menor", "maior ou igual", "menor ou igual"};

char *erros[] = {"numero mal formatado", "caracter nao reconhecido", "comentario nao fechado", "comentario nao aberto"};

