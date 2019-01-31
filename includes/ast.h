#pragma once

//  Declarations for a calculator that builds an AST
//  and a graphical representation of the AST.
//  by Brian Malloy

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "literal.h"

extern void yyerror(const char*);
extern void yyerror(const char*, const char);

class IdentNode : public Node {
public:
  IdentNode(const std::string id) : Node(), ident(id) { }
  virtual ~IdentNode() {}
  const std::string getIdent() const { return ident; }
  virtual const Literal* eval() const;
private:
  std::string ident;
};

class IndexNode : public Node {
public:
  IndexNode(Node* i) : Node(), index(i) { }
  virtual const Literal* eval() const;
  IndexNode(const IndexNode&) = delete;
  IndexNode& operator=(const IndexNode&) = delete;
private:
  Node* index;
};

class SliceNode : public Node {
public:
  SliceNode(Node* s, Node* e, Node* st) : Node(), start(s), end(e), step(st) {}
  virtual const Literal* eval() const;
  Node* getStart() const { return start; }
  Node* getEnd() const { return end; }
  Node* getStep() const { return step; }
  SliceNode(const SliceNode&) = delete;
  SliceNode& operator=(const SliceNode&) = delete;
private:
  Node* start;
  Node* end;
  Node* step;
};

class TrailerNode : public Node {
public:
  TrailerNode(Node* l, const std::vector<Node*>& vec) : Node(), left(l), trailers(vec) {}
  virtual const Literal* eval() const;
  const Literal* evalSliceNode(const Literal*, const SliceNode*) const;
  TrailerNode(const TrailerNode&) = delete;
  TrailerNode& operator=(const TrailerNode&) = delete;
private:
  Node* left;
  std::vector<Node*> trailers;
};

class SuiteNode : public Node {
public:
  SuiteNode(const std::vector<Node*>& vec) : Node(), stmts(vec) {}
  virtual const Literal* eval() const;
private:
  std::vector<Node*> stmts;
};

class FuncNode : public Node {
public:
  FuncNode(const std::string& name,Node* p, Node* n) : Node(), funcName(name), parameter(p), suite(n) {}
  virtual const Literal* eval() const;
  FuncNode(const FuncNode&) = delete;
  FuncNode& operator=(const FuncNode&) = delete;
private:
  std::string funcName;
  Node* parameter;
  Node* suite;
};

class VarParamNode : public Node {
public:
  VarParamNode(const std::string& s): Node(), ident(s) {}
  const std::string getIdent() const { return ident;}
  virtual const Literal* eval() const { return NULL; }
private:
  std::string ident;
};

class ParamNode : public Node {
public:
  ParamNode(const std::vector<Node*> vec) : Node(), params(vec) {}
  virtual const Literal* eval() const { return NULL;}
  std::vector<Node*> getValue() const { return params; }
private:
  std::vector<Node*> params;
};

class CallNode : public Node {
public:
  CallNode(const std::string& name, Node* n) : Node(), funcName(name), argNode(n) {}
  virtual const Literal* eval() const;
  CallNode(const CallNode&) = delete;
  CallNode& operator=(CallNode&) = delete;
private:
  std::string funcName;
  Node* argNode;
};

class VarArgNode : public Node {
public:
  VarArgNode(Node* n) : Node(), list(n) {}
  virtual const Literal* eval() const;
  Node* getValue() const { return list; }
  VarArgNode(const VarArgNode&) = delete;
  VarArgNode& operator=(const VarArgNode&) = delete;
private:
  Node* list;
};

class ArgNode : public Node {
public:
  ArgNode(const std::vector<Node*> vec) : Node(), args(vec) {}
  virtual const Literal* eval() const {return NULL;}
  std::vector<Node*> getValue() const { return args;}
private:
  std::vector<Node*>args;
};

class ReturnNode : public Node {
public:
  ReturnNode(Node* n) : Node(), result(n) {}
  virtual const Literal* eval() const;
  ReturnNode(const ReturnNode&) = delete;
  ReturnNode& operator=(const ReturnNode&) = delete;
private:
  Node* result;
};

class PrintNode : public Node {
public:
  PrintNode(Node* n) : Node(), node(n) {}
  virtual const Literal* eval() const;
  PrintNode(const PrintNode&) = delete;
  PrintNode& operator=(const PrintNode&) = delete;
private:
  Node* node;
};

