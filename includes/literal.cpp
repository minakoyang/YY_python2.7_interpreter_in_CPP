#include "literal.h"

const Literal* StringLiteral::slice(const Literal* start, const Literal* end, const Literal* step) const {
  const IntLiteral* startPtr = static_cast<const IntLiteral*>(start);
  const IntLiteral* endPtr = static_cast<const IntLiteral*>(end);
  const IntLiteral* stepPtr = static_cast<const IntLiteral*>(step);

  //if ( stepptr->getValue() == NULL || stepptr->getValue() == 1) {
  //  return new StringLiteral (val.substr(startptr->getValue(), endptr->getValue() - startptr->getValue()));
//  }
//  else if (stepptr->getValue() == 0 ){
//    throw std::string("ValueError: slice step cannot be zero");
//  }
//  else {
//    std::string temp = "";
//    for (int i = startptr->getValue(); i < endptr->getValue(); i += stepptr->getValue()) {
//      temp += val[i];
//    }
//    const Literal* node = new StringLiteral(temp);
//    PoolOfNodes::getInstance().add(node);
//    return node;
//  }
  std::string temp ="";
  if (stepPtr->getValue() < 0) {
    // int a = startPtr->getValue();
    // int b = endPtr->getValue();
    // if (abs(a) > (int)val.size() || abs(b) > (int)val.size()) {
    //   std::cout<<""<<std::endl;
    // }
    for (int i = startPtr->getValue(); i > endPtr->getValue(); i += stepPtr->getValue()) {
      if (i >= 0 && i < (int)val.size()){
        temp += val.substr(i, 1);
      }
    }
  }
  else {
    // int a = startPtr->getValue() - endPtr->getValue();
    // if (abs(a) > (int)val.size()) {
    //   throw std::string("IndexError: string index out of range");
    // }
    for (int i = startPtr->getValue(); i < endPtr->getValue(); i += stepPtr->getValue()) {
      if (i>= 0 && i < (int)val.size()){
        temp += val.substr(i, 1);
      }
    }
  }
  const Literal* node = new StringLiteral(temp);
  PoolOfNodes::getInstance().add(node);
  return node;
}

const Literal* ListLiteral::slice(const Literal* start, const Literal* end, const Literal* step) const {
  const IntLiteral* startPtr = static_cast<const IntLiteral*>(start);
  const IntLiteral* endPtr = static_cast<const IntLiteral*>(end);
  const IntLiteral* stepPtr = static_cast<const IntLiteral*>(step);
  std::vector<Node*>* temp = new std::vector<Node*>;

  if (stepPtr->getValue() < 0 ) {
    for (int i = startPtr->getValue(); i > endPtr->getValue(); i += stepPtr->getValue()) {
      if (i>= 0 && i < (int)list.size()){
        temp->push_back(list[i]);
      }
    }
  }
  else {
    for (int i = startPtr->getValue(); i < endPtr->getValue(); i += stepPtr->getValue()) {
      if (i>= 0 && i < (int)list.size()){
        temp->push_back(list[i]);
      }
    }
  }
  const Literal* node = new ListLiteral(*temp);
  PoolOfNodes::getInstance().add(node);
  delete temp;
  return node;
}

// void ListLiteral::print() const {
//   std::stringstream ss;
//   ss << "[";
//   for (const Node* n : list) {
//     const FloatLiteral* floatLiteralPtr = dynamic_cast <const FloatLiteral*>(n->eval());
//     if (floatLiteralPtr) {
//       long double val = floatLiteralPtr->getValue();
//       if (std::abs(std::floor(val) - val) < 1e-6 && val < 1e+16) {
//         ss << val << ".0" << ", ";
//       }
//       else {
//         ss << std::setprecision(12) << val << ", ";
//       }
//     }
//     else {
//       const IntLiteral* intLiteralPtr = dynamic_cast<const IntLiteral*>(n->eval());
//       if (intLiteralPtr) {
//         ss << intLiteralPtr->getValue() << ", ";
//       }
//       else {
//         const StringLiteral* stringLiteralPtr = dynamic_cast<const StringLiteral*>(n->eval());
//         if (stringLiteralPtr) {
//           ss << "'" << stringLiteralPtr->getValue() << "', ";
//         }
//         else {
//           const ListLiteral* listLiteralPtr = static_cast<const ListLiteral*>(n->eval());
//         }
//       }
//     }
//   }
//   std::string result = ss.str();
//   result = result.substr(0, result.size() - 2) + "]";
//   std::cout << result << std::endl;
// }

