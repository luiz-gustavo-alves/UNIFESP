/*
 *   UNIFESP SJC
 *
 *   COMPILADORES
 *   ARQUIVO utils.c
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */
 
#include "utils.h"

void lexical_analysis(char *fileName, FILE *input_file) {
	
	printf("FASE 01: ANALISE LEXICA | GERACAO DOS TOKENS E LEXEMAS: \n");
	
	FILE *read_file = fopen(fileName, "r");
	
	token_t token;
	char *token_name;
	
	/* Buffers para leitura de arquivo */
	char current_line[LINE_LEN];
	char text_line[LINE_LEN];
	char temp_text_line[LINE_LEN];
	
	/* Flag de controle para leitura do arquivo */
	int lineFinished = 0;
	
	while (!lineFinished) {
		
		if (fgets(current_line, LINE_LEN, read_file) == NULL) break;
		
		if (current_line[0] == '\n') {
			
			if(fgets(current_line, LINE_LEN, read_file) == NULL) break;
		}
		
		int current_line_number = line_num;
		
		if (line_num == 0) current_line_number++;
		
		sprintf(text_line, "\n%d: ", current_line_number);
        sprintf(temp_text_line, "%s", current_line);
        strcat(text_line, temp_text_line);
        printf("%s", text_line);
        memset(&text_line, 0, LINE_LEN);
		
		int newToken = 1;
		while (newToken) {
			
			token = get_token();
			token_name = get_token_name(token);
			
			if (token == FINISHED) {
				free(token_name);
				break;
			}
			
			if (line_num > current_line_number) {
				free(token_name);
				break;
			}
			
			sprintf(text_line, "%s ", token_name);
            printf("%s", text_line);
            memset(&text_line, 0, LINE_LEN);
            free(token_name);		
		}
		printf("\n");			
	}
	fclose(read_file);
}

void syntax_analysis(char *fileName, FILE *input_file) {
	
	FILE *read_file = fopen(fileName, "r");
	
	printf("FASE 02: ANALISE SINTATICA | GERACAO DA ARVORE SINTATICA: \n");
	
	syntax_tree = parse();
	//print_syntax_tree(syntax_tree);
	
	fclose(read_file);
}

char *get_token_name(token_t token) {
	
	char *token_name = (char*) malloc(sizeof(char) * TOKEN_LEN);

    switch(token) 
    {
        case ASSIGN: strcpy(token_name, "ASSIGN"); break;
        case CBRACKET: strcpy(token_name, "CBRACKET"); break;
        case CKEY: strcpy(token_name, "CKEY"); break;
        case COMENT: strcpy(token_name, "COMENT"); break;
        case COMMA: strcpy(token_name, "COMMA"); break;
        case CPARENT: strcpy(token_name, "CPARENT"); break;
        case DIF: strcpy(token_name, "DIF"); break;
        case ELSE:  strcpy(token_name, "ELSE"); break;
        case EQUAL: strcpy(token_name, "EQUAL"); break;
        case GT: strcpy(token_name, "GT"); break;
        case GTE: strcpy(token_name, "GTE"); break;
        case ID: strcpy(token_name, "ID"); break;
        case IF: strcpy(token_name, "IF"); break;
        case INT: strcpy(token_name, "INT"); break;
        case LT: strcpy(token_name, "LT"); break;
        case LTE: strcpy(token_name, "LTE"); break;
        case MINUS: strcpy(token_name, "MINUS"); break;
        case NEWLINE: strcpy(token_name, "NEWLINE"); break;
        case NUM: strcpy(token_name, "NUM"); break;
        case OBRACKET: strcpy(token_name, "OBRACKET"); break;
        case OKEY: strcpy(token_name, "OKEY"); break;
        case OPARENT: strcpy(token_name, "OPARENT"); break;
        case PLUS: strcpy(token_name, "PLUS"); break;
        case RETURN: strcpy(token_name, "RETURN"); break;
        case SEMICOLON: strcpy(token_name, "SEMICOLON"); break;
        case SLASH: strcpy(token_name, "SLASH"); break;
        case TIMES: strcpy(token_name, "TIMES"); break;
        case VOID: strcpy(token_name, "VOID"); break;
        case WHILE: strcpy(token_name, "WHILE"); break;
        case WHITESPACE: strcpy(token_name, "WHITESPACE"); break;
    }
    return token_name;
}

void init_stack(Stack *stack) {
	
	stack = (Stack*)malloc(sizeof(Stack));
	
	stack->top = NULL;
}

void push_stack(Stack *stack, char *name) {
	
	Stack *stack_t = (Stack*)malloc(sizeof(Stack));
	
	stack_t->next = stack->top;
	stack_t->name = name;
	stack->top = stack_t;
}

char *pop_stack(Stack *stack) {
	
	if (stack == NULL) return NULL;
	
	Stack *stack_old_top;
    char *name = NULL;
    
    name = strdup(stack->top->name);

    stack_old_top = stack->top;
    stack->top = stack_old_top->next;

    free(stack_old_top);
}

TreeNode *init_tree_node(nodeKind node) {
	
	TreeNode *newNode = (TreeNode*) malloc(sizeof(TreeNode));
	
	int i;
    for (i = 0; i < CHILD_NODES; i++)
        newNode->child[i] = NULL;

    newNode->sibling = NULL;
    newNode->line_num = line_num;
    newNode->node_kind = node;
    
	return newNode;
}

TreeNode *create_decl_tree_node(declKind kind) { 

    TreeNode *newNode = init_tree_node(decl_k);
    newNode->kind.decl = kind;

    return newNode;
}

TreeNode *create_stmt_tree_node(stmtKind kind) { 
    
	TreeNode *newNode = init_tree_node(stmt_k);
    newNode->kind.decl = kind;

    return newNode;
}

TreeNode *create_exp_tree_node(expKind kind) { 
    
	TreeNode *newNode = init_tree_node(exp_k);
    newNode->kind.decl = kind;

    return newNode;
}




