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

unsigned char cipherText[MAX_BYTES];

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

	int i = 0;
	int j = 0;

	int k;
	for (k = 0; k < textLen; k++) {
	
		i = (i + 1) % MAX_BYTES;
		j = (j + S[i]) % MAX_BYTES;
		swap(&S[i], &S[j]);
		cipherText[k] = S[(S[i] + S[j]) % MAX_BYTES] ^ text[k];
		printf("%d", cipherText[k]);
	}
}

const char *RC4(unsigned char *text, unsigned char *key) {
	
	unsigned char S[MAX_BYTES];

	KSA(S, key);
	PRGA(S, text);

	return cipherText;
}