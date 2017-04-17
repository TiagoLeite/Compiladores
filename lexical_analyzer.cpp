/*
 * SCC0217 Linguagens de programação e compiladores
 * Trabalho 1 - Analisador léxico
 *
 * Grupo:
 * Eduardo Kamikabeya         nUSP 9778536
 * Laércio de Oliveira Junior nUSP 8922198
 * Luis Ricardo G. da Silva   nUSP 8937402
 * Otávio Augusto F. Sousa    nUSP 8936801
 * Tiago de Miranda Leite     nUSP 7595289
 *
 * Requisitos para rodar: 
 * - g++ versão 4.9 ou acima
 * - possuir suporte para C++11
 * 
 * Para compilar:
 * $ g++ -std=c++11 lexical_analyzer.cpp -o lexical_analyzer
 *
 * Para executar:
 * $ ./lexical_analyzer < programa_entrada.txt
 */

#include <iostream>
#include <utility>
#include <string>
#include <regex>
#include <map>
#include <set>

using namespace std;

class LexicalAnalyzer {

	string input;                // string que possuirá cada linha do programa de entrada

	const int ID_MAX_SIZE = 10;  // apenas para mostrar o tratamento de erro
	const int NUM_MAX_SIZE = 20; // apenas para mostrar o tratamento de erro

	// estruturas de dados utilizadas
	set<string> reservedWords;                // considerado que para palavras reservadas, o token é a própria palavra
	map<string, string> symbols;              // dado um símbolo str, o token correspondente é symbols[str]
	map<string, string> assignmentOperators;  // dado um operator str, o token correspondente é assignmentOperators[str]
	map<string, string> arithmeticOperators;  // dado um operator str, o token correspondente é arithmeticOperators[str]
	map<string, string> relationalOperators;  // dado um operator str, o token correspondente é relationalOperators[str]

	// métodos que dado uma string, indicam se ela é um símbolo, palavra reservada, etc.
	bool isSymbol(string str)             { return symbols.count(str);             }
	bool isReservedWord(string str)       { return reservedWords.count(str);       }
	bool isAssignmentOperator(string str) { return assignmentOperators.count(str); }
	bool isArithmeticOperator(string str) { return arithmeticOperators.count(str); }
	bool isRelationalOperator(string str) { return relationalOperators.count(str); }

	// inicializa as estruturas de dados
	void initializeDataStructures (void)
	{
		symbols.clear();
		symbols.insert(pair<string, string>(";" , "simbolo_ponto_e_virgula"));
		symbols.insert(pair<string, string>("." , "simbolo_ponto"          ));
		symbols.insert(pair<string, string>(":" , "simbolo_dois_pontos"    ));
		symbols.insert(pair<string, string>("," , "simbolo_virgula"        ));
		symbols.insert(pair<string, string>("(" , "simbolo_abre_parentese" ));
		symbols.insert(pair<string, string>(")" , "simbolo_fecha_parentese"));

		assignmentOperators.clear();
		assignmentOperators.insert(pair<string, string>(":=", "simbolo_atribuicao"));
		// '=' como assignment operator, acontece apenas para variaveis constantes
		assignmentOperators.insert(pair<string, string>("=" , "simbolo_igual"     )); 

		arithmeticOperators.clear();
		arithmeticOperators.insert(pair<string, string>("+" , "simbolo_soma"         ));
		arithmeticOperators.insert(pair<string, string>("-" , "simbolo_subtracao"    ));
		arithmeticOperators.insert(pair<string, string>("*" , "simbolo_multiplicacao"));
		arithmeticOperators.insert(pair<string, string>("/" , "simbolo_divisao"      ));

		relationalOperators.clear();
		relationalOperators.insert(pair<string, string>("=" , "simbolo_igual"         ));
		relationalOperators.insert(pair<string, string>("<>", "simbolo_diferente"     ));
		relationalOperators.insert(pair<string, string>(">=", "simbolo_maior_ou_igual"));
		relationalOperators.insert(pair<string, string>("<=", "simbolo_menor_ou_igual"));
		relationalOperators.insert(pair<string, string>(">" , "simbolo_maior"         ));
		relationalOperators.insert(pair<string, string>("<" , "simbolo_menor"         ));

		reservedWords.clear();
		reservedWords.insert("program"  );
		reservedWords.insert("begin"    );
		reservedWords.insert("end"      );
		reservedWords.insert("const"    );
		reservedWords.insert("var"      );
		reservedWords.insert("real"     );
		reservedWords.insert("integer"  );
		reservedWords.insert("procedure");
		reservedWords.insert("else"     );
		reservedWords.insert("while"    );
		reservedWords.insert("do"       );
		reservedWords.insert("if"       );
		reservedWords.insert("then"     );
		reservedWords.insert("for"      );
		reservedWords.insert("to"       );
		reservedWords.insert("read"     );
		reservedWords.insert("write"    );
	}

