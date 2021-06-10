#ifndef _ASMBUILDER_
#define _ASMBUILDER_
#include "y.tab.h"
#include "AST.h"
#include "symTable.h"
#include "emitcode.h"
class asmBuilder
{
public:
    TreeNode *tree;
    asmBuilder(TreeNode *tree)
    {
        this->tree = tree;
    }
    void asmBuild();
    void generateAsm(TreeNode *node);
};
#endif