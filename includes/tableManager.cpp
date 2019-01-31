#include "tableManager.h"
#include "literal.h"

TableManager& TableManager::getInstance() {
  static TableManager instance;
  return instance;
}

bool TableManager::hasSymbol(const std::string& name) const {
  return symbolTables[currentScope].hasValue(name);
}

bool TableManager::hasFuncName(const std::string& name) const {
  return functionTables[currentScope].hasValue(name);
}

const Literal* TableManager::getSymbolValue(const std::string& name) const {
  SymbolTable symbolTable = symbolTables[currentScope];
  return symbolTable.getValue(name);
}

const Node* TableManager::getSuite(const std::string& name) const {
  FunctionTable funcTable = functionTables[currentScope];
  return funcTable.getValue(name);
}

const Node* TableManager::getParams(const std::string& name) const {
  FunctionTable funcTable = functionTables[currentScope];
  return funcTable.getParams(name);
}

void TableManager::insertSymbolValue(const std::string& name, const Literal* val) {
  SymbolTable& symbolTable = symbolTables[currentScope];
  symbolTable.setValue(name, val);
}

void TableManager::insertSuite(const std::string& name, const Node* suite) {
  FunctionTable& funcTable = functionTables[currentScope];
  funcTable.setValue(name, suite);
}

void TableManager::insertParams(const std::string& name, const Node* params) {
  FunctionTable& funcTable = functionTables[currentScope];
  funcTable.setParams(name, params);
}

int TableManager::getFunctionIdentScope(std::string funcName) {
  std::map<std::string, int>::const_iterator it = functionIdentScopeMap.find(funcName);
  if (it == functionIdentScopeMap.end()) {
    throw funcName + std::string("not found");
  }
  return it->second;
}

void TableManager::setFunctionIdentScope(std::string funcName) {
  functionIdentScopeMap[funcName] = currentScope;
}

void TableManager::pushScope(const std::string& name) {
  symbolTables.push_back(SymbolTable());
  FunctionTable funcTable;
  if (hasFuncName(name)) {
    funcTable = functionTables[currentScope];
  }
  functionTables.push_back(funcTable);
  currentScope++;
}

void TableManager::popScope() {
  if (currentScope>0) {
    currentScope--;
    if (symbolTables.size()>0) {
      symbolTables.pop_back();
    }
    if ( functionTables.size() > 0) {
      functionTables.pop_back();
    }
  }
}

void TableManager::display() const {
  for (unsigned int i = 0; i < symbolTables.size(); i++) {
    symbolTables[i].display(i);
  }
  for (unsigned int i = 0; i < functionTables.size(); i++) {
    functionTables[i].display(i);
  }
}
