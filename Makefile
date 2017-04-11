all: clear lex gcc run
lex: lexical_an.l
	lex lexical_an.l
gcc: lex.yy.c
	gcc lex.yy.c -o lexical_an
run:
	./lexical_an <in.txt
clear:
	clear
gitadd:
	git add Makefile in.txt lexical_an.l