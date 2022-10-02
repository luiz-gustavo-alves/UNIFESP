# ----------------- LABORATORIO 1 ----------------- #
# ------------------------------------------------- #
# ---- NOME: LUIZ GUSTAVO ALVES ASSIS DA SILVA ---- #
# ------------------------------------------------- #

.data
	str_dia: .asciiz "Entre com o dia (DD): \n"
	str_mes: .asciiz "Entre com o mes (MM): \n"
	str_ano: .asciiz "Entre com o ano (AAAA): \n"
	str_nascimento: .asciiz "\nData de Nascimento: "
	caractere: .asciiz "/"
	zero: .asciiz "0"

	str_erro_dia: .asciiz "Dia invalido.\n"
	str_erro_mes: .asciiz "Mes invalido.\n"
	str_erro_ano: .asciiz "Ano invalido.\n"

.text
.globl main

# FUNCAO GLOBAL MAIN
main:

	# PULA PARA FUNCAO DIA E ARMAZENA O RESULTADO NO REGISTRADOR $s0	
	jal dia	
	move $s0, $v0  
	
	# PULA PARA FUNCAO MES E ARMAZENA O RESULTADO NO REGISTRADOR $s1
	jal mes
	move $s1, $v0
	
	# PULA PARA FUNCAOO ANO E ARMAZENA O RESULTADO NO REGISTRADOR $s2
	jal ano
	move $s2, $v0
	
	# IMPRIMIR STRING (str_nascimento)
	la $a0, str_nascimento
	li $v0, 4
	syscall
	
	# IMPRIME O VALOR ATRIBUIDO AO DIA (DD)
	move $t0, $s0
	ble $t0, 9, str_zero_1

end_if_1:
	move $a0, $s0		
	li $v0, 1
	syscall
	
	la $a0, caractere
	li $v0, 4
	syscall
	
	# IMPRIME O VALOR ATRIBUIDO AO MES (MM)
	move $t0, $s1
	ble $t0, 9, str_zero_2
	
end_if_2:
	move $a0, $s1	
	li $v0, 1
	syscall
	
	la $a0, caractere
	li $v0, 4
	syscall
	
	# IMPRIME O VALOR ATRIBUIDO AO ANO (AAAA)
	move $a0, $s2
	li $v0, 1
	syscall
	
	# PULA PARA O FINAL DO PROGRAMA
	jal end
	
	dia:
		# IMPRIMIR STRING (str_dia)
		li $v0, 4
		la $a0, str_dia
		syscall
		
		# RECEBE ENTRADA DE DADOS
		li $v0, 5
		syscall
		
		# VERIFICAR SE O VALOR DO INPUT EH MENOR QUE 1 OU MAIOR QUE 31
		move $t0, $v0
		blt $t0, 1, erro_dia
		bgt $t0, 31, erro_dia
		
		# RETORNA PARA MAIN 
		jr $ra
						
	mes:
		# IMPRIMIR STRING (str_mes)
		li $v0, 4
		la $a0, str_mes
		syscall
		
		# RECEBE ENTRADA DE DADOS
		li $v0, 5
		syscall
		
		
		# VERIFICAR SE O VALOR DO INPUT EH MENOR QUE 1 OU MAIOR QUE 12
		move $t0, $v0
		blt $t0, 1, erro_mes
		bgt $t0, 12, erro_mes
		
		# RETORNA PARA MAIN
		jr $ra
			
	ano:
		# IMPRIMIR STRING (str_ano)
		li $v0, 4
		la $a0, str_ano
		syscall
		
		# RECEBE ENTRADA DE DADOS
		li $v0, 5
		syscall
		
		# VERIFICAR SE O VALOR DO INPUT EH MENOR QUE 1900 OU MAIOR QUE 2021
		move $t0, $v0
		blt $t0, 1900, erro_ano
		bgt $t0, 2021, erro_ano
		
		# RETORNA PARA MAIN
		jr $ra																	

	erro_dia:
		# IMPRIMIR STRING (str_erro_dia)
		li $v0, 4
		la $a0, str_erro_dia
		syscall
		
		# RETORNA PARA FUNCAO DIA
		j dia	
		
	erro_mes:
		# IMPRIMIR STRING (str_erro_mes)
		li $v0, 4
		la $a0, str_erro_mes
		syscall
		
		# RETORNA PARA FUNCAO MES
		j mes
		
	erro_ano:
		# IMPRIMIR STRING (str_erro_ano)
		li $v0, 4
		la $a0, str_erro_ano
		syscall
		
		# RETORNA PARA FUNCAO ANO
		j ano			
		
	# FUNCAO QUE ADICIONA 0 (ZERO) PARA O VALOR DE DIA NO INTERVALO [1,9]
	str_zero_1:
		la $a0, zero
		li $v0, 4
		syscall 
		
		# RETORNA PARA end_if_1
		j end_if_1
		
	# FUNCAO QUE ADICIONA 0 (ZERO) PARA O VALOR DE MES NO INTERVALO [1,9]	
	str_zero_2:
		la $a0, zero
		li $v0, 4
		syscall 
		
		# RETORNA PARA end_if_2
		j end_if_2
		
	# FUNCAO QUE ENCERRA O PROGRAMA		
	end:
		li $v0, 10
		syscall	 	 	 	 	 	 	 
