/*
 *   UNIFESP SJC
 *
 *   COMPILADORES
 *   ARQUIVO utils.c
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */
 
#include "utils.h"

int tab_tree = 0;

void lexical_analysis(char *fileName, FILE *input_file) {
	
	printf("\n* * * * * FASE 01: ANALISE LEXICA | GERACAO DOS TOKENS E LEXEMAS * * * * *\n\n");
	
	FILE *read_file = fopen(fileName, "r");

	/* Buffer para leitura de arquivo */
	char lexems[LINE_LEN];
	
	/* Flags de controle para leitura dos tokens e lexemas */
	int newToken = 1;
	int firstToken = 0;
	int lineFinished = 0;
	
	while (!lineFinished) {
		
		if (fgets(lexems, LINE_LEN, read_file) == NULL) break;
		while (lexems[1] == '\n') {
			
			if (fgets(lexems, LINE_LEN, read_file) == NULL) break;
		}
		
		int current_line_num = line_num;
		if (line_num == 0) current_line_num++;
		
		printf("Linha %d: ", current_line_num);
		printf("%s", lexems);
		
		token_t token;
		char *token_name = get_token_name(token);
		
		if (firstToken) {
			
			printf("%s ", token_name);	
            firstToken = 0;
		}
		free(token_name);
		
		while (newToken) {
	
			token = get_token();
			token_name = get_token_name(token);
			
			if (token == 0 || line_num != current_line_num) {
				
				firstToken = 1;
				free(token_name);
				break;
			}

			printf("%s ", token_name);
            free(token_name);
		}
		printf("\n\n");
	}
	fclose(read_file);
}

void syntax_analysis(char *fileName, FILE *input_file) {
	
	FILE *read_file = fopen(fileName, "r");
	
	printf("\n* * * * * FASE 02: ANALISE SINTATICA | GERACAO DA ARVORE SINTATICA: * * * * *\n\n");
	
	syntax_tree = parse();
	print_syntax_tree(syntax_tree);
	
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
        case NEWLINE: printf("\n"); break;
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

		default: strcpy(token_name, "Invalid Token"); break;
    }
    return token_name;
}

char *string_copy(char *string) { 

    char *token_name = malloc(strlen(string) + 1);
    strcpy(token_name, string);
    
    return token_name;
}

void init_stack(Stack *stack) {
	
	stack = (Stack*)malloc(sizeof(Stack));
	stack->top = NULL;
}

void push_stack(Stack *stack, char *name) {
	
	Stack *stack_t = (Stack*)malloc(sizeof(Stack));
	
	stack_t->next = stack->top;
	stack_t->name = strdup(name);
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

	return name;
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

void print_syntax_tree(TreeNode *tree) { 
	
	int i, j;
	
	tab_tree += TAB_SIZE;

    while (tree != NULL) {
	
        for (i = 0; i < tab_tree; i++)
            printf(" ");

        if (tree->node_kind == exp_k) { 

            switch (tree->kind.exp) {
                case exp_id:
	
                    if (strcmp(tree->attr.name, "void") == 0) printf("void\n");
                    else printf("Id: %s\n", tree->attr.name);
                    break;

                case exp_num: printf("Const: %d\n", tree->attr.value); break;
                case exp_op: printf("Operator: %s\n", get_token_name(tree->attr.op)); break;
            }
        }
        else if (tree->node_kind == stmt_k) { 
            
			switch (tree->kind.stmt) {
	
                case stmt_if: printf("If\n"); break;
                case stmt_while: printf("While\n"); break;
                case stmt_atrib: printf("Assign\n"); break;
                case stmt_return: printf("Return\n"); break;
                case stmt_func: printf("Function Call: %s\n", tree->attr.name); break;
            }
        }
        else if (tree->node_kind == decl_k) {
            
			switch(tree->kind.decl) {
	
                case decl_kind:
	
                    if (tree->p_kind == Integer) printf("Primitive int\n");
                    else if(tree->p_kind == Array) printf("Primitive int[]\n");
                    else printf("Primitive void\n");
                    break;

                case decl_func: printf("Function: %s\n", tree->attr.name); break;
                case decl_var: printf("Variable: %s\n", tree->attr.name); break;         
            } 
        } 

        for (j = 0; j < CHILD_NODES; j++)
            print_syntax_tree(tree->child[j]);

        tree = tree->sibling;
    }
    tab_tree -= TAB_SIZE;
}