const std::string ListLiteral::getValueString() const {
  std::stringstream ss;
  ss << "[";
  for (const Node* n : list) {
    const FloatLiteral* floatLiteralPtr = dynamic_cast<const FloatLiteral*>(n->eval());
    if (floatLiteralPtr) {
      long double val = floatLiteralPtr->getValue();
      if (std::abs(std::floor(val) - val) < 1e-6 && val < 1e+16) {
        ss << val << ".0" << ", ";
      }
      else {
        ss << std::setprecision(12) << val << ", ";
      }
    }
    else {
      const IntLiteral* intLiteralPtr = dynamic_cast<const IntLiteral*>(n->eval());
      if (intLiteralPtr) {
        ss << intLiteralPtr->getValue() << ", ";
      }
      else {
        const StringLiteral* stringLiteralPtr = dynamic_cast<const StringLiteral*>(n->eval());
        if (stringLiteralPtr) {
          ss << "'" << stringLiteralPtr->getValue() << "', ";
        }
        else {
          const ListLiteral* listLiteralPtr = static_cast<const ListLiteral*>(n->eval());
          ss << listLiteralPtr->getValueString() << ", ";
        }
      }
    }
  }
  std::string result = ss.str();
  result = result.substr(0, result.size() - 2) + "]";
  return result;
}

const Literal* ListLiteral::opEqEqual(std::vector<Node*> lhs) const {
  int equalFlag=1;
  if(lhs.size() != list.size()) {
    equalFlag = 0;
  }
  else {
    for (unsigned int i = 0; i < lhs.size(); i++) {
      const Literal* x = lhs[i]->eval();
      const Literal* y = list[i]->eval();
      const IntLiteral* test = dynamic_cast<const IntLiteral*>((*x)!=(*y));
      if (test) {
        if (test->getValue()) {
          equalFlag = 0;
          break;
        }
      }
      else {
        if (static_cast<const FloatLiteral*>((*x)!=(*y))->getValue()) {
          equalFlag = 0;
        }
      }
    }
  }
  const Literal* node = new FloatLiteral(equalFlag);
  PoolOfNodes::getInstance().add(node);
  return node;
}

const Literal* ListLiteral::opLess(std::vector<Node*> lhs) const {
  int testFlag = 0;
  unsigned int size = lhs.size()<=list.size()?lhs.size():list.size();
  unsigned int i = 0;
  for (; i<size; i++) {
    const Literal* x = lhs[i]->eval();
    const Literal* y = list[i]->eval();

    const IntLiteral* less = dynamic_cast<const IntLiteral*>((*x)<(*y));
    if (less) {
      if (less->getValue()) {
      testFlag =1;
      break;
    }
    else if (static_cast<const IntLiteral*>((*x)>(*y))->getValue()) {
      break;
    }
  }
  else {
    if (static_cast<const FloatLiteral*>((*x)<(*y))->getValue()) {
      testFlag =1;
      break;
    }
    else if (static_cast<const FloatLiteral*>((*x)>(*y))->getValue()) {
      break;
    }
  }
}
if (size < list.size() && i == size) {
  testFlag =1;
}
const Literal* node = new FloatLiteral(testFlag);
PoolOfNodes::getInstance().add(node);
return node;
}

