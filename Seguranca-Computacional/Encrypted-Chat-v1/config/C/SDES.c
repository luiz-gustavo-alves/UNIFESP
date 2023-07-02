/*
 *   UNIFESP SJC
 *
 *   SEGURANCA COMPUTACIONAL
 *   SIMPLIFIED DATA ENCRYPTION STANDARD (S-DES)
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *output;

/* BITS E CHAVES */
char *bits;
char *key;
char *k1;
char *k2;

/* PERMUTACOES (PERMUTATIONS) */
int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
int P8[] = {6, 3, 7, 4, 8, 5, 10, 9};
int P4[] = {2, 4, 3, 1};

/* OPERACOES (OPERATIONS) */
int EXP[] = {4, 1, 2, 3, 2, 3, 4, 1};
int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};
int IP_INV[] = {4, 1, 3, 5, 7, 2, 8, 6};

/* S-BOXES */
int S0[4][4] = {1, 0, 3, 2,
				3, 2, 1, 0,
				0, 2, 1, 3,
				3, 1, 3, 2};

int S1[4][4] = {1, 1, 2, 3,
				2, 0, 1, 3,
				3, 0, 1, 0,
				2, 1, 0, 3};

void init() {

    bits = (char*)malloc(8 * sizeof(char));
	key = (char*)malloc(10 * sizeof(char));
	k1 = (char*)malloc(8 * sizeof(char));
	k2 = (char*)malloc(8 * sizeof(char));
}

void finish() {
    
    /* LIBERA MEMORIA QUE FOI ALOCADA DINAMICAMENTE */
	free(key);
	free(bits);
	free(k1);
	free(k2);
}

char *permutate(char *bits, int *permutation, int permutation_size) {
	
	char result[256] = {0};

	int i;
	for (i = 0; i < permutation_size; i++) {
		result[i] = bits[permutation[i] - 1];
	}

	char *output = (char*)malloc(permutation_size * sizeof(char));
	return strcpy(output, result);
}

char *split(char *bits, int init, int split_size) {
	
	char *output = (char*)malloc(split_size * sizeof(char));
	return memcpy(output, &bits[init], split_size);
}

char *join(char *left_bits, char *right_bits, int join_size) {
	
	char result[256] = {0};
	strcpy(result, left_bits);
	strcat(result, right_bits);

	char *output = (char*)malloc(join_size * sizeof(char));
	return strcpy(output, result);
}

char *shift(char *bits, int num_shift, int shift_size) {
	
	int shift_index[shift_size];

	int i; 
	for (i = 0; i < shift_size; i++) {
	
		int index = i + (num_shift + 1);
		
		if (index > shift_size) {
			shift_index[i] = index - shift_size;
		}
		else {
			shift_index[i] = index;
		}
	}
	return permutate(bits, shift_index, shift_size);
}

void key_generation(char *key, char **k1, char **k2) {
	
	char *output;
	char *left_split;
	char *right_split;
	
	output = permutate(key, P10, 10);
	left_split = split(output, 0, 5);
	right_split = split(output, 5, 5);

	left_split = shift(left_split, 1, 5);
	right_split = shift(right_split, 1, 5);
	output = join(left_split, right_split, 10);
	*k1 = permutate(output, P8, 8);

	left_split = shift(left_split, 2, 5);
	right_split = shift(right_split, 2, 5);
	output = join(left_split, right_split, 10);
	*k2 = permutate(output, P8, 8);
}

char *xor(char *bits, char *key, int bits_size) {
	
	char result[256] = {0};

	int i;
	for (i = 0; i < bits_size; i++) {
		
		if (bits[i] == '0' && key[i] == '1' || bits[i] == '1' && key[i] == '0') {
			result[i] = '1';
		}
		else {
			result[i] = '0';
		}
	}

	char *output = (char*)malloc(bits_size * sizeof(char));
	return strcpy(output, result);
}

int binary_to_decimal(char x, char y) {
	
	if (x == '0' && y == '0') return 0;
	if (x == '0' && y == '1') return 1;
	if (x == '1' && y == '0') return 2;
	if (x == '1' && y == '1') return 3;
}

char *decimal_to_binary(int num) {
	
	if (num == 0) return "00";
	if (num == 1) return "01";
	if (num == 2) return "10";
	if (num == 3) return "11";
}

char *get_sbox(char *bits) {
	
	char *left_split;
	char *right_split;

	left_split = split(bits, 0, 4);
	right_split = split(bits, 4, 8);

	/*
 	 *	BIT(1) - BIT(4) => LINHA SBOX
	 *	BIT(2) - BIT(3) => COLUNA SBOX
	 */

	int s0_row, s0_col;
	int s1_row, s1_col;
	
	s0_row = binary_to_decimal(left_split[0], left_split[3]);
	s0_col = binary_to_decimal(left_split[1], left_split[2]);
	s1_row = binary_to_decimal(right_split[0], right_split[3]);
	s1_col = binary_to_decimal(right_split[1], right_split[2]);

	char *s0_output;
	char *s1_output;

	s0_output = decimal_to_binary(S0[s0_row][s0_col]);
	s1_output = decimal_to_binary(S1[s1_row][s1_col]);

	return join(s0_output, s1_output, 4);
}

char *fkey(char *bits, char *key) {
	
	char *output;
	char *left_split;
	char *right_split;
	
	left_split = split(bits, 0, 4);
	right_split = split(bits, 4, 8);
	
	/* EXPANSAO E PERMUTACAO */
	output = permutate(right_split, EXP, 8);
	output = xor(output, key, 8);
	
	/* SBOX */
	output = get_sbox(output);
	output = permutate(output, P4, 4);
	output = xor(output, left_split, 4);
	output = join(output, right_split, 8);

	return output;
}

char *encryption(char *bits, char *k1, char *k2) {
	
	char *output;
	char *left_split;
	char *right_split;
	
	/* PERMUTACAO INICIAL */
	output = permutate(bits, IP, 8);
	output = fkey(output, k1);
	
	/* SWAP */
	char *left_swap;
	char *right_swap;

	left_swap = split(output, 4, 7);
	right_swap = split(output, 0, 4);

	output = join(left_swap, right_swap, 8);
	output = fkey(output, k2);
	output = permutate(output, IP_INV, 8);

	return output;
}

char *decryption(char *bits, char *k1, char *k2) {
	
	char *output;
	char *left_split;
	char *right_split;
	
	/* PERMUTACAO INICIAL */
	output = permutate(bits, IP, 8);
	output = fkey(output, k2);
	
	/* SWAP */
	char *left_swap;
	char *right_swap;

	left_swap = split(output, 4, 7);
	right_swap = split(output, 0, 4);

	output = join(left_swap, right_swap, 8);
	output = fkey(output, k1);
	output = permutate(output, IP_INV, 8);

	return output;
}

const char *simple_des(char *bits, char* key, int op) {

    init();
	
    key_generation(key, &k1, &k2);

	output = (char*)malloc(8 * sizeof(char));

    if (op == 1) {
        output = encryption(bits, k1, k2);
    }
    else if (op == 2) {
        output = decryption(bits, k1, k2);
    }
	else {
		return "";
	}

    finish();
	return output;
}