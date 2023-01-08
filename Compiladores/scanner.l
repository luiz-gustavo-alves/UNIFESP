%{
	#include "utils.h"
	
	char token_str[TOKEN_LEN];

	void lexical_error();
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
              
              	if (current_char == EOF) exit(-1);
              	if (current_char == '\n') line_num++;
              
				if (previous_char == '*' && current_char == '/') break;
              	else previous_char = current_char;

            } while(1);
         }
{IDENTIFIER} { strncpy(token_str, yytext, TOKEN_LEN); return ID; };
{NEWLINE} { line_num++; };
{NUMBER} { strncpy(token_str, yytext, TOKEN_LEN); return NUM; };
{WHITESPACE} { };
<<EOF>> { return FINISHED; };
. {	lexical_error(); return ERROR; }
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
	printf("ERRO LEXICO: %s | Linha: %d\n", token_str, line_num);
	exit(-1);
}
