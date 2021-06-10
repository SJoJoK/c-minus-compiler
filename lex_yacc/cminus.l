
%{
#include "y.tab.h"
#include "AST.h"
extern YYSTYPE yylval;
static int lineNO = 1;
%}

%option noyywrap

%%
[' '\t]+
"else"		{return ELSE;}
"if"		{return IF;}
"int"		{return INT;}
"return" 	{return RETURN;}
"void" 		{return VOID;}
"while" 	{return WHILE;}

[a-zA-Z]+	{
				NameInfo *tmp = (NameInfo *) malloc(sizeof(NameInfo));
				tmp->name = strdup(yytext);
				tmp->lineNO = lineNO;
				yylval.nameInfo = tmp;
				return ID;
				}

[0-9]+		{yylval.value=atoi(yytext);
		 		return NUM;
			}

"<="		{return LTE;}
">="		{return GTE;}
"=="		{return EQUAL;}
"!="		{return NOTEQUAL;}

"\+"		{return ADD;}
"\-"		{return SUB;}
"\*"		{return MUL;}
"\/"		{return DIV;}
"<"			{return LT;}
">"			{return GT;}
"="			{return yytext[0];}
";"			{return yytext[0];}
","			{return yytext[0];}
"\("		{return yytext[0];}
"\)"		{return yytext[0];}
"\["		{return yytext[0];}
"\]"		{return yytext[0];}
"\{"		{return yytext[0];}
"\}"		{return yytext[0];}
"\n"		{yylineno++;lineNO++;}


%%




