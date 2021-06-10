#!/bin/sh
cd lex_yacc
yacc -d cminus_new.y
lex cminus.l
mv lex.yy.c ../src
mv y.tab.c ../src
mv y.tab.h ../include