%{
	#define YYPARSER 
	#include "utils.h"
  	#define YYSTYPE TreeNode*

	char *attr_name, *var_name, *func_name;	
 	int cur_line_number, func_cur_line_number;
 	int firstFunc = 1;
  	
	Stack func_stack;
   	TreeNode* treeToReturn;
	
	static int yylex();
	int yyerror(char *error);
%}

%token IF ELSE WHILE RETURN INT VOID
%token ID NUM
%token ASSIGN EQUAL DIF LT GT LTE GTE PLUS MINUS TIMES SLASH
%token OPARENT CPARENT OBRACKET CBRACKET OKEY CKEY SEMICOLON COMMA COMENT
%token NEWLINE WHITESPACE
%token ERROR END

%%
program : list_decl { treeToReturn = $1; };

term : term mult factor {
	
            $$ = create_exp_tree_node(exp_op);

            $$->child[0] = $1;
            $$->child[1] = $3;
            $$->attr.op = $2->attr.op; 
          } 
		  | factor { $$ = $1; };

mult : TIMES { 

          $$ = create_exp_tree_node(exp_id); 
          $$->attr.op = TIMES;
        }
        | SLASH {
        	
          $$ = create_exp_tree_node(exp_id); 
          $$->attr.op = SLASH;
        };

factor : OPARENT exp CPARENT { $$ = $1; }
        | var { $$ = $1; }
        | activate { $$ = $1; }
        | NUM { 
        
          $$ = create_exp_tree_node(exp_num);

          $$->attr.value = atoi(token_num);
          $$->p_kind = Integer;
        };

sum : PLUS {
 
          $$ = create_exp_tree_node(exp_id); 
          $$->attr.op = PLUS; 
        }
        | MINUS {
        	
          $$ = create_exp_tree_node(exp_id); 
          $$->attr.op = MINUS;
        };

exp : var ASSIGN exp { 

              $$ = create_stmt_tree_node(stmt_atrib);

              $$->child[0] = $1;
              $$->child[1] = $3;
              $$->p_kind = Integer;
              $$->attr.op = ASSIGN; 
            }
            | exp_simple { $$ = $1; };

exp_decl : exp SEMICOLON { $$ = $1; } | SEMICOLON { $$ = NULL; };

exp_simple : exp_sum operator exp_sum { 

                  $$ = create_exp_tree_node(exp_op);
                  
                  $$->child[0] = $1;
                  $$->child[1] = $3;
                  $$->attr.op = $2->attr.op; 
                } 
				| exp_sum { $$ = $1; };

exp_sum : exp_sum sum term { 

              $$ = create_exp_tree_node(exp_op);
              
              $$->child[0] = $1;
              $$->child[1] = $3;
              $$->attr.op = $2->attr.op; 
            } 
			| term { $$ = $1; };

exp_kind : INT { 

              $$ = create_decl_tree_node(decl_kind); 
              $$->p_kind = Integer; 
            } 
			| VOID { 
			
              $$ = create_decl_tree_node(decl_kind); 
              $$->p_kind = Void; 
            };

decl : var_decl { $$ = $1; } | func_decl { $$ = $1; };

var_decl : exp_kind ID { 

                  attr_name = string_copy(token_id);
                  cur_line_number = line_num;
                }
              	SEMICOLON {
              		
                  $$ = $1;
                  YYSTYPE tree_node = create_decl_tree_node(decl_var);

                  tree_node->attr.name = attr_name;
                  tree_node->line_num = cur_line_number;
                  tree_node->p_kind = $1->p_kind;
                  
                  $$->child[0] = tree_node;
                }
            	| exp_kind ID { 
            	
                  attr_name = string_copy(token_id);
                  cur_line_number = line_num;
                }
            	OBRACKET NUM CBRACKET SEMICOLON { 
            	
                  $$ = $1;
                  
                  YYSTYPE exp_node = create_exp_tree_node(exp_num);
                  exp_node->attr.value = atoi(token_num);
                  exp_node->p_kind = Integer;
                  
                  YYSTYPE tree_node = create_decl_tree_node(decl_var);
                  tree_node->attr.name = attr_name;
                  tree_node->line_num = cur_line_number;
                  tree_node->child[0] = exp_node;

                  if ($1->p_kind == Integer) tree_node->p_kind = Array;
                  else tree_node->p_kind = Void;
                  
                  $$->child[0] = tree_node; 
                };

