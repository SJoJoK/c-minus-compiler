#include"symTable.h"
extern symbolAttributes parsedSymbolAttributes;
extern symbolTable globalSymTab;
extern symbolTable *CurrentScope;
extern int LabelSeed;
extern int NumOfParams;
extern int ArgList[3];
extern int ArgNum;
extern int ScopeLevel;
extern FILE *fp;