#include <iostream>
#include <typeinfo>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "ast.h"
//#include "symbolTable.h"
#include "tableManager.h"

const Literal* IdentNode::eval() const {
  TableManager& tm = TableManager::getInstance();
  int scope = tm.getCurrentScope();
  auto symTables = tm.getSymbolTables();
  auto funcTables = tm.getfunctionTables();

  while (tm.getCurrentScope()>=0) {
    if (tm.hasSymbol(ident)) {
      const Literal* val = tm.getSymbolValue(ident);
      tm.setCurrentScope(scope);
      tm.setSymbolTables(symTables);
      tm.setfunctionTables(funcTables);
      return val;
    }
    else {
      if (tm.getCurrentScope()==0) {
        tm.setCurrentScope(scope);
        tm.setSymbolTables(symTables);
        tm.setfunctionTables(funcTables);
        std::string errorMsg = "NameError: name '" + ident +"' is not defined";
        throw errorMsg;
      }
      else {
        tm.popScope();
      }
    }
  }
  return NULL;
  // const Literal* val = SymbolTable::getInstance().getValue(ident);
  // return val;
}

const Literal* IndexNode::eval() const {
  if (!index) {
    throw std::string("SyntaxError: invalid syntax");
  }
  const Literal* x = index->eval();
  return x;
}

const Literal* SliceNode::eval() const {
  return NULL;
}

// const Literal* TrailerNode::eval() const {
//   if (!left || trailers.size() == 0 ) {
//     throw std::string("error");
//   }
//   const Literal* result = left->eval();
//   for (const Node* n : trailers) {
//     const IndexNode* ptr = dynamic_cast<const IndexNode*>(n);
//     if (ptr) {
//       const Literal* t = n->eval();
//       result = (*result)[*t];
//     }
//     else {
//       const SliceNode* sptr = static_cast<const SliceNode*>(n);
//       const Literal* start = sptr->getStart()->eval();
//       const Literal* end = sptr->getEnd()->eval();
//       const Literal* step = sptr->getStep()->eval();
//       const StringLiteral* stringLiteralPtr = dynamic_cast<const StringLiteral*>(result);
//       if (stringLiteralPtr) {
//         result = stringLiteralPtr->slice(start, end, step);
//       }
//       else{
//       result = static_cast<const ListLiteral*>(result)->slice(start, end, step);
//       }
//     }
//   }
//   return result;
// }

const Literal* TrailerNode::eval() const {
  if (!left || trailers.size() ==0 ) {
    throw std::string("error");
  }
  const Literal* result = left->eval();
  for (const Node* n : trailers) {
    const IndexNode* ptr = dynamic_cast<const IndexNode*>(n);
    if (ptr) {
      const Literal* index = n->eval();
      result = (*result)[*index];
    }
    else {
      const SliceNode* sliceNodePtr = static_cast<const SliceNode*>(n);
      result = evalSliceNode(result, sliceNodePtr);
    }
  }
  return result;
}

const Literal* TrailerNode::evalSliceNode(const Literal* result, const SliceNode* sliceNodePtr) const {
  int size = 0;
  const StringLiteral* stringLiteralPtr = dynamic_cast<const StringLiteral*>(result);
  if (stringLiteralPtr) {
    size = stringLiteralPtr->getValue().size();
  }
  else {
    size = static_cast<const ListLiteral*>(result)->getValue().size();
  }

  const Literal* start = NULL;
  const Literal* end = NULL;
  const Literal* step = NULL;
  bool isStepNegative = false;

  if (sliceNodePtr->getStart()) {
    start = sliceNodePtr->getStart()->eval();
    const IntLiteral* startPtr = static_cast<const IntLiteral*>(start);
    if (startPtr->getValue()<0) {
      start = new IntLiteral(size + startPtr->getValue());
      PoolOfNodes::getInstance().add(start);
    }
  }

  if (sliceNodePtr->getEnd()) {
    end = sliceNodePtr->getEnd()->eval();
    const IntLiteral* endPtr = static_cast<const IntLiteral*>(end);
    if (endPtr->getValue()<0) {
      end = new IntLiteral(size+endPtr->getValue());
      PoolOfNodes::getInstance().add(end);
    }
  }

  if (sliceNodePtr->getStep()) {
    step = sliceNodePtr->getStep()->eval();
    const IntLiteral* stepPtr = static_cast<const IntLiteral*>(step);
    if (stepPtr->getValue() < 0) {
      isStepNegative = true;
      if (!sliceNodePtr->getStart()) {
        start = new IntLiteral(size - 1);
        PoolOfNodes::getInstance().add(start);
      }
      if (!sliceNodePtr->getEnd()) {
        end = new IntLiteral(-1);
        PoolOfNodes::getInstance().add(end);
      }
    }
  }
  else {
    step = new IntLiteral(1);
    PoolOfNodes::getInstance().add(step);
  }

  if (!isStepNegative) {
    if(!sliceNodePtr->getStart()) {
      start = new IntLiteral(0);
      PoolOfNodes::getInstance().add(start);
    }
    if (!sliceNodePtr->getEnd()) {
      end = new IntLiteral(size);
      PoolOfNodes::getInstance().add(end);
    }
  }

  if (stringLiteralPtr) {
    result = stringLiteralPtr->slice(start, end, step);
  }
  else {
    result = static_cast<const ListLiteral*>(result)->slice(start, end, step);
  }
  return result;
}

