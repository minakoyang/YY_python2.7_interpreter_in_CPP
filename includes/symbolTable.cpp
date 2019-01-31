#include <map>
//#include <algorithm>
#include "symbolTable.h"
#include "literal.h"

// SymbolTable& SymbolTable::getInstance() {
//   static SymbolTable instance;
//   return instance;
// }

bool SymbolTable::hasValue(const std::string& name) const {
  std::map<std::string, const Literal*>::const_iterator it = symbolTable.find(name);
  return it != symbolTable.end();
}

const Literal* SymbolTable::getValue(const std::string& name) const {
  std::map<std::string, const Literal*>::const_iterator it = symbolTable.find(name);
  if ( it == symbolTable.end() ) throw name+std::string(" not found");
  return it->second;  //second refer to literal*
}

void SymbolTable::setValue(const std::string& name, const Literal* val) {
  symbolTable[name] = val;
}

void SymbolTable::display(int i) const {
  std::cout << "SymbolTable: " << i << std::endl;
  std::map<std::string, const Literal*>::const_iterator it = symbolTable.begin();
  while ( it != symbolTable.end()) {
    std::cout << it->first<<": " << std::endl;
    it->second->eval()->print();
    it ++;
  }
}
