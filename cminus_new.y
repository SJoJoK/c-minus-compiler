%{
#include "AST.h"  
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static struct TreeNode *aTree;
extern int lineNO;
extern int	yylex();
int yyerror (char *s){ 
    fprintf(stderr,"%s\n",s);
    return 0;
}	
extern FILE *yyin;
extern FILE *yyout;

%}

%union{
	char *name;
	int value;
	int tokenType;
	struct TreeNode *node;
}

%token IF ELSE INT RETURN VOID WHILE
%token ID 
%token NUM
%token LTE GTE LT GT ADD SUB MUL DIV EQUAL NOTEQUAL
%token ERROR

%type <node> program             declaration_list     declaration        var_declaration
		     fun_declaration     params param_list    param              compound_stmt
			 local_declarations  statement_list       statement          expression_stmt 
			 selection_stmt      iteration_stmt       return_stmt        expression 
			 simple_expression   additive_expression  var                term 
			 factor              call                 args               arg_list

%type <tokenType> relop addop mulop type_specifier
%start program
%%

program : declaration_list {
							aTree = createGlobalScopeNode();
							addChildNode(aTree, $1); 
		           		   }
        ;

declaration_list: declaration_list declaration	{
													if ($1 != NULL)
													{
														$$ = $1;
														addBrotherNode($1, $2);
													}
													else
													{
														$$ = $2;
													}
												}
                | declaration {$$ = $1;}
                ;

declaration: var_declaration {$$ = $1;}
           | fun_declaration {$$ = $1;}
           ;
var_declaration: type_specifier ID ';' 	{
											$$=createDeclarationNode(D_VAR);
									     	$$->type = $1;
										 	$$->attribute.name =strdup($2->name);
										 	$$->lineNO = $2->lineNO;
										}
               |  type_specifier ID '[' NUM ']' ';' 	{
															$$=createDeclarationNode(D_ARRAY);
															$$->type = $1;
															$$->attribute.name = strdup($2->name);
															$$->lineNO = $2->lineNO;														   
															$$->arraySize = $4;
														}
               ;

type_specifier: INT {$$ = 0; }
              | VOID {$$ = 1;}
              ;

fun_declaration: type_specifier ID '(' params ')' compound_stmt { 		
																		$$ = createDeclarationNode(D_FUN);
																	    $$->attribute.name = strdup($2->name);	 
																		$$->lineNO = $2->lineNO;
																		$$->type = $1;
																		addChildNode($$, $4);
																		addChildNode($$, $6);
																}
               													;

params: param_list {$$ = $1;}
      | VOID {
		  		$$ = createParameterNode(P_VOID);
	  		  	$$->type = 0;
			 }
      ;

param_list: param_list ',' param 	{ 	
										$$ = $1;
										addBrotherNode($1, $3);
									}
          | param {$$ = $1;}
          ;

param: type_specifier ID {
							$$=createParameterNode(P_VAR);
						  	$$->type = $1;
						  	$$->attribute.name = $2->name;
						  	$$->lineNO = $2->lineNO;
						 }
     | type_specifier ID '[' ']' { 			
		 							$$=createParameterNode(P_ARRAY);
						  			$$->type  = $1;
									$$->attribute.name = $2->name;
									$$->lineNO = $2->lineNO;
								 }
     ;

compound_stmt: '{' local_declarations statement_list '}' {		
															$$ = createStatementNode(S_COMPOUND);
															addChildNode($$, $2);
															addChildNode($$, $3);
														 }
             													;

local_declarations: local_declarations var_declaration {
															if ($1 != NULL)
															{
																$$ = $1;
																addBrotherNode($1, $2);
															}
															else
															{
															$$ = $2;
															}
														}
                  | /* empty */ {$$=NULL;}
                  ;

statement_list: statement_list statement {
											if ($1 != NULL)
											{
												$$ = $1;
												addBrotherNode($1, $2);
											}
											else
											{
											$$ = $2;
											}
										}
              |  /* empty */ {$$=NULL;}
              ;

