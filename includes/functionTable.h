#ifndef FUNCTIONTABLE__H
#define FUNCTIONTABLE__H

#include <iostream>
#include <string>
#include <map>

class Node;

class FunctionTable {
public:
  FunctionTable() : paramTable(), funcTable() {}
  bool hasValue(const std::string& name) const;
  void setValue(const std::string& name, const Node* suite);
  void setParams(const std::string& name, const Node* params);
  const Node* getValue(const std::string& name) const;
  const Node* getParams(const std::string& name) const;
  void display(int) const;
private:
  std::map<std::string, const Node*> paramTable;
  std::map<std::string, const Node*> funcTable;
};

#endif
