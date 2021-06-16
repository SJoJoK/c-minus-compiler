#ifndef EMITCODE_H
#define EMITCODE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symTable.h"

void emitInit();

void emitAluOp(int op, int reg1, int reg2);
enum {PLUS, MINUS, MULT, DIVI} ALU_OPS;

void emitRelOp(int op, int reg1, int reg2);
enum {EQU, NEQU, LESS, GTR, LTEQU, GTEQU} RELATION_OPS;

void emitMemOp(int op, char *id, int reg);
enum {LOAD, STORE} MEMORY_OPS;

void emitLoadConst(int reg, int value);

void emitDeclaration(int type, char *id);
enum {VAR, FUNC} DECLARATION_TYPE;

void emitCall(char *id, int argList[]);

void emitOutput(int reg);

void emitInput();

void emitEpilogue();

const char *regToString(int reg);
enum {EAX, EBX, ECX, EDX, ESI, EDI} REGISTER_NAME;

int nextFreeRegister();
void releaseOneRegister();
void releaseAllRegister();

#endif