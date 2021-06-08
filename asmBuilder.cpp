#include"AST.h"
#include"symTable.h"
#include"emitcode.h"
extern symbolAttributes parsedSymbolAttributes;
extern symbolTable globalSymTab;
extern symbolTable *CurrentScope;
extern int LabelSeed;
extern int NumOfParams;
extern int ArgList[3];
extern int ArgNum;
int TextSection = 0;

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
    void asmBuild(){};
    void generateGlobalScope();
    void generateCallMain();
    void generateProgramEnd();
    void generateIOFunctions();
};
void asmBuilder::asmBuild()
{
    globalSymTab.finalizeScope();
    fprintf(fp, "SECTION .data\n                                                \n");
    fprintf(fp, "ReturnMsg: db \"Return Value:%%i\",10,0\n");
    generateGlobalScope();
    generateCallMain();
    generateProgramEnd();
    generateIOFunctions();
}
void asmBuilder::generateGlobalScope()
{

    TreeNode *aNode = tree->firstChild;
    while (aNode != nullptr)
    {
        if (aNode->nodeKind == NK_DECLARATION)
        {
            switch (aNode->specificKind.declaration)
            {
            case D_VAR:
                dMemToAllcoate++;
                aNode->isAbsoluteAddress = true;
                aNode->dataMemoryAddress = dMemAddress;
                dMemAddress--;
                numVariables++;
                break;
            case D_ARRAY:
                dMemToAllcoate += aNode->arraySize;
                aNode->isAbsoluteAddress = true;
                aNode->dataMemoryAddress = dMemAddress;
                dMemAddress -= aNode->arraySize;
                numVariables++;
                break;
            default:
                break;
            }
        }

        aNode = aNode->nextBrother;
    }
}