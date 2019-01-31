#include <algorithm>
#include "functionTable.h"
#include "literal.h"

bool FunctionTable::hasValue(const std::string& name) const {
  std::map<std::string, const Node*>::const_iterator it = funcTable.find(name);
  return it != funcTable.end();
}

void FunctionTable::setValue(const std::string& name, const Node* suite) {
  funcTable[name] = suite;
}

void FunctionTable::setParams(const std::string& name, const Node* params) {
  paramTable[name] = params;
}

const Node* FunctionTable::getValue(const std::string& name) const {
  std::map<std::string, const Node*>::const_iterator it = funcTable.find(name);
  if(it == funcTable.end()) {
    throw name + std::string("not found");
  }
  return it->second;
}

const Node* FunctionTable::getParams(const std::string& name) const {
  std::map<std::string, const Node*>::const_iterator it = paramTable.find(name);
  if (it == paramTable.end()) return NULL;
  return it->second;
}

void FunctionTable::display(int i ) const {
  std::cout << "FuncTable: " << i << std::endl;
  std::map<std::string, const Node*>::const_iterator it = funcTable.begin();
  while (it != funcTable.end()) {
    std::cout << it->first << std::endl;
    it++;
  }
}
