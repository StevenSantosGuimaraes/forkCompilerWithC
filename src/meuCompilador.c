#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


#define TAMANHO 10000


enum TipoToken {
	IDENTIFICADOR,      // -> Letra {Letra | Digito}
	LETRA,              // -> a | ... | z | A | ... | Z
	DIGITO,             // -> 0 | ... | 9
	//LITERAL           // -> Inteiro | Boleano | Ponto Flutuante
	INTEIRO,           // -> Digito {Digito}
	//BOLEANO           // -> verdadeiro | falso
	DECIMAL,   // -> Inteiro . Inteiro
	CARACTERE           // -> 'CaractereASCII'
};


const char *nomeTipoToken[] = {
	"Identificador",
	"Letra",
	"Digito",
	"Inteiro",
	"Decimal",
	"Caractere"
};


struct Token {
	enum TipoToken tipo;
	char *valor;
};


void limparTela();
void exibirToken(struct Token registro);
bool lerCodigoFonte(const char *nomeArquivo, char *codigoFonte, int tamanhoMaximo);
struct Token criarToken(enum TipoToken tipo, const char *valor);
void liberarToken(struct Token token);
void liberarTokens(struct Token *token, int qtdTokens);
void analiseLexica();


int main () {

	limparTela();

	struct Token tokens[TAMANHO];
    int contadorToken = 0;

	char nomeArquivo[] = "linguagemFonte.txt";
	char codigoFonte[TAMANHO];

	// Abrir e ler código:
	if(lerCodigoFonte(nomeArquivo, codigoFonte, sizeof(codigoFonte))) {
		printf("Codigo-fonte carregado:\n====\n%s====\n", codigoFonte);
	} else {
		printf("Falha ao ler o arquivo: '%s', com o codigo-fonte!\n", nomeArquivo);
	}

	// Exibir e Liberar memória:
	for (int t = 0; t < TAMANHO; t++) {
		exibirToken(tokens[t]);
		liberarTokens(tokens, t);
	}
	
	return 0;
}


void limparTela() {
	fflush(stdout);
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void exibirToken(struct Token registro) {
	printf("Token: <%s, %s>\n", nomeTipoToken[registro.tipo], registro.valor);
}

bool lerCodigoFonte(const char *nomeArquivo, char *codigoFonte, int tamanhoMaximo) {

	FILE *arquivo = fopen(nomeArquivo, "r");
	if (arquivo == NULL) {
		perror("Erro ao abrir o arquivo!");
		return false;
	}

	char textoLinha[TAMANHO];
	while (fgets(textoLinha, sizeof(textoLinha), arquivo) != NULL) {
		textoLinha[strcspn(textoLinha, "\n")] = '\0';
		strcat(codigoFonte, textoLinha);
		strcat(codigoFonte, "\n");
	}

	// Iniciar Análise Lexica:
	
	fclose(arquivo);
	printf("Analise finalizada.");
	return true;

}

struct Token criarToken(enum TipoToken tipo, const char *valor) {
	struct Token novoToken;
	novoToken.tipo = tipo;
	novoToken.valor = malloc(strlen(valor) + 1);
	strcpy(novoToken.valor, valor);
	return novoToken;
}

void liberarToken(struct Token token) {
	free(token.valor);
}

void liberarTokens(struct Token *token, int qtdTokens) {
	for (int i = 0; i < qtdTokens; i++) {
		liberarToken(token[i]);
	}
	free(token);
}

void analiseLexica() {
	printf("Inicio da analise lexica.");
}
