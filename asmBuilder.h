#ifndef _ASMBUILDER_
#define _ASMBUILDER_
#include "y.tab.h"
#include "AST.h"
#include "symTable.h"
#include "emitcode.h"
extern symbolAttributes parsedSymbolAttributes;
extern symbolTable globalSymTab;
extern symbolTable *CurrentScope;
extern int LabelSeed;
extern int NumOfParams;
extern int ArgList[3];
extern int ArgNum;
class asmBuilder
{
public:
    FILE *fp;
    TreeNode *tree;
    asmBuilder(TreeNode *tree, FILE *fp)
    {
        this->tree = tree;
        this->fp = fp;
    }
    void asmBuild();
    void generateAsm(TreeNode *node);
};
#endif