const Literal* SuiteNode::eval() const {
  const Literal* result = NULL;

  for (const Node* n :stmts) {
    if (n) {
      if (TableManager::getInstance().hasReturned()) {
        break;
      }
      //const Literal* temp = n->eval();
      result = n->eval();

      const ReturnNode* ptr = dynamic_cast<const ReturnNode*>(n);
      if (ptr) {
        //result = temp;
        TableManager::getInstance().setReturned(true);
        break;
      }
    }
  }
  return result;
}

const Literal* FuncNode::eval() const {
  TableManager& tm = TableManager::getInstance();
  if (parameter) {
    tm.insertParams(funcName, parameter);
  }
  tm.insertSuite(funcName, suite);
  tm.setFunctionIdentScope(funcName);
  return NULL;
}

const Literal* VarArgNode::eval() const {
  return NULL;
}

const Literal* CallNode::eval() const {
  TableManager& tm = TableManager::getInstance();
  const Literal* result = NULL;

  if (tm.hasFuncName(funcName)) {
    const SuiteNode* suite =  dynamic_cast<const SuiteNode*>(tm.getSuite(funcName));
    auto symTables = tm.getSymbolTables();
    auto funcTables = tm.getfunctionTables();

    const ParamNode* paramNode = dynamic_cast<const ParamNode*>(tm.getParams(funcName));
    std::vector<Node*> paramVec;
    if (paramNode) {
      paramVec = paramNode->getValue();
    }

    std::vector<Node*> argVec = static_cast<const ArgNode*>(argNode)->getValue();
    std::vector<const Literal*> argValues;
    for (unsigned int i=0; i< argVec.size(); i++) {
      const VarArgNode* varArg = dynamic_cast<const VarArgNode*>(argVec[i]);
      if (varArg) {
        const ListLiteral* args = dynamic_cast<const ListLiteral*>(varArg->getValue()->eval());
        if (args) {
          std::vector<Node*> list = args->getValue();
          for (Node* n : list) {
            argValues.push_back(n->eval());
          }
        }
      }
      else {
      argValues.push_back(argVec[i]->eval());
    }
  }

    int scope = tm.getCurrentScope();

    while (tm.getFunctionIdentScope(funcName) < tm.getCurrentScope()) {
      tm.popScope();
    }

    tm.pushScope(funcName);
    for (unsigned int i=0; i < paramVec.size(); i++) {
      const IdentNode* param = dynamic_cast<const IdentNode*>(paramVec[i]);
      if (param) {
        std::string name = param->getIdent();
        tm.insertSymbolValue(name, argValues[i]);
      }
      else {
        const VarParamNode* varParam = static_cast<const VarParamNode*>(paramVec[i]);
        std::string name = varParam->getIdent();
        std::vector<Node*> vec;
        for (unsigned int j=i; j < argValues.size(); j++) {
          const Node* node = static_cast<const Node*>(argValues[j]);
          vec.push_back(const_cast<Node*>(node));
        }
        ListLiteral* list = new ListLiteral(vec);
        tm.insertSymbolValue(name, list);
      }
    }
    if (suite) {
      result =suite->eval();
      if (!result) {

      }
    }
    tm.popScope();

    tm.setCurrentScope(scope);
    tm.setSymbolTables(symTables);
    tm.setfunctionTables(funcTables);
    tm.setReturned(false);

    return result;
  }
  else {
    std::string errorMsg = "NameError: name '" + funcName + "' is not defined";
    throw errorMsg;
  }
}

const Literal* ReturnNode::eval() const {
  if (!result) {
    return NULL;
  }
  else {
    return result->eval();
  }
}

const Literal* PrintNode::eval() const{
  const Literal* temp = node->eval();
  if (temp) {
    temp->print();
  }
  else {
    std::cout << "None" << std::endl;
  }
  return NULL;
}

// const Literal* IfNode::eval() const {
//   if (test) {
//     int testFlag = 0;
//     const IntLiteral* intTest= dynamic_cast<const IntLiteral*>(test->eval());
//     if (intTest) {
//       testFlag = intTest->getValue();
//       }
//       else {
//         const FloatLiteral* floatTest = static_cast<const FloatLiteral*>(test->eval());
//         testFlag = floatTest->getValue();
//       }
//       if (testFlag && suite) {
//         suite->eval();
//       }
//       else {
//         if (elseSuite) {
//           elseSuite->eval();
//         }
//       }
//     }
//     else {
//       throw std::string("SyntaxError: invalid syntax");
//     }
//     return NULL;
//   }

const Literal* IfNode::eval() const {
  std::vector<Node*> v = suites;
  return evalElseIfNode(v);
}

