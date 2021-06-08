#ifndef SYMTABLE_H
#define SYMTABLE_H

#define MAX_NAME_LENGTH 20
#define MAX_SYMBOLS_PER_TABLE 10

class symbolAttributes{
public:
	int type;
  	int initialized;
  	int references;
	int scope;
	int array;
	int arrSize;    
// 如果符号为参数，则parameter为其序号
// 如果符号为函数，则为其所需参数数
// 否则为零
  	int parameters;
  	int localVarStackOffset;
  	int regContainingArrIndex;
};

class symbolEntry{
public:
	char id[MAX_NAME_LENGTH];
	int type;	/*variable or function*/
	struct symbolAttributes attr;
};

class symbolTable{
public:
	symbolTable(){};
	symbolTable(symbolTable *outerScope, int numOfSym, int numOfLocalVar)
	{
		this->outerScope = outerScope;
		this->numOfSym = numOfSym;
		this->numOfLocalVar = numOfLocalVar;
	}
	symbolEntry symTab[MAX_SYMBOLS_PER_TABLE];
	symbolTable *outerScope;
  	int numOfSym;
  	int numOfLocalVar;
	symbolEntry *lookUpSym(char *id);
	void insertSym(char *id, symbolAttributes attr, int type);
	void insertGlobalSym(char *id, symbolAttributes attr, int type);
	void initializeScope();
	void finalizeScope();
	void printSym(struct symbolEntry sym);
	void resetparsedSymbolAttributes();
	int inFunctionBody();
};

symbolAttributes parsedSymbolAttributes;

symbolTable globalSymTab;
symbolTable *CurrentScope;



#endif