func_decl : exp_kind ID  {
	
                func_name = string_copy(token_id);
                func_cur_line_number = line_num;
              }
              OPARENT params CPARENT bloc_decl {
                
				$$ = $1;

                YYSTYPE func_node = create_decl_tree_node(decl_func);
                
                func_node->child[0] = $5;
                func_node->child[1] = $7;
                func_node->attr.name = func_name;
                func_node->line_num = func_cur_line_number;
                func_node->p_kind = $1->p_kind;
                
                $$->child[0] = func_node;
              };

arg : exp_kind ID  { 

            $$ = $1;

            attr_name = string_copy(token_id);
            cur_line_number = line_num;
            
            YYSTYPE decl_node = create_decl_tree_node(decl_var); 
            
            decl_node->attr.name = attr_name;
            decl_node->line_num = cur_line_number;
            decl_node->p_kind = $1->p_kind;
            
            $$->child[0] = decl_node;
          } | exp_kind ID {
          	
            attr_name = string_copy(token_id);
            cur_line_number = line_num;
          }
    	  OBRACKET CBRACKET {    
    	  
            $$ = $1;

            YYSTYPE decl_node = create_decl_tree_node(decl_var);
            
            decl_node->attr.name = attr_name;
            decl_node->line_num = cur_line_number;
            
            if ($1->p_kind == Integer) decl_node->p_kind = Array;
            else decl_node->p_kind = $1->p_kind;

            $$->child[0] = decl_node;
          };

params : list_params { $$ = $1; } 
		| VOID { 
			
			$$ = create_exp_tree_node(exp_id); 
			$$->attr.name = "void"; 
			$$->p_kind = Void; 
		};

stmt : exp_decl  { $$ = $1; }
     | bloc_decl { $$ = $1; }
     | cond_decl  { $$ = $1; }
     | loop_decl { $$ = $1; }
     | return_decl  { $$ = $1; };

bloc_decl : OKEY local_decl list_stmt CKEY { 

            YYSTYPE tmp = $2;
                                                    
            if (tmp != NULL) {
            	
                while (tmp->sibling != NULL) tmp = tmp->sibling;
                  
                tmp->sibling = $3;
                $$ = $2;
            }
            else $$ = $3;
        };

local_decl : local_decl var_decl {
 
                  YYSTYPE tmp = $1;
                                    
                  if (tmp != NULL) {
                  	
                    while (tmp->sibling != NULL) tmp = tmp->sibling;

                    tmp->sibling = $2;
                    $$ = $1;
                  }
                  else $$ = $2;
                } 
				| { $$ = NULL; };
                        
cond_decl : IF OPARENT exp CPARENT stmt { 

                $$ = create_stmt_tree_node(stmt_if);
              
                $$->child[0] = $3;
                $$->child[1] = $5;
              }
              | IF OPARENT exp CPARENT stmt ELSE stmt{ 
              
                $$ = create_stmt_tree_node(stmt_if);
                
                $$->child[0] = $3;
                $$->child[1] = $5;
                $$->child[2] = $7;
              };

loop_decl : WHILE OPARENT exp CPARENT stmt { 

                $$ = create_stmt_tree_node(stmt_while);

                $$->child[0] = $3;
                $$->child[1] = $5;
            };

return_decl : RETURN SEMICOLON { 

                $$ = create_stmt_tree_node(stmt_return);
              }    
              | RETURN exp SEMICOLON {
              	
                $$ = create_stmt_tree_node(stmt_return);
                
                $$->child[0] = $2;
              };