statement: expression_stmt {$$=$1;}
         | compound_stmt {$$=$1;}
         | selection_stmt {$$=$1;}
         | iteration_stmt {$$=$1;}
         | return_stmt {$$=$1;}
         ;

expression_stmt: expression ';' {$$ = $1;}
               | ';' {$$ = NULL;}
               ;

selection_stmt: IF '(' expression ')' statement {		
													$$ = createStatementNode(S_IF);
													addChildNode($$, $3);
													addChildNode($$, $5); 
														
												}
              | IF '(' expression ')' statement ELSE statement {
				  													$$ = createStatementNode(S_IF);
			  														addChildNode($$, $3);
																	addChildNode($$, $5);
																	addChildNode($$, $7);
																}
              ;

iteration_stmt: WHILE '(' expression ')' statement {	$$ = createStatementNode(S_WHILE);
														addChildNode($$, $3);
														addChildNode($$, $5);
													}
              ;

return_stmt: RETURN ';' {$$ = createStatementNode(S_RETURN);}
           | RETURN expression ';' {
			   						$$ = createStatementNode(S_RETURN);
		   						    addChildNode($$, $2);
									}   
           ;

expression: var '=' expression {
									$$ = createExpressionNode(E_ASSIGN);
								   	addChildNode($$, $1);
								   	addChildNode($$, $3);
								}
          | simple_expression {$$ = $1;}
          ;

var: ID {
			$$=createExpressionNode(E_VAR_ID);
		 	$$->attribute.name = strdup($1->name);
	     	$$->lineNO = $1->lineNO;
		}
   | ID '[' expression ']' 	{
	   							$$=createExpressionNode(E_ARRAY_ID);
								$$->attribute.name = strdup($1->name);
								$$->lineNO = $1->lineNO;
								addChildNode($$, $3);
							}
   ;

simple_expression: additive_expression relop additive_expression {
																	$$=createExpressionNode(E_OP);
                                                                  	addChildNode($$, $1);
																  	addChildNode($$, $3);
																  	$$->attribute.op = $2;
																}
                 | additive_expression {$$ = $1;}
                 ;
relop: LTE {$$ = LTE;} 
     | LT {$$ = LT;}
     | GT {$$ = GT;}
     | GTE {$$ = GTE;}
     | EQUAL {$$ = EQUAL;}
     | NOTEQUAL {$$ = NOTEQUAL;}
     ;

additive_expression: additive_expression addop term {
														$$=createExpressionNode(E_OP);
													 	addChildNode($$, $1);
													 	addChildNode($$, $3);
													 	$$->attribute.op = $2;
													}
                   | term {$$ = $1;}
                   ;

addop: ADD {$$ = ADD;}
     | SUB {$$ = SUB;}
     ;
    
term: term mulop factor {
							$$=createExpressionNode(E_OP);
							addChildNode($$, $1);
						 	addChildNode($$, $3);
							$$->attribute.op = $2;
						}
    | factor {$$ = $1;}
    ;

mulop: MUL {$$ = MUL;}
     | DIV {$$ = DIV;}
     ;

factor: '(' expression ')' {$$ = $2;}
      | var { $$ = $1;}
      | call { $$ = $1;}
      | NUM { 
				$$ = createExpressionNode(E_CONST);
	  	      	$$->attribute.value = $1;
	  		}
      ;

call: ID '(' args ')' {			
							$$ = createExpressionNode(E_CALL_FUN);
							$$->attribute.name = strdup($1->name);
							$$->lineNO = $1->lineNO; 
							addChildNode($$, $3);
						}
    ;

args: arg_list {$$ = $1; };
    | {$$ = NULL;}
    ;

arg_list: arg_list ',' expression {   if ($1 != NULL)
										{
											$$ = $1;
											addBrotherNode($1, $3);
										}
										else
										{
											$$ = $3;
										}
								}	
        | expression {$$ = $1;}
        ;

%%



TreeNode *parse(FILE *fileIn)
{
	if (fileIn != NULL){
		yyin = fileIn;
	}
	
  	yyparse();

  	return aTree;
}


