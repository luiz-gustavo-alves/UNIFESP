/*
 *   UNIFESP SJC
 *
 *   COMPILADORES
 *   ARQUIVO MAIN
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */

#include "utils.h"

FILE *input_file;

int main(int argc, char *argv[]) {
	
	if (argc < 2) {
		
		printf("Numero de argumentos de entrada invalido ou insuficiente.");
		return -1;
	}	
	
	input_file = fopen(argv[1], "r");
	
	//lexical_analysis(argv[1], input_file);
	syntax_analysis(argv[1], input_file);
	
	return 0;
}