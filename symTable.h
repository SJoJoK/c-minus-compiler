#pragma once

#define MAX_NAME_LENGTH 20
#define MAX_SYMBOLS_PER_TABLE 10

#include<unordered_map>
#include<string>

using namespace std;
class symbolAttributes
{
public:
	int type = 0;
	int initialized = 0;
	int references = 0;
	int scope = 0;
	int array = 0;
	int arrSize = 0;
	// 如果符号为参数，则parameter为其序号
	// 如果符号为函数，则为其所需参数数
	// 否则为零
	int parameters = 0;
	int localVarStackOffset = 0;
	int regContainingArrIndex = 0;
	void reset()
	{
		this->type = 0;
		this->initialized = 0;
		this->references = 0;
		this->scope = 0;
		this->array = 0;
		this->arrSize = 0;
		this->parameters = 0;
		this->localVarStackOffset = 0;
	}
};

class symbolEntry{
public:
	symbolEntry(){};
	symbolEntry(string id, int type, symbolAttributes attr) : id(id), type(type), attr(attr){};
	string id;
	int type;	/*variable or function*/
	symbolAttributes attr;
};

typedef std::unordered_map<string, symbolEntry> symbolTableMap;
class symbolTable{
public:
	symbolTable(){};
	symbolTable(symbolTable *outerScope, int numOfSym, int numOfLocalVar)
	{
		this->outerScope = outerScope;
		this->numOfSym = numOfSym;
		this->numOfLocalVar = numOfLocalVar;
	}
	symbolTableMap symTab;
	symbolTable *outerScope;
	int numOfSym;
  	int numOfLocalVar;
	symbolEntry *lookUpSym(string id);
	void insertSym(string id, symbolAttributes attr, int type);
	void insertGlobalSym(string id, symbolAttributes attr, int type);
	void initializeScope();
	void finalizeScope();
	void printSym(symbolEntry sym);
};

symbolAttributes parsedSymbolAttributes;

symbolTable globalSymTab;
symbolTable *CurrentScope;
