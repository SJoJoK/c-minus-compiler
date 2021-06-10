#ifndef _SYNTEXTREE_
#define _SYNTEXTREE_

#include "y.tab.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NameInfo
    {
        char *name;
        int lineNO;
    } NameInfo;
    typedef enum
    {
        NK_GLOBALSCOPE,
        NK_DECLARATION,
        NK_STATEMENT,
        NK_EXPRESSION,
        NK_PARAMETER
    } NodeKind;

    typedef enum
    {
        D_ARRAY,
        D_VAR,
        D_FUN,

    } DeclarationKind;

    typedef enum
    {
        P_ARRAY,
        P_VAR,
        P_VOID
    } ParameterKind;

    typedef enum
    {
        S_IF,
        S_WHILE,
        S_COMPOUND,
        S_RETURN
    } StatementKind;

    typedef enum
    {
        E_ROP,
        E_AOP,
        E_CONST,
        E_ID,
        E_VAR_ID,
        E_ARRAY_ID,
        E_CALL_FUN,
        E_ASSIGN
    } ExpressionKind;

    typedef struct TreeNode
    {
        struct TreeNode *firstChild;
        struct TreeNode *nextBrother;
        int lineNO;
        int LabelSeed;
        int reg;
        NodeKind nodeKind;
        union
        {
            DeclarationKind declaration;
            StatementKind statement;
            ExpressionKind expression;
            ParameterKind parameter;
        } specificKind;

        union
        {
            int op;
            int value;
            char *name;
        } attribute;
        int type;
        int arraySize;

        struct TreeNode *symbolMap;

        int dataMemoryAddress;
        int isAbsoluteAddress;

        int scopeIndex;
    } TreeNode;

    TreeNode *createNode();
    TreeNode *createGlobalScopeNode();
    TreeNode *createDeclarationNode(DeclarationKind specificKind);
    TreeNode *createStatementNode(StatementKind specificKind);
    TreeNode *createExpressionNode(ExpressionKind specificKind);
    TreeNode *createParameterNode(ParameterKind specificKind);

    void freeTree(TreeNode *aTree);
    void freeBrothers(TreeNode *aNode);
    void addChildNode(TreeNode *currentNode, TreeNode *aChildNode);
    void addBrotherNode(TreeNode *currenNode, TreeNode *aNode);

    void printSyntaxTree(FILE *out, TreeNode *aTree, int numEmptySpace);
    void printTreeNode(FILE *out, TreeNode *aNode, int numEmptySpace);
    void printToken(FILE *out, int aToken);

#ifdef __cplusplus
}
#endif

#endif // !_SYNTEXTREE_
