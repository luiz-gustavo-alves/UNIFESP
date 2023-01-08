%{
	#include "utils.h"

	void lexical_error();
	char token_id[TOKEN_LEN], token_num[TOKEN_LEN], token_str[TOKEN_LEN];
%}

ALPHA [a-zA-Z]
DIGIT [0-9]
IDENTIFIER {ALPHA}({ALPHA}|{DIGIT})*
NOT_IDENTIFIER {DIGIT}{ALPHA}
NEWLINE \n
NUMBER {DIGIT}+
WHITESPACE [ \t\r]+

%%
"="      { return ASSIGN; }
"]"      { return CBRACKET; }
"}"      { return CKEY;	}
","      { return COMMA; }
")"      { return CPARENT; }	
"!="     { return DIF; }
"else"   { return ELSE; }
"=="     { return EQUAL; }
">"      { return GT; }
">="     { return GTE; }
"if"     { return IF; }
"int"    { return INT; }
"<"      { return LT; }
"<="     { return LTE; }
"-"      { return MINUS; }
"["      { return OBRACKET; }
"{"      { return OKEY; }
"("      { return OPARENT; }
"+"      { return PLUS; }
"return" { return RETURN; }
";"      { return SEMICOLON; }
"/"      { return SLASH; }
"*"      { return TIMES; }
"void"   { return VOID; }
"while"  { return WHILE; }
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
{IDENTIFIER} { strncpy(token_id, yytext, TOKEN_LEN); return ID; };
{NEWLINE} { line_num++; };
{NUMBER} { strncpy(token_num, yytext, TOKEN_LEN); return NUM; };
{WHITESPACE} { };
<<EOF>> { return yytext[0]; };
. { lexical_error(); return ERROR; }
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
    strncpy(token_str, yytext, TOKEN_LEN);

    return current_token;
}

void lexical_error() {
	
	strcat(token_str, yytext);
	printf("\n\n(!) ERRO LEXICO: %s | Linha: %d\n", token_str, line_num);
	exit(-1);
}
