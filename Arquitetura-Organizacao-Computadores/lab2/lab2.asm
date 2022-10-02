# ----------------- LABORATORIO 2 ----------------- #
# ------------------------------------------------- #
# ---- NOME: LUIZ GUSTAVO ALVES ASSIS DA SILVA ---- #
# ------------------------------------------------- #

.data
	str_msg: .asciiz "Insira a mensagem: "
	str_strlen: .asciiz "Numero total de caracteres: "
	str_cripto_msg: .asciiz "Mensagem Criptografada: "
	new_line: .asciiz "\n"
	
	userInput: .space 256
	str_criptografada: .space 256

.text
.globl main

# FUNCAO GLOBAL MAIN
main:

	# IMPRIMIR STRING (str_msg)
	li $v0, 4
	la $a0, str_msg
	syscall
	
	# RECEBE ENTRADA DE DADOS (STRING)
	li $v0, 8
	la $a0, userInput
	li $a1, 256
	syscall
	
	# ARMAZENANDO O VALOR DE ENTRADA NO REGISTRADOR $t0 
	move $s0, $a0  

	# INICIALIZANDO O CONTADOR EM -1.
	li $a1, -1
	
	jal strlen
	move $s1, $v0
	
	# IMPRIMIR STRING (str_strlen)
	li $v0, 4
	la $a0, str_strlen
	syscall
	
	# IMPRIMIR INTEIRO (CONTADOR) 
	li $v0, 1
	move $a0, $s1 		
	syscall
	
	# IMPRIMIR STRING (new_line)
	li $v0, 4
	la $a0, new_line
	syscall
	
	# IMPRIMIR STRING (str_cripto_msg)
	li $v0, 4
	la $a0, str_cripto_msg
	syscall
	
	# MOVENDO ARGUMENTOS E INICIALIZANDO $a2 COMO STRING VAZIA
	move $a0, $s0
	move $a1, $s1
	la $a2, str_criptografada
	
	jal str_cripto
	
	# IMPRIMIR STRING (str_criptografada)
	li $v0, 4
	la $a0, str_criptografada
	syscall

	# PULA PARA O FINAL DO PROGRAMA
	j end	 
	
	
# FUNCAO STRLEN
strlen:	

	# LENDO BYTE DA STRING E ARMAZENANDO EM $t2
	lb $t0, 0($a0)
	
	# VERIFICANDO SE O BYTE CONTEM O CARACTERE NULO '\o'
	beq $t0, $zero, end_strlen
	
	# INCREMENTANDO O ENDEREÇO DO BYTE E O CONTADOR
	addi $a0, $a0, 1
	addi $a1, $a1, 1
	j strlen
	

# FIM DO LOOP (strlen)	
end_strlen:

	move $v0, $a1
	jr $ra
	
	
# FUNCAO STR_CRIPTO	
str_cripto:
	
	# INICIALIZANDO CONTADOR EM 0
	addi $t0, $zero, 0
	
	while:
	
		# LENDO BYTE DA STRING E ARMAZENANDO EM $t1
		lb $t1, 0($a0)
	
		# VERIFICANDO SE O CONTADOR E IGUAL AO TAMANHO DA STRING
		beq $t0, $a1, end_str_cripto
	
		# VERIFICANDO BYTE (ESPACO)
		beq $t1, 32, cripto_espaco
	
		# VERIFICANDO BYTE (a, A)
		beq $t1, 97, cripto_aA
		beq $t1, 65, cripto_aA
	
		# VERIFICANDO BYTE (r, R)
		beq $t1, 114, cripto_rR
		beq $t1, 82, cripto_rR
	
		# VERIFICANDO BYTE (e, E)
		beq $t1, 101, cripto_eE
		beq $t1, 69, cripto_eE
	
		# VERIFICANDO BYTE (o, O)
		beq $t1, 111, cripto_oO
		beq $t1, 79, cripto_oO
	
		# VERIFICANDO BYTE (m, M)
		beq $t1, 109, cripto_mM
		beq $t1, 77, cripto_mM
	
		# VERIFICANDO BYTE (h, H)
		beq $t1, 104, cripto_hH
		beq $t1, 72, cripto_hH
	
		# VERIFICANDO BYTE (l, L)
		beq $t1, 108, cripto_lL
		beq $t1, 76, cripto_lL
	
		# VERIFICANDO BYTE (s, S)
		beq $t1, 115, cripto_sS
		beq $t1, 83, cripto_sS
	
		# VERIFICANDO BYTE (p, P)
		beq $t1, 112, cripto_pP
		beq $t1, 80, cripto_pP
		
		# VERIFICANDO BYTE (0)
		beq $t1, 48, cripto_0
		
		# VERIFICANDO BYTE (1)
		beq $t1, 49, cripto_1
		
		# VERIFICANDO BYTE (2)
		beq $t1, 50, cripto_2
		
		# VERIFICANDO BYTE (3)
		beq $t1, 51, cripto_3
		
		# VERIFICANDO BYTE (4)
		beq $t1, 52, cripto_4
		
		# VERIFICANDO BYTE (5)
		beq $t1, 53, cripto_5
		
		# VERIFICANDO BYTE (6)
		beq $t1, 54, cripto_6
		
		# VERIFICANDO BYTE (7)
		beq $t1, 55, cripto_7
		
		# VERIFICANDO BYTE (8)
		beq $t1, 56, cripto_8
		
		# VERIFICANDO BYTE (9)
		beq $t1, 57, cripto_9
		
	end_cripto:
		
		# ARMAZENANDO O BYTE NA STRING CRIPTOGRAFADA
		sb $t1, str_criptografada($t0)
		
		# INCREMENTANDO O ENDEREÇO DO BYTE E O CONTADOR
		addi $a0, $a0, 1
		addi $a2, $a2, 1
		addi $t0, $t0, 1
		
		j while

# FIM DO LOOP (str_cripto)	
end_str_cripto:
	move $v0, $a2
	jr $ra
	
# FUNCOES QUE CRIPTOGRAFAM A STRING ORIGINAL
cripto_espaco:
	li $t1, '0'
	j end_cripto
	
cripto_aA:
	li $t1, '1'
	j end_cripto

cripto_rR:
	li $t1, '2'
	j end_cripto

cripto_eE:
	li $t1, '3'
	j end_cripto

cripto_oO:
	li $t1, '4'
	j end_cripto

cripto_mM:
	li $t1, '5'
	j end_cripto

cripto_hH:
	li $t1, '6'
	j end_cripto

cripto_lL:
	li $t1, '7'
	j end_cripto

cripto_sS:
	li $t1, '8'
	j end_cripto

cripto_pP:
	li $t1, '9'
	j end_cripto
	
cripto_0:
	li $t1, ' '
	j end_cripto
	
cripto_1:
	li $t1, 'A'
	j end_cripto
	
cripto_2:
	li $t1, 'R'
	j end_cripto	
		
cripto_3:
	li $t1, 'E'
	j end_cripto	
	
cripto_4:
	li $t1, 'O'
	j end_cripto	
	
cripto_5:
	li $t1, 'M'
	j end_cripto
	
cripto_6:
	li $t1, 'H'
	j end_cripto		
				
cripto_7:
	li $t1, 'L'
	j end_cripto	

cripto_8:
	li $t1, 'S'
	j end_cripto
	
cripto_9:
	li $t1, 'P'
	j end_cripto				
			
	# FUNCAO QUE ENCERRA O PROGRAMA		
	end:
		li $v0, 10
		syscall	 
		 	 	 	 	
