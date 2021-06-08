
%{
#include "y.tab.h"
extern YYSTYPE yylval;
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

[a-zA-Z]+	{strcpy(yylval.s,yytext);
		 			return ID;
				}

[0-9]+		{yylval.n=atoi(yytext);
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
"\n"		{yylineno++;}


%%