const Literal* IfNode::evalElseIfNode(std::vector<Node*>& vec) const {
  int testFlag = 0;
  const ElseIfNode* test = static_cast<const ElseIfNode*>(vec[0]);
  const IntLiteral* intTest = dynamic_cast<const IntLiteral*>(test->getTest()->eval());
  if (intTest) {
    testFlag = intTest->getValue();
  }
  else {
    const FloatLiteral* floatTest = static_cast<const FloatLiteral*>(test->getTest()->eval());
    testFlag = (int) floatTest->getValue();
  }

  const ElseIfNode* suite = static_cast<const ElseIfNode*>(vec[0]);
  const Literal* result = NULL;

  if (testFlag) {
    result = suite->getSuite()->eval();
  }
  else {
    vec.erase(vec.begin());
    if (vec.size()>0) {
      result = evalElseIfNode(vec);
    }
    else if (elseSuite) {
      result = elseSuite->eval();
    }
  }
  return result;
}

const Literal* ElseIfNode::eval() const {
  return NULL;
}

const Literal* WhileNode::eval() const {
  int testFlag=1;
  while (testFlag) {
    const IntLiteral* intTest = dynamic_cast<const IntLiteral*>(test->eval());
    if (intTest) {
      testFlag = intTest->getValue();
    }
    else {
      const FloatLiteral* floatTest = static_cast<const FloatLiteral*>(test->eval());
      testFlag = (int) floatTest->getValue();
    }
    if (testFlag !=0) {
      suite->eval();
    }
    else if (elseSuite) {
      elseSuite->eval();
    }
  }
  return NULL;
}

const Literal* ForNode::eval() const {
  TableManager& tm = TableManager::getInstance();
  const IdentNode* ident = dynamic_cast<const IdentNode*>(expr);
  if (ident) {
    const StringLiteral* stringLiteralPtr = dynamic_cast<const StringLiteral*>(testlist);
    if (stringLiteralPtr) {
      std::string str = stringLiteralPtr->getValue();
      for (char& c : str) {
        std::string tempStr = "";
        StringLiteral* tempLiteral = new StringLiteral(tempStr + c);
        tm.insertSymbolValue(ident->getIdent(), tempLiteral);
        suite->eval();
      }
      if (elseSuite) {
        elseSuite->eval();
      }
    }
    else {
      const ListLiteral* listLiteralPtr = static_cast<const ListLiteral*>(testlist->eval());
      const std::vector<Node*>& list = listLiteralPtr->getValue();
      for (Node* n : list) {
        tm.insertSymbolValue(ident->getIdent(), n->eval());
        suite->eval();
      }
      if (elseSuite) {
        elseSuite->eval();
      }
    }
  }
  else {
    throw std::string("SyntaxError: invalid syntax");
  }
  return NULL;
}


const Literal* MinusUnaryNode::eval() const {
  if (!right) {
    throw "error";
  }
  const Literal* x = right->eval();
  const Literal* zero = new IntLiteral(0);
  PoolOfNodes::getInstance().add(zero);
  return *zero-(*x);
}

const Literal* TildeUnaryNode::eval() const {
  if (!right) {
    throw "error";
  }
  const Literal* x = right->eval();
  const Literal* minusOne = new IntLiteral(-1);
  PoolOfNodes::getInstance().add(minusOne);
  return *minusOne-(*x);
}

AsgBinaryNode::AsgBinaryNode(Node* left, Node* right) :
  BinaryNode(left, right) {
  // const Literal* res = right->eval(); //18-20 delete
  // const std::string n = static_cast<IdentNode*>(left)->getIdent();
  // SymbolTable::getInstance().setValue(n, res);
}


const Literal* AsgBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* res = right->eval();

  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  //SymbolTable::getInstance().setValue(n, res);
  TableManager::getInstance().insertSymbolValue(n, res);
  return res;
}

const Literal* AddBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x+*y);
}

const Literal* SubBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)-(*y));
}

const Literal* MulBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)*(*y));
}

const Literal* DivBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)/(*y));
}

const Literal* ModBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)%(*y);
}

const Literal* FlrDivBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return x->floorDivide(*y);
}

const Literal* PowBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return x->pow(*y);
}

const Literal* LShiftBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)<<(*y);
}

const Literal* RShiftBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)>>(*y);
}

const Literal* CatBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)+(*y);
}

const Literal* SliceBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)[*y];
}

const Literal* LessBinaryNode::eval() const {
  if (!left||!right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)<(*y);
}

const Literal* GreaterBinaryNode::eval() const {
  if (!left||!right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)>(*y);
}

const Literal* EqEqualBinaryNode::eval() const {
  if (!left||!right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)==(*y);
}

const Literal* GreaterEqualBinaryNode::eval() const {
  if (!left||!right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)>=(*y);
}

const Literal* LessEqualBinaryNode::eval() const {
  if (!left||!right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)<=(*y);
}

const Literal* NotEqualBinaryNode::eval() const {
  if (!left||!right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)!=(*y);
}
