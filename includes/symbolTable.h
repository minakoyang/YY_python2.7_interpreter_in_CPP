#ifndef SYMBOLTABLE__H
#define SYMBOLTABLE__H

#include <iostream>
#include <string>
#include <map>
//#include <algorithm>

class Literal;

class SymbolTable {
public:
  //static   SymbolTable& getInstance();
  SymbolTable() :symbolTable() {}
  bool hasValue(const std::string& name) const;
  void setValue(const std::string& name, const Literal* val);
  const Literal* getValue(const std::string& name) const;
  void display(int) const;
private:
  // std::map<std::string, const Literal*> table;
  // SymbolTable() : table() {}
  // SymbolTable(const SymbolTable&);
  // SymbolTable operator=(const SymbolTable&);
  std::map<std::string, const Literal*> symbolTable;
};

#endif
