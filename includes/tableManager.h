#ifndef TABLEMANAGER__H
#define TABLEMANAGER__H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "symbolTable.h"
#include "functionTable.h"

class Literal;

class TableManager {
public:
  static TableManager& getInstance();

  bool hasSymbol(const std::string&) const;
  bool hasFuncName(const std::string&) const;
  const Literal* getSymbolValue(const std::string&) const;
  const Node* getSuite(const std::string&) const;
  const Node* getParams(const std::string&) const;
  void insertSymbolValue(const std::string&, const Literal*);
  void insertSuite(const std::string&, const Node*);
  void insertParams(const std::string&, const Node*);

  const std::vector<SymbolTable> getSymbolTables() const { return symbolTables; }
  const std::vector<FunctionTable> getfunctionTables() const { return functionTables; }
  void setSymbolTables(std::vector<SymbolTable>& symTable) { symbolTables = symTable; }
  void setfunctionTables(std::vector<FunctionTable>& funcTable) { functionTables = funcTable; }

  int getCurrentScope() const { return currentScope; }
  void setCurrentScope(int scope) { currentScope = scope; }
  int getFunctionIdentScope(std::string funcName);
  void setFunctionIdentScope(std::string funcName);
  void pushScope(const std::string&);
  void popScope();

  bool hasReturned() const {return returned; }
  void setReturned(bool r) { returned = r; }

  void display() const;

private:
  int currentScope;
  bool returned;
  std::vector<SymbolTable> symbolTables;
  std::vector<FunctionTable> functionTables;
  std::map<std::string, int> functionIdentScopeMap;

  TableManager() : currentScope(0), returned(false), symbolTables(), functionTables(), functionIdentScopeMap(){
    symbolTables.push_back(SymbolTable());
    functionTables.push_back(FunctionTable());
  }

  TableManager(const TableManager&);
  TableManager& operator=(const TableManager&);
};

#endif
