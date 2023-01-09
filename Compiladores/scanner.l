%{
	#include "utils.h"

	#define CPY_TK strncpy(token_str, yytext, TOKEN_LEN);

	char token_id[TOKEN_LEN]; 
	char token_num[TOKEN_LEN];
	char token_str[TOKEN_LEN];

	int lexical_err;
%}

ALPHA [a-zA-Z]
DIGIT [0-9]
IDENTIFIER {ALPHA}({ALPHA}|{DIGIT})*
NOT_IDENTIFIER {DIGIT}{ALPHA}
NEWLINE \n
NUMBER {DIGIT}+
WHITESPACE [ \t\r]+

%%
"="      { CPY_TK  printf("Linha: %d | Token: ASSIGN | Lexema: %s \n", line_num, token_str); return ASSIGN; }
"]"      { CPY_TK  printf("Linha: %d | Token: CBRACKET | Lexema: %s \n", line_num, token_str); return CBRACKET; }
"}"      { CPY_TK  printf("Linha: %d | Token: CKEY | Lexema: %s \n", line_num, token_str); return CKEY;	}
","      { CPY_TK  printf("Linha: %d | Token: COMMA | Lexema: %s \n", line_num, token_str); return COMMA; }
")"      { CPY_TK  printf("Linha: %d | Token: CPARENT | Lexema: %s \n", line_num, token_str); return CPARENT; }	
"!="     { CPY_TK  printf("Linha: %d | Token: DIF | Lexema: %s \n", line_num, token_str); return DIF; }
"else"   { CPY_TK  printf("Linha: %d | Token: ELSE | Lexema: %s \n", line_num, token_str); return ELSE; }
"=="     { CPY_TK  printf("Linha: %d | Token: EQUAL | Lexema: %s \n", line_num, token_str); return EQUAL; }
">"      { CPY_TK  printf("Linha: %d | Token: GT | Lexema: %s \n", line_num, token_str); return GT; }
">="     { CPY_TK  printf("Linha: %d | Token: GTE | Lexema: %s \n", line_num, token_str); return GTE; }
"if"     { CPY_TK  printf("Linha: %d | Token: IF | Lexema: %s \n", line_num, token_str); return IF; }
"int"    { CPY_TK  printf("Linha: %d | Token: INT | Lexema: %s \n", line_num, token_str); return INT; }
"<"      { CPY_TK  printf("Linha: %d | Token: LT | Lexema: %s \n", line_num, token_str); return LT; }
"<="     { CPY_TK  printf("Linha: %d | Token: LTE | Lexema: %s \n", line_num, token_str); return LTE; }
"-"      { CPY_TK  printf("Linha: %d | Token: MINUS | Lexema: %s \n", line_num, token_str); return MINUS; }
"["      { CPY_TK  printf("Linha: %d | Token: OBRACKET | Lexema: %s \n", line_num, token_str); return OBRACKET; }
"{"      { CPY_TK  printf("Linha: %d | Token: OKEY | Lexema: %s \n", line_num, token_str); return OKEY; }
"("      { CPY_TK  printf("Linha: %d | Token: OPARENT | Lexema: %s \n", line_num, token_str); return OPARENT; }
"+"      { CPY_TK  printf("Linha: %d | Token: PLUS | Lexema: %s \n", line_num, token_str); return PLUS; }
"return" { CPY_TK  printf("Linha: %d | Token: RETURN | Lexema: %s \n", line_num, token_str); return RETURN; }
";"      { CPY_TK  printf("Linha: %d | Token: SEMICOLON | Lexema: %s \n", line_num, token_str); return SEMICOLON; }
"/"      { CPY_TK  printf("Linha: %d | Token: SLASH | Lexema: %s \n", line_num, token_str); return SLASH; }
"*"      { CPY_TK  printf("Linha: %d | Token: TIMES | Lexema: %s \n", line_num, token_str); return TIMES; }
"void"   { CPY_TK  printf("Linha: %d | Token: VOID | Lexema: %s \n", line_num, token_str); return VOID; }
"while"  { CPY_TK  printf("Linha: %d | Token: WHILE | Lexema: %s \n", line_num, token_str); return WHILE; }
"/*"     {
            char current_char, previous_char;

            do 
			{
				
            	current_char = input();
              
              	if (current_char == '\n') line_num++;
              
				if (previous_char == '*' && current_char == '/') break;
              	else previous_char = current_char;

            } while(current_char != '\0');
			
			if (current_char != '/') {
				strncpy(token_str, "Comentario Infinito", TOKEN_LEN);
				lexical_error();
			}
         }
{IDENTIFIER} { strncpy(token_id, yytext, TOKEN_LEN); printf("Linha: %d | Token: ID | Lexema: %s \n", line_num, token_id); return ID; };
{NEWLINE} { printf("\n"); line_num++; };
{NUMBER} { strncpy(token_num, yytext, TOKEN_LEN); printf("Linha: %d | Token: NUM | Lexema: %s \n", line_num, token_num); return NUM; };
{WHITESPACE} { };
<<EOF>> { return yytext[0]; };
. { strncpy(token_str, yytext, TOKEN_LEN); lexical_error(); return ERROR; }
%%

token_t get_token(void) {
    
	static int first_time = 1;
    token_t current_token;

    if (first_time) {
    	
        first_time = 0;
        line_num++;
        yyin = input_file;
        yyout = stdout;
    }

    current_token = yylex();
    return current_token;
}

void lexical_error() {
	
	strncpy(token_str, yytext, TOKEN_LEN);

	printf("\n\n(!) ERRO LEXICO | Linha: %d | Lexema: %s \n", line_num, token_str);

	lexical_err = 1;
	exit(-1);
}