	// método que analisa a cadeia e retorna o par <cadeia, token> com o token correspondente
	pair<string, string> analyze(string str)
	{
		// primeiro, tenta reconhecer se é um símbolo ou operador
		if (isSymbol(str))             return pair<string, string>(str, symbols[str]);
		if (isAssignmentOperator(str)) return pair<string, string>(str, assignmentOperators[str]);
		if (isArithmeticOperator(str)) return pair<string, string>(str, arithmeticOperators[str]);
		if (isRelationalOperator(str)) return pair<string, string>(str, relationalOperators[str]);

		// verifica se é palavra reservada ou um ID
		if (isalpha(str[0])) 
		{
			if (isReservedWord(str)) 
				return pair<string, string>(str, "palavra_reservada_" + str);
			else if (str.size() <= ID_MAX_SIZE) // se não ultrapassou o limite de caracteres para IDs
			{
				if (regex_match(str, regex("[[:alpha:]]([[:alpha:]]|[[:digit:]])*")))
					return pair<string, string>(str, "identificador");
				else
					return pair<string, string>(str, "erro - identificador mal formado");
			}
			else
				return pair<string, string>(str, "erro - identificador muito longo, quantidade máxima de caracteres: " + to_string(ID_MAX_SIZE));
		}

		// verifica se é número real ou inteiro
		else if (isdigit(str[0])) 
		{
			if (str.size() <= NUM_MAX_SIZE) // se não ultrapassou o limite de dígitos para números
			{
				if (regex_match(str, regex("[[:digit:]]+\\.[[:digit:]]+")))
					return pair<string, string>(str, "numero_real");
				else if (regex_match(str, regex("[[:digit:]]+")))
					return pair<string, string>(str, "numero_inteiro");
				else 
					return pair<string, string>(str, "erro - numero mal formado");
			}
			else
				return pair<string, string>(str, "erro - numero muito longo, quantidade máxima de dígitos: " + to_string(NUM_MAX_SIZE));
		}

		return pair<string, string>(str, "erro - cadeia não pertence à linguagem");
	}

	public: // começando a área de métodos públicos da classe

	const pair<string, string> END_OF_FILE = make_pair("", "");

	// construtor da classe
	LexicalAnalyzer()
	{
		initializeDataStructures();
	}

	pair<string, string> getNextToken(void)
	{
		// ler o programa de entrada, linha por linha
		if ((input.size() == 0) && (!getline(cin, input)))
			return this->END_OF_FILE;


		string str = "";        // acumula caracteres a serem analisados
		bool isComment = false; // indica o escopo de um comentário 

		// Para cada linha do programa de entrada, várias cadeias serão analisadas pelo
		// analisador léxico. O loop abaixo identifica a proxima cadeia e retorna o token correspondente.

		for(int i = 0; i < input.size(); i++)
		{
			// iniciando a cadeia de caracteres do comentário
			if (input[i] == '{')
			{
				isComment = true;  
				str += input[i];
			}

			// finalizando a cadeia de caracteres do comentário
			else if (input[i] == '}')
			{
				isComment = false; 
				str = "";
			}

			// apenas acumule caracteres se estiver dentro do escopo de comentário
			else if (isComment)
				str += input[i];

			// checa se é preciso olhar o próximo caractere para compor 
			// a maior cadeia de símbolos (primeiro tentar formar os 
			// símbolos: ">=", "<=", ":=", "<>", senão use um caractere por vez)
			else if (i + 1 < input.size() &&
					(isAssignmentOperator(string(1, input[i]) + string(1, input[i + 1])) ||
					 isRelationalOperator(string(1, input[i]) + string(1, input[i + 1]))))
			{
				// se já havia algo em 'str', quer dizer que o simbolo atual indica o fim da cadeia em 'str'
				if (str.size() > 0)
					input = input.substr(i, -1);
				else
				{
					str = string(1, input[i]) + string(1, input[i + 1]);
					input = input.substr(i + 2, -1);
				}
				return analyze(str);
			}

			// apenas acumule caracteres caso seja dígito ou letra
			else if (isalnum(input[i]))
				str += input[i];

			// se o '.' deve ser usado para formar um numero real
			else if (input[i] == '.' && str.size() > 0 && isdigit(str[0]))
			{
				// acumule o maximo de caracteres que podem fazer parte do número (mesmo que mal formado)
				str += input[i];
				for(i++; i < input.size() && isalnum(input[i]); i++)
					str += input[i];

				input = input.substr(i, -1);
				return analyze(str); // analise o número
			}

			// caso o caractere input[i] seja um símbolo que deve ser analisado por si só
			else
			{
				// se já havia algo em 'str', quer dizer que o simbolo atual indica o fim da cadeia em 'str'
				if (str.size() > 0)
					input = input.substr(i, -1);

				// se o caractere input[i] deve ser analisado (se não deve ser skipped)
				else if (input[i] != ' ' && input[i] != '\t' && input[i] != '\r' && input[i] != '\n')
				{
					str = input[i];
					input = input.substr(i + 1, -1);
				}

				// se o caractere input[i] deve ser skipped
				else 
					continue;

				return analyze(str); // analise o que há em 'str'
			}
		}

		input = "";

		if (str.size() > 0) // caso sobrou algo a ser analisado
		{
			// se encontrou o simbolo '{' mas não o simbolo '}'
			if (isComment)
				return pair<string, string>(str, "erro - comentário não fechado");
			else
				return analyze(str);
		}
		else                // nao foi possivel encontrar o proximo token nessa linha, tente outra
			return getNextToken();
	}


} lex;

// programa principal
int main(int argc, char *argv[])
{
	ios::sync_with_stdio(false);

	pair<string, string> ans;

	while((ans = lex.getNextToken()) != lex.END_OF_FILE)
		cout << ans.first << " - " << ans.second << "\n";

	return (0);
}