const Literal* ListLiteral::opGreater(std::vector<Node*> lhs) const{
  int testFlag = 0;
  unsigned int size = lhs.size()>=list.size()?list.size():lhs.size();
  unsigned int i = 0;
  for (; i<size; i++) {
    const Literal* x = lhs[i]->eval();
    const Literal* y = list[i]->eval();

    const IntLiteral* greater = dynamic_cast<const IntLiteral*>((*x)>(*y));
    if (greater) {
      if (greater->getValue()) {
      testFlag =1;
      break;
    }
    else if (static_cast<const IntLiteral*>((*x)<(*y))->getValue()) {
      break;
    }
  }
  else {
    if (static_cast<const FloatLiteral*>((*x)>(*y))->getValue()) {
      testFlag =1;
      break;
    }
    else if (static_cast<const FloatLiteral*>((*x)<(*y))->getValue()) {
      break;
    }
  }
}
if (size < lhs.size() && i == size) {
  testFlag =1;
}
const Literal* node = new FloatLiteral(testFlag);
PoolOfNodes::getInstance().add(node);
return node;
}

const Literal* ListLiteral::opLessEqual(std::vector<Node*> lhs) const{
  int testFlag = 0;
  unsigned int size = lhs.size()<=list.size()?lhs.size():list.size();
  unsigned int i = 0;
  for (; i<size; i++) {
    const Literal* x = lhs[i]->eval();
    const Literal* y = list[i]->eval();

    const IntLiteral* less = dynamic_cast<const IntLiteral*>((*x)<(*y));
    if (less) {
      if (less->getValue()) {
      testFlag =1;
      break;
    }
    else if (static_cast<const IntLiteral*>((*x)>(*y))->getValue()) {
      break;
    }
    if (i == size -1) {
      testFlag =1;
    }
  }
  else {
    if (static_cast<const FloatLiteral*>((*x)<(*y))->getValue()) {
      testFlag =1;
      break;
    }
    else if (static_cast<const FloatLiteral*>((*x)>(*y))->getValue()) {
      break;
    }
    if ( i == size -1) {
      testFlag = 1;
    }
  }
}
// if (size < list.size() && i == size) {
//   testFlag =1;
// }
const Literal* node = new FloatLiteral(testFlag);
PoolOfNodes::getInstance().add(node);
return node;
}

const Literal* ListLiteral::opGreaterEqual(std::vector<Node*> lhs) const{
  int testFlag = 0;
  unsigned int size = lhs.size()>=list.size()?list.size():lhs.size();
  unsigned int i = 0;
  for (; i<size; i++) {
    const Literal* x = lhs[i]->eval();
    const Literal* y = list[i]->eval();

    const IntLiteral* greater = dynamic_cast<const IntLiteral*>((*x)>(*y));
    if (greater) {
      if (greater->getValue()){
      testFlag =1;
      break;
    }
    else if (static_cast<const IntLiteral*>((*x)<(*y))->getValue()) {
      break;
    }
    if (i == size -1) {
      testFlag =1;
    }
  }
  else {
    if (static_cast<const FloatLiteral*>((*x)>(*y))->getValue()) {
      testFlag =1;
      break;
    }
    else if (static_cast<const FloatLiteral*>((*x)<(*y))->getValue()) {
      break;
    }
    if ( i == size -1) {
      testFlag = 1;
    }
  }
}
// if (size < list.size() && i == size) {
//   testFlag =1;
// }
const Literal* node = new FloatLiteral(testFlag);
PoolOfNodes::getInstance().add(node);
return node;
}

const Literal* ListLiteral::opNotEqual(std::vector<Node*> lhs) const {
  int equalFlag = 0;
  if (lhs.size() != list.size()) {
    equalFlag =1;
  }
  else {
    for (unsigned int i =0 ; i < lhs.size(); i++) {
      const Literal* x = lhs[i]->eval();
      const Literal* y = list[i]->eval();

      const IntLiteral* test = dynamic_cast<const IntLiteral*>((*x)!=(*y));
      if (test) {
        if (test->getValue()) {
          equalFlag=1;
          break;
        }
      }
      else {
        if (static_cast<const FloatLiteral*>((*x)!=(*y))->getValue()) {
          equalFlag = 1;
        }
      }
    }
  }
  const Literal* node = new FloatLiteral(equalFlag);
  PoolOfNodes::getInstance().add(node);
  return node;
}
