%{
	#include "utils.h"
	
	void lexical_error();
	
	char token_str[TOKEN_LEN];
%}

DIGIT [0-9]
NUMBER {DIGIT}+
ALPHA [a-zA-Z]
IDENTIFIER {ALPHA}({ALPHA}|{DIGIT})*
NEWLINE \n
WHITESPACE [ \t]+

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
{IDENTIFIER} { return ID; }
{NUMBER} { return NUM; }
{NEWLINE} { line_num++; }
{WHITESPACE} {}
"/*"     {
            char current_char, previous_char;

            do 
			{
              current_char = input();
              
              if(current_char == EOF) break;
              if(current_char == '\n') line_num++;
              if (previous_char == '*' && current_char == '/') break;
              
              else previous_char = current_char;
            } while(1);
         }
. { void lexical_error(); }

<<EOF>> { return FINISHED; }
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
	
	printf("ERRO LEXICO: %s - Linha: %d", yytext, line_num);
	exit(-1);
}
