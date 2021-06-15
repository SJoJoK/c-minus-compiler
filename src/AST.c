#include "AST.h"

TreeNode *createNode()
{
    TreeNode *aNode = (TreeNode *)malloc(sizeof(TreeNode));
    aNode->firstChild = NULL;
    aNode->nextBrother = NULL;
    aNode->type = -1;
    aNode->hasReturn = 0;
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
    aNode->specificKind.parameter = specificKind;
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

void printTreeNode(FILE *out, TreeNode *aNode, int numEmptySpace)
{
    for (int i = 0; i < numEmptySpace; i++)
    {
        fprintf(out, " ");
    }
    switch (aNode->nodeKind)
    {
    case NK_GLOBALSCOPE:
        fprintf(out, "Global Scope!\n");
        break;
    case NK_DECLARATION:
        switch (aNode->specificKind.declaration)
        {
        case D_FUN:
            fprintf(out, "Line %d: Function Declare: %s\n", aNode->lineNO, aNode->attribute.name);
            break;

        case D_VAR:
            fprintf(out, "Line %d: Variable Declare: %s\n", aNode->lineNO, aNode->attribute.name);
            break;
        case D_ARRAY:
            fprintf(out, "Line %d: Array Declare : %s [%d]\n", aNode->lineNO, aNode->attribute.name, aNode->arraySize);
            break;

        default:
            break;
        }

        break;
    case NK_STATEMENT:
        switch (aNode->specificKind.statement)
        {
        case S_IF:
            fprintf(out, "If\n");

            break;

        case S_WHILE:
            fprintf(out, "While\n");
            break;

        case S_COMPOUND:
            fprintf(out, "Compound Statment\n");
            break;

        case S_RETURN:
            fprintf(out, "Return\n");
            break;

        default:
            break;
        }

        break;
    case NK_EXPRESSION:
        switch (aNode->specificKind.expression)
        {
        case E_AOP:
            fprintf(out, "Operator:");
            printToken(out, aNode->attribute.op);
            fprintf(out, "\n");
            break;
        case E_ROP:
            fprintf(out, "Operator:");
            printToken(out, aNode->attribute.op);
            fprintf(out, "\n");
            break;
        case E_CONST:
            fprintf(out, "Const: %d\n", aNode->attribute.value);
            break;
        case E_ID:
            fprintf(out, "Var in a expression:\n");
            break;
        case E_VAR_ID:
            fprintf(out, "Line %d: Var: %s\n", aNode->lineNO, aNode->attribute.name);
            break;
        case E_ARRAY_ID:
            fprintf(out, "Line %d: Array: %s\n", aNode->lineNO, aNode->attribute.name);
            break;
        case E_CALL_FUN:
            fprintf(out, "Line %d: Call Function: %s\n", aNode->lineNO, aNode->attribute.name);
            break;
        case E_ASSIGN:
            fprintf(out, "Assign:\n");
            break;
        default:
            break;
        }

        break;
    case NK_PARAMETER:
        switch (aNode->specificKind.parameter)
        {
        case P_ARRAY:
            fprintf(out, "Array parameter Declare: %s\n", aNode->attribute.name);
            break;

        case P_VAR:
            fprintf(out, "Variable parameter Declare: %s\n", aNode->attribute.name);
            break;

        case P_VOID:
            fprintf(out, "Void parameter Declare: \n");
            break;
        default:
            break;
        }

    default:
        break;
    }
}

void printToken(FILE *out, int aToken)
{

    switch (aToken)
    {
    case SUB:
        fprintf(out, "-");
        break;

    case ADD:
        fprintf(out, "+");
        break;

    case MUL:
        fprintf(out, "*");
        break;

    case DIV:
        fprintf(out, "/");
        break;

    case LT:
        fprintf(out, "<");
        break;

    case LTE:
        fprintf(out, "<=");
        break;

    case GT:
        fprintf(out, ">");
        break;

    case GTE:
        fprintf(out, ">=");
        break;

    case EQUAL:
        fprintf(out, "==");
        break;

    case NOTEQUAL:
        fprintf(out, "!=");
        break;

    case '=':
        fprintf(out, "=");
        break;

    default:
        break;
    }
}