var : ID { 

        attr_name = string_copy(token_id);
        cur_line_number = line_num;

        $$ = create_exp_tree_node(exp_id);
        
        $$->attr.name = attr_name;
        $$->line_num = cur_line_number;
        $$->p_kind = Void;
      }
      | ID { 
      
        var_name = string_copy(token_id);
        cur_line_number = line_num;
      } 
      OBRACKET exp CBRACKET {
      	
        $$ = create_exp_tree_node(exp_id);

        $$->attr.name = var_name;
        $$->line_num = cur_line_number;
        $$->child[0] = $4;
        $$->p_kind = Integer; 
      };

operator : LTE { 

              $$ = create_exp_tree_node(exp_id); 
              $$->attr.op = LTE; 
            }
            | LT { 
              $$ = create_exp_tree_node(exp_id); 
              $$->attr.op = LT; 
            }
            | GT { 
            
              $$ = create_exp_tree_node(exp_id); 
              $$->attr.op = GT; 
            }
            | GTE { 
            
              $$ = create_exp_tree_node(exp_id); 
              $$->attr.op = GTE; 
            }
            | EQUAL { 
            
              $$ = create_exp_tree_node(exp_id); 
              $$->attr.op = EQUAL; 
            }
            | DIF { 
            
              $$ = create_exp_tree_node(exp_id); 
              $$->attr.op = DIF; 
            };

activate : ID { 
              
			  if (firstFunc) {
			  	
                init_stack(&func_stack);
                firstFunc = 0;
              }

              push_stack(&func_stack, string_copy(token_id));
              cur_line_number = line_num;
            }
            OPARENT arguments CPARENT { 
            
              $$ = create_stmt_tree_node(stmt_func);

              $$->child[1] = $4; 
              $$->attr.name = pop_stack(&func_stack);
              $$->line_num = cur_line_number;
            };

arguments : list_arg { $$ = $1; } | { $$ = NULL; };

list_decl : list_decl decl { 

                  YYSTYPE tmp = $1;
                  
                  if (tmp != NULL)  {
                    
					while (tmp->child[0]->sibling != NULL) tmp = tmp->child[0]->sibling;
					
                    tmp->child[0]->sibling = $2;
                    $$ = $1;
                  }
                  else $$ = $2;
                }   
              	| decl { $$ = $1; };

list_arg : list_arg COMMA exp { 

                YYSTYPE tmp = $1;
                                    
                if (tmp != NULL) {
                	
                    while (tmp->sibling != NULL) tmp = tmp->sibling;

                    tmp->sibling = $3;
                    $$ = $1;
                }
                else $$ = $3;
              } 
			  | arg { $$ = $1; } 
			  | exp { $$ = $1; };

list_params : list_params COMMA arg { 
                
				YYSTYPE tmp = $1;

                if (tmp != NULL) {
                	
                  while (tmp->sibling != NULL) tmp = tmp->sibling;

                  tmp->sibling = $3;
                  $$ = $1;
                } 
                else $$ = $3;
              } 
			  | arg { $$ = $1; };

list_stmt : list_stmt stmt { 
                  
				  YYSTYPE tmp = $1;
                                    
                  if (tmp != NULL) {
                    
					while (tmp->sibling != NULL) tmp = tmp->sibling;

                    tmp->sibling = $2;
                    $$ = $1;
                  }
                  else $$ = $2;
                } 
				| { $$ = NULL; };
%%

static int yylex(void) { 

	return get_token(); 
}

TreeNode *parse(void) { 

	yyparse(); 
	return treeToReturn; 
}

int yyerror(char *error_msg) {
	
    char* token_name = get_token_name(yychar);

    if (strcmp(token_name, "ID") == 0 || strcmp(token_name, "NUM") == 0) lexical_error();
    else printf("\n\n(!) ERRO SINTATICO | Linha: %d | Token: %s \n", line_num, token_name);

	syntax_err = 1; 
    free(token_name); 
}
