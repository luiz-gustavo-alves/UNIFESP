/*
 *   UNIFESP SJC
 *
 *   SEGURANCA COMPUTACIONAL
 *	 RIVEST CIPHER 4 (RC4)
 *   
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TAMANHO MAXIMO DE BYTES DA ENTRADA */
#define MAX_BYTES 256

void swap(unsigned char *a, unsigned char *b) {

	unsigned char temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void KSA(unsigned char *S, unsigned char *key) {

	int keyLen = strlen((char*) key);

	int i;
	int j = 0;

	for (i = 0; i < MAX_BYTES; i++) {
		S[i] = i;
	}

	for (i = 0; i < MAX_BYTES; i++) {
		j = (j + S[i] + key[i % keyLen]) % MAX_BYTES;
		swap(&S[i], &S[j]);
	}
}

unsigned char *PRGA(unsigned char *S, unsigned char *text) {

	int textLen = strlen((char*) text);
	unsigned char cipherText[MAX_BYTES];

	int i = 0;
	int j = 0;

	int k;
	for (k = 0; k < textLen; k++) {
	
		i = (i + 1) % MAX_BYTES;
		j = (j + S[i]) % MAX_BYTES;
		swap(&S[i], &S[j]);
		cipherText[k] = S[(S[i] + S[j]) % MAX_BYTES] ^ text[k];
	}

	for (i = 0; i < textLen; i++) {
		printf("%x:", cipherText[i]);
	}
}

unsigned char *RC4(unsigned char *text, unsigned char *key) {
	
	unsigned char S[MAX_BYTES];

	KSA(S, key);
	PRGA(S, text);
}

int main(int argc, char **argv) {
	
	unsigned char *text = (unsigned char*)malloc(MAX_BYTES * sizeof(unsigned char));
	unsigned char *key = (unsigned char*)malloc(MAX_BYTES * sizeof(unsigned char));

	scanf("%s", text);
  	scanf(" %s", key);
	
	/* EXECUTA ALGORITMO RC4 */
	RC4(text, key);
	
	/* LIBERA MEMORIA QUE FOI ALOCADA DINAMICAMENTE */
	free(text);
	free(key);

	return 0;
}