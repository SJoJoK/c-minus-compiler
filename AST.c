#include "AST.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TreeNode *createNode()
{
    TreeNode *aNode = (TreeNode *)malloc(sizeof(TreeNode));
    aNode->firstChild = NULL;
    aNode->nextBrother = NULL;
    aNode->type = -1;
    aNode->dataMemoryAddress = -1;
    return aNode;
}

TreeNode *createGlobalScopeNode()
{
    TreeNode *aNode = createNode();
    aNode->nodeKind = NK_GLOBALSCOPE;
    return aNode;
}

TreeNode *createDeclarationNode(DeclarationKind specificKind)
{
    TreeNode *aNode = createNode();
    aNode->nodeKind = NK_DECLARATION;
    aNode->specificKind.declaration = specificKind;
    return aNode;
}

TreeNode *createStatementNode(StatementKind specificKind)
{
    TreeNode *aNode = createNode();
    aNode->nodeKind = NK_STATEMENT;
    aNode->specificKind.statement = specificKind;
    return aNode;
}

TreeNode *createExpressionNode(ExpressionKind specificKind)
{
    TreeNode *aNode = createNode();
    aNode->nodeKind = NK_EXPRESSION;
    aNode->specificKind.expression = specificKind;
    return aNode;
}

TreeNode *createParameterNode(ParameterKind specificKind)
{
    TreeNode *aNode = createNode();
    aNode->nodeKind = NK_PARAMETER;
    aNode->specificKind.expression = specificKind;
    return aNode;
}

void freeTree(TreeNode *aTree)
{
    if (aTree->firstChild == NULL)
    {
        free(aTree);
    }
    else
    {
        freeTree(aTree->firstChild);
    }
}

void freeBrothers(TreeNode *aNode)
{
    if (aNode->nextBrother == NULL)
    {
        free(aNode);
    }
    else
    {
        freeBrothers(aNode);
    }
}

void addChildNode(TreeNode *currentNode, TreeNode *aChildNode)
{
    if (currentNode->firstChild == NULL)
    {
        currentNode->firstChild = aChildNode;
    }
    else
    {
        addBrotherNode(currentNode->firstChild, aChildNode);
    }
}

void addBrotherNode(TreeNode *currenNode, TreeNode *aNode)
{
    if (currenNode->nextBrother == NULL)
    {
        currenNode->nextBrother = aNode;
    }
    else
    {
        addBrotherNode(currenNode->nextBrother, aNode);
    }
}

void printSyntaxTree(FILE *out, TreeNode *aTree, int numEmptySpace)
{
    if (aTree == NULL)
    {
        return;
    }

    printTreeNode(out, aTree, numEmptySpace);
    printSyntaxTree(out, aTree->firstChild, numEmptySpace + 4);
    printSyntaxTree(out, aTree->nextBrother, numEmptySpace);
}
