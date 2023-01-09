/*
 *   UNIFESP SJC
 *
 *   COMPILADORES
 *   ARQUIVO UTILS.h 
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */
 
#ifndef UTILS_H
#define UTILS_H
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_LEN 100
#define COMMENT_LEN 1024
#define LINE_LEN 100
#define CHILD_NODES 3
#define TAB_SIZE 4

#ifndef YYPARSER
#include "parse.tab.h"	
#endif

extern FILE* input_file;
extern char* yytext;
typedef int token_t;
int line_num;

char *get_token_name(token_t);
token_t get_token();
void lexical_error();

char *string_copy(char *string);

char token_id[TOKEN_LEN];
char token_num[TOKEN_LEN];
char token_str[TOKEN_LEN];

int lexical_err;
int syntax_err;

/* Fases de Analise */
void lexical_analysis(char *fileName, FILE *input);
void syntax_analysis(char *fileName, FILE *input);
//void semantic_analysis(char *fileName, FILE *input);

/* Declaracao estrutura de dados Pilha */
typedef struct stack {
	
	char *name;
	struct stack *next;
	struct stack *top;
	
} Stack;

/* Metodos para estrutura de dados Pilha */
void init_stack(Stack *stack);
void push_stack(Stack *stack, char *name);
char *pop_stack(Stack *stack);

/* Enumeracoes para tipos de tokens (declaration, expression, statement, tiposPrimitivos) */
typedef enum {decl_k, exp_k, stmt_k} nodeKind;
typedef enum {decl_func, decl_kind, decl_var} declKind;
typedef enum {stmt_atrib, stmt_func, stmt_if, stmt_return, stmt_while} stmtKind;
typedef enum {exp_id, exp_num, exp_op} expKind;
typedef enum {Array, Boolean, Integer, Void} primitiveKind;

/* Declaracao estrutura de dados Arvore */
typedef struct treeNode {
	
    struct treeNode *child[CHILD_NODES];
    struct treeNode *sibling;

    int line_num;
    
    nodeKind node_kind;

    union { 
    
        declKind decl; 
        expKind exp;
        stmtKind stmt; 
        
    } kind;
    
    union {
    	
        char *name;
        token_t op;
        int value;
        
    } attr;

    primitiveKind p_kind;
    
} TreeNode;

/* Metodos para estrutura de dados Arvore */
TreeNode *parse();
TreeNode *init_tree_node(nodeKind node);
TreeNode *create_decl_tree_node(declKind node);
TreeNode *create_stmt_tree_node(stmtKind node);
TreeNode *create_exp_tree_node(expKind node);
void print_syntax_tree(TreeNode *tree);

TreeNode* syntax_tree;



#endif /* UTILS_H */