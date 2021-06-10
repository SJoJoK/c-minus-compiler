#include "symTable.h"
#include "global.h"
#include "y.tab.h"
extern symbolAttributes parsedSymbolAttributes = symbolAttributes();
extern symbolTable *CurrentScope = new symbolTable(nullptr, 0, 0);
extern symbolTable& globalSymTab = *CurrentScope;
symbolEntry *symbolTable::lookUpSym(string id)
{
  struct symbolTable *tableIterator = CurrentScope;
  while (tableIterator != NULL)
  {
      if (tableIterator->symTab.count(id) == 1)
      {
        return &tableIterator->symTab.at(id);
      }
    tableIterator = tableIterator->outerScope;
  }
  printf("error - id: %s was never declared\n", id);
  exit(0);
}

void symbolTable::insertSym(string id, struct symbolAttributes attr, int type)
{
  symbolEntry symbol(id, type, attr);
  if (id=="main")
    symbol.attr.references = 1;

  printf("adding symbol to table\n");
  printSym(symbol);
  printf("\n\n");

  symbolTable *tableIterator = CurrentScope;
  while (tableIterator != nullptr)
  {
    if (tableIterator->symTab.count(id) == 1)
    {
      printf("error - id: %s was previously declared\n", id);
      exit(0);
    }
    tableIterator = tableIterator->outerScope;
  }
  CurrentScope->symTab.insert(pair<string, symbolEntry>(id, symbol));
  CurrentScope->numOfSym++;
}

void symbolTable::insertGlobalSym(string id, struct symbolAttributes attr, int type)
{
  symbolEntry symbol(id, type, attr);
  if (id == "main")
    symbol.attr.references = 1;

  printf("adding symbol to table\n");
  printSym(symbol);
  printf("\n\n");

  symbolTable *tableIterator = &globalSymTab;
  if (tableIterator->symTab.count(id) == 1)
  {
    printf("error - id: %s was previously declared\n", id);
    exit(0);
  }
  tableIterator->symTab.insert(pair<string, symbolEntry>(id, symbol));
  tableIterator->numOfSym++;
}

void symbolTable::initializeScope()
{
  ScopeLevel++;
  printf("Initializing new scope. Scope depth:%i\n", ScopeLevel);

  symbolTable *newTable = new symbolTable();
  newTable->outerScope = CurrentScope;
  newTable->numOfSym = 0;
  CurrentScope = newTable;
}

void symbolTable::finalizeScope()
{
  printf("Exiting scope level:%i\nPrinting Table\n\n", ScopeLevel);
  printf("Name\t\tType\t\tAttributes\n");
  symbolTableMap &symTab = CurrentScope->symTab;
  for (symbolTableMap::iterator it = symTab.begin(); it != symTab.end(); ++it)
  {
    printSym(it->second);
    printf("\n");

    if (it->second.attr.references == 0)
    {
      printf("warning - id \"%s\" was not referenced\n\n",
             it->second.id.c_str());
    }
  }
  printf("\n");

  if (ScopeLevel)
  {
    symbolTable *temp = CurrentScope;
    CurrentScope = CurrentScope->outerScope;
    delete(temp);
    temp = nullptr;
    ScopeLevel--;
  }
}

enum
{
  VAR,
  FUNC
};

void symbolTable::printSym(symbolEntry sym)
{
  printf("%s\t", sym.id.c_str());
  if (sym.id.length() < 9)
    printf("\t");
  if (sym.type == VAR)
    printf("Variable\t");
  else
    printf("Function\tParameters:%i\t", sym.attr.parameters);

  if (sym.attr.type == INT)
    printf("INT\t");
  else
    printf("VOID\t");

  if (sym.attr.array == 1)
    printf("array, size:%i", sym.attr.arrSize);
}

int inFunctionBody()
{
  if (ScopeLevel == 1)
    return 1;
  return 0;
}