// class IfNode : public Node {
// public:
//   IfNode(Node* t, Node* s, Node* es) : Node(), test(t), suite(s), elseSuite(es) {}
//   virtual const Literal* eval() const;
//   IfNode(const IfNode&) = delete;
//   IfNode& operator=(const IfNode&) = delete;
// private:
//   Node* test;
//   Node* suite;
//   Node* elseSuite;
// };

class IfNode : public Node {
public:
  IfNode(std::vector<Node*> vec, Node* es) : Node(), suites(vec), elseSuite(es) {}
  virtual const Literal* eval() const;
  const Literal* evalElseIfNode(std::vector<Node*>&) const;
  IfNode(const IfNode&) = delete;
  IfNode& operator=(const IfNode&) = delete;
private:
  std::vector<Node*> suites;
  Node* elseSuite;
};

class ElseIfNode : public Node {
public:
  ElseIfNode(Node* t, Node* s) : Node(), test(t), suite(s) {}
  virtual const Literal* eval() const;
  const Node* getTest() const { return test; }
  const Node* getSuite() const { return suite; }
  ElseIfNode(const ElseIfNode&) = delete;
  ElseIfNode& operator=(const ElseIfNode&) = delete;
private:
  Node* test;
  Node* suite;
};

class WhileNode : public Node {
public:
  WhileNode(Node* t, Node* s, Node* es) : Node(), test(t), suite(s), elseSuite(es) {}
  virtual const Literal* eval() const;
  WhileNode(const WhileNode&) = delete;
  WhileNode& operator=(const WhileNode&) = delete;
private:
  Node* test;
  Node* suite;
  Node* elseSuite;
};

class ForNode : public Node {
public:
  ForNode(Node* e, Node* tl, Node* s, Node* es) : Node(), expr(e), testlist(tl), suite(s), elseSuite(es) {}
  virtual const Literal* eval() const;
  ForNode(const ForNode&) = delete;
  ForNode& operator=(const ForNode&) = delete;
private:
  Node* expr;
  Node* testlist;
  Node* suite;
  Node* elseSuite;
};


class UnaryNode : public Node {
public:
  UnaryNode(Node* r) : Node(), right(r) {}
    virtual const Literal* eval() const = 0;
    Node* getRight() const { return right; }
    UnaryNode(const UnaryNode&) = delete;
    UnaryNode& operator = (const UnaryNode&) = delete;
protected:
  Node* right;
};

class MinusUnaryNode : public UnaryNode {
public:
  MinusUnaryNode(Node* right) : UnaryNode(right) {}
  virtual const Literal* eval() const;
};

class TildeUnaryNode : public UnaryNode {
public:
  TildeUnaryNode(Node* right) : UnaryNode(right) {}
  virtual const Literal* eval() const;
};

class BinaryNode : public Node {
public:
  BinaryNode(Node* l, Node* r) : Node(), left(l), right(r) {}
  virtual const Literal* eval() const = 0;
  Node* getLeft()  const { return left; }
  Node* getRight() const { return right; }
  BinaryNode(const BinaryNode&) = delete;
  BinaryNode& operator=(const BinaryNode&) = delete;
protected:
  Node *left;
  Node *right;
};

class AsgBinaryNode : public BinaryNode {
public:
  AsgBinaryNode(Node* left, Node* right);
  virtual const Literal* eval() const;
};

class AddBinaryNode : public BinaryNode {
public:
  AddBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class SubBinaryNode : public BinaryNode {
public:
  SubBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class MulBinaryNode : public BinaryNode {
public:
  MulBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class DivBinaryNode : public BinaryNode {
public:
  DivBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class ModBinaryNode : public BinaryNode {
public:
  ModBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class FlrDivBinaryNode : public BinaryNode {
public:
  FlrDivBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class PowBinaryNode : public BinaryNode {
public:
  PowBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class LShiftBinaryNode : public BinaryNode {
public:
  LShiftBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class RShiftBinaryNode : public BinaryNode {
public:
  RShiftBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class CatBinaryNode : public BinaryNode {
public:
  CatBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class SliceBinaryNode : public BinaryNode {
public:
  SliceBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class LessBinaryNode : public BinaryNode {
public:
  LessBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class GreaterBinaryNode : public BinaryNode {
public:
  GreaterBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class EqEqualBinaryNode : public BinaryNode {
public:
  EqEqualBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class GreaterEqualBinaryNode : public BinaryNode {
public:
  GreaterEqualBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class LessEqualBinaryNode : public BinaryNode {
public:
  LessEqualBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class NotEqualBinaryNode : public BinaryNode {
public:
  NotEqualBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};
