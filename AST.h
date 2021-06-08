#pragma once
#include <stdio.h>

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
    E_OP,
    E_CONST,
    E_VAR_ID,
    E_ARRAY_ID,
    E_CALL_FUN,
    E_ASSIGN
} ExpressionKind;

class Node
{
public:
    Node *firstChild;
    Node *nextBrother;
    NodeKind nodeKind;
    union
    {
        int op;
        int value;
        char *name;
    } attribute;
    int type;
    int arraySize;
};
class DeclarationNode : public Node
{

};
class StatementNode : public Node
{
};
class ExpressionNode : public Node
{
};
class ParameterNode : public Node
{
};
