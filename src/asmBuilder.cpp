#include"asmBuilder.h"
#include"global.h"
#include"ctype.h"
extern int LabelSeed = 0;
extern int NumOfParams = 0;
extern int ArgList[3] = {0, 0, 0};
extern int ArgNum = 0;
extern int ScopeLevel = 0;
int TextSection = 0;
void asmBuilder::asmBuild()
{
    fprintf(fp, "SECTION .data\n                                                \n");
    fprintf(fp, "ReturnMsg: db \"Return Value:%%i\",10,0\n");
    TreeNode *node = tree;
    generateAsm(node);
};
void asmBuilder::generateAsm(TreeNode *node)
{
    if (node == nullptr)
        return;
    switch (node->nodeKind)
    {
    case NK_GLOBALSCOPE:
    {
        TreeNode *tmp = node->firstChild;
        while(tmp)
        {
            generateAsm(tmp);
            tmp = tmp->nextBrother;
        }
        symbolTable:: finalizeScope();
    }
        break;
    case NK_DECLARATION:
    {
        if (node->specificKind.declaration == D_VAR)
        {
            parsedSymbolAttributes.type = node->type;
            symbolTable::insertSym(node->attribute.name, parsedSymbolAttributes, VAR);
            parsedSymbolAttributes.reset();
        }
        else if (node->specificKind.declaration == D_ARRAY)
        {
            parsedSymbolAttributes.type = node->type;
            parsedSymbolAttributes.array = 1;
            parsedSymbolAttributes.arrSize = node->arraySize;
            symbolTable::insertSym(node->attribute.name, parsedSymbolAttributes, VAR);
            parsedSymbolAttributes.reset();
        }
        else if (node->specificKind.declaration == D_FUN)
        {
            if (!TextSection++)
                fprintf(fp, "\nSECTION .text\nextern printf\n");
            emitDeclaration(FUNC, node->attribute.name);
            symbolTable::initializeScope();
            //Params
            TreeNode *param = node->firstChild;
            if(param->specificKind.parameter!=P_VOID)
            {
                while (param && param->nodeKind == NK_PARAMETER)
                {
                    generateAsm(param);
                    param = param->nextBrother;
                }
            }
            else
            {
                param = param->nextBrother;
            }
            parsedSymbolAttributes.type = node->type;
            parsedSymbolAttributes.parameters = NumOfParams;
            symbolTable::insertGlobalSym(node->attribute.name, parsedSymbolAttributes, FUNC);
            parsedSymbolAttributes.reset();
            NumOfParams = 0;
            //Compound_stmts
            TreeNode *stmts = param;
            generateAsm(stmts);
            symbolTable::finalizeScope();
            if (node->type == VOID)
                emitEpilogue();
            releaseAllRegister();
        }
    }
    break;
    case NK_PARAMETER:
    {
        if (node->specificKind.parameter == P_VOID)
        {
            break;
        }
        else if (node->specificKind.parameter == P_VAR)
        {
            parsedSymbolAttributes.type = node->type;
            parsedSymbolAttributes.parameters = NumOfParams + 1;
            parsedSymbolAttributes.initialized = 1;
            symbolTable::insertSym(node->attribute.name, parsedSymbolAttributes, VAR);
            parsedSymbolAttributes.reset();
            NumOfParams++;
        }
        else if (node->specificKind.parameter == P_ARRAY)
        {
            parsedSymbolAttributes.type = node->type;
            parsedSymbolAttributes.parameters = NumOfParams + 1;
            parsedSymbolAttributes.array = 1;
            parsedSymbolAttributes.initialized = 1;
            symbolTable::insertSym(node->attribute.name, parsedSymbolAttributes, VAR);
            parsedSymbolAttributes.reset();
            NumOfParams++;
        }
    }
    break;
    case NK_STATEMENT:
    {
        if (node->specificKind.statement == S_COMPOUND)
        {
            if (!inFunctionBody)
                symbolTable::initializeScope();
            //Local declaration
            TreeNode *local = node->firstChild;
            while (local && local->nodeKind == NK_DECLARATION)
            {
                generateAsm(local);
                emitDeclaration(VAR, local->attribute.name);
                local = local->nextBrother;
            }
            //Stmts
            TreeNode *stmt = local;
            while (stmt && (stmt->nodeKind == NK_STATEMENT || stmt->nodeKind == NK_EXPRESSION))
            {
                generateAsm(stmt);
                stmt = stmt->nextBrother;
            }
            if (!inFunctionBody())
                symbolTable::finalizeScope();
        }
        else if (node->specificKind.statement == S_IF)
        {
            int numOfChilds = 0;
            TreeNode *tmp = node->firstChild;
            while (tmp)
            {
                tmp = tmp->nextBrother;
                numOfChilds++;
            }
            if (numOfChilds == 2)
            {
                //Expression
                tmp = node->firstChild;
                generateAsm(tmp);
                node->LabelSeed = LabelSeed;
                LabelSeed++;
                fprintf(fp, "cmp %s, 1\n", regToString(tmp->reg));
                fprintf(fp, "jne EndIf%i\n", node->LabelSeed);
                releaseOneRegister();
                //Stmts
                tmp = tmp->nextBrother;
                generateAsm(tmp);
                fprintf(fp, "EndIf%i:\n", node->LabelSeed);
            }
            else if (numOfChilds == 3)
            {
                //Expression
                tmp = node->firstChild;
                generateAsm(tmp);
                node->LabelSeed = LabelSeed;
                LabelSeed++;
                fprintf(fp, "cmp %s, 1\n", regToString(tmp->reg));
                fprintf(fp, "jne EndIf%i\n", node->LabelSeed);
                releaseOneRegister();
                //Stmts
                tmp = tmp->nextBrother;
                generateAsm(tmp);
                fprintf(fp, "jmp EndIfElse%i\n", node->LabelSeed);
                fprintf(fp, "EndIf%i:\n", node->LabelSeed);
                //Else stmts
                tmp = tmp->nextBrother;
                generateAsm(tmp);
                fprintf(fp, "EndIfElse%i:\n", node->LabelSeed);
            }
        }
        else if (node->specificKind.statement == S_WHILE)
        {
            node->LabelSeed = LabelSeed;
            LabelSeed++;
            fprintf(fp, "While%i:\n", node->LabelSeed);
            //Expression
            TreeNode *tmp = node->firstChild;
            generateAsm(tmp);
            fprintf(fp, "cmp %s, 1\n", regToString(tmp->reg));
            fprintf(fp, "jne EndWhile%i\n", node->LabelSeed);
            releaseOneRegister();
            //Stmts
            tmp = tmp->nextBrother;
            generateAsm(tmp);
            fprintf(fp, "jmp While%i\n", node->LabelSeed);
            fprintf(fp, "EndWhile%i:\n", node->LabelSeed);
        }
        else if (node->specificKind.statement == S_RETURN)
        {
            if(node->firstChild)
            {
                TreeNode *tmp = node->firstChild;
                //Expression
                generateAsm(tmp);
                {
                    if (tmp->reg == EAX)
                    {
                        emitPrintReturn();
                        emitEpilogue();
                    }
                    else
                    {
                        fprintf(fp, "mov eax, %s\n", regToString(tmp->reg));
                        emitPrintReturn();
                        emitEpilogue();
                    }
                    releaseOneRegister();
                }
            }
            else
            {
                emitEpilogue();
            }
        }
    }
    break;
    case NK_EXPRESSION:
    {
        if(node->specificKind.expression==E_ASSIGN)
        {
            TreeNode *var = node->firstChild;
            //var
            generateAsm(var);
            //Expression
            TreeNode *exp = var->nextBrother;
            generateAsm(exp);
            if (exp->type!=var->type)
                printf("error - cant assign different variables \n");
            node->reg = 9;
            emitMemOp(STORE, var->attribute.name, exp->reg);
            releaseOneRegister();
        }
        else if (node->specificKind.expression == E_ROP)
        {
            TreeNode *a = node->firstChild;
            //additive_expression
            generateAsm(a);
            //additive_expression
            TreeNode *b = a->nextBrother;
            generateAsm(b);
            node->reg = a->reg;
            if (a->type != b->type)
                printf("error - cant compare different type variables\n");
            int op = node->attribute.op;
            switch (op)
            {
            case LT:
                op = LESS;
                break;
            case GT:
                op = GTR;
                break;
            case GTE:
                op = GTEQU;
                break;
            case LTE:
                op = LTEQU;
                break;
            case EQUAL:
                op = EQU;
                break;
            case NOTEQUAL:
                op = NEQU;
                break;
            default:
                op = 0;
            }
            emitRelOp(op, a->reg, b->reg);
            releaseOneRegister();
        }
        else if (node->specificKind.expression == E_AOP)
        {
            TreeNode *a = node->firstChild;
            //additive_expression
            generateAsm(a);
            //additive_expression
            TreeNode *b = a->nextBrother;
            generateAsm(b);
            node->reg = a->reg;
            if (a->type != b->type)
                printf("error - cant operate different type variables\n");
            int op = node->attribute.op;
            switch (op)
            {
            case ADD:
                op = PLUS;
                break;
            case SUB:
                op = MINUS;
                break;
            case MUL:
                op = MULT;
                break;
            case DIV:
                op = DIVI;
                break;
            default:
                op = 0;
            }
            emitAluOp(op, a->reg, b->reg);
            releaseOneRegister();
        }
        else if (node->specificKind.expression == E_CONST)
        {
            node->reg = nextFreeRegister();
            node->attribute.name = (char *)malloc(25 * sizeof(char));
            sprintf(node->attribute.name, "%d", node->attribute.value);
            emitLoadConst(node->reg, node->attribute.value);
        }
        else if (node->specificKind.expression == E_ID)
        {
            generateAsm(node->firstChild);
            node->reg = nextFreeRegister();
            node->type = node->firstChild->type;
            node->attribute.name = node->firstChild->attribute.name;
            emitMemOp(LOAD, node->firstChild->attribute.name, node->reg);
        }
        else if (node->specificKind.expression == E_CALL_FUN)
        {
            TreeNode *arg = node->firstChild;
            while(arg)
            {
                generateAsm(arg);
                ArgList[NumOfParams++] = arg->reg;
                arg = arg->nextBrother;
            }
            symbolEntry *tmp = symbolTable::lookUpSym(node->attribute.name);
            node->type = tmp->attr.type;
            emitCall(node->attribute.name, ArgList);
            node->reg = nextFreeRegister();
            NumOfParams = 0;
        }
        else if (node->specificKind.expression == E_VAR_ID)
        {
            symbolEntry *tmp = symbolTable::lookUpSym(node->attribute.name);
            node->type = tmp->attr.type;
            tmp->attr.references++;
        }
        else if (node->specificKind.expression == E_ARRAY_ID)
        {
            //Expression
            TreeNode *exp = node->firstChild;
            generateAsm(exp);
            symbolEntry *tmp = symbolTable::lookUpSym(node->attribute.name);
            node->type = tmp->attr.type;
            if (!tmp->attr.array)
                printf("error - %s is not an array\n", tmp->id);
            if (exp->type!=INT)
                printf("error - index in array is not integer\n", tmp->id);
            tmp->attr.references++;
            tmp->attr.regContainingArrIndex = exp->reg;
        }
    }
    break;
    default:
        break;
    }
}