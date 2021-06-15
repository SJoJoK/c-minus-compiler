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

    //ID的类型，分别为其名字与行编号
    typedef struct NameInfo
    {
        char *name;
        int lineNO;
    } NameInfo;
    
    //结点的类型
    typedef enum
    {
        NK_GLOBALSCOPE,//根节点
        NK_DECLARATION,//声明
        NK_STATEMENT,//语句
        NK_EXPRESSION,//表达式
        NK_PARAMETER//参数
    } NodeKind;

    //声明结点的具体类型
    typedef enum
    {
        D_ARRAY,//数组
        D_VAR,//变量
        D_FUN,//函数

    } DeclarationKind;

    //参数结点的具体类型
    typedef enum
    {
        P_ARRAY,//数组
        P_VAR,//变量
        P_VOID//函数
    } ParameterKind;
    
    //语句结点...
    typedef enum
    {
        S_IF,
        S_WHILE,
        S_COMPOUND,//复合语句
        S_RETURN
    } StatementKind;

    // 表达式结点...
    typedef enum
    {
        E_ROP,//比较类运算符表达式
        E_AOP,//ALU运算符表达式
        E_CONST,//常量表达式
        E_ID,//名字表达式（下两者的公共父结点）
        E_VAR_ID,//变量名字表达式
        E_ARRAY_ID,//数组名字表达式
        E_CALL_FUN,//函数调用表达式
        E_ASSIGN//赋值表达式
    } ExpressionKind;

    typedef struct TreeNode
    {
        struct TreeNode *firstChild;
        struct TreeNode *nextBrother;
        int lineNO;
        int LabelSeed;//不同跳转语句需要的Label编号
        int reg;//表达式的值所在的寄存器编号
        NodeKind nodeKind;//结点种类
        union
        {
            DeclarationKind declaration;
            StatementKind statement;
            ExpressionKind expression;
            ParameterKind parameter;
        } specificKind;//具体种类

        union
        {
            int op;
            int value;
            char *name;
        } attribute;//结点属性
        int type;//类型，也就是int或void
        int arraySize;//数组长度，用于数组声明
        int hasReturn;//是否有return语句，用于函数定义
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
