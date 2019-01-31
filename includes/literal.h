#include "node.h"
#include "poolOfNodes.h"
#include <cmath>
#include <iomanip>
#include <sstream>

class Literal : public Node {
public:
  virtual ~Literal() {}

  virtual const Literal* operator+(const Literal& rhs) const =0;
  virtual const Literal* opPlus(long double) const =0;
  virtual const Literal* opPlus(int) const =0;
  virtual const Literal* opPlus(std::string) const = 0;
  virtual const Literal* opPlus(std::vector<Node*>) const = 0;

  virtual const Literal* operator*(const Literal& rhs) const =0;
  virtual const Literal* opMult(long double) const =0;
  virtual const Literal* opMult(int) const =0;
  virtual const Literal* opMult(std::string) const = 0;
  virtual const Literal* opMult(std::vector<Node*>) const = 0;

  virtual const Literal* operator-(const Literal& rhs) const =0;
  virtual const Literal* opSubt(long double) const =0;
  virtual const Literal* opSubt(int) const =0;

  virtual const Literal* operator/(const Literal& rhs) const =0;
  virtual const Literal* opDiv(long double) const =0;
  virtual const Literal* opDiv(int) const =0;

  virtual const Literal* operator%(const Literal& rhs) const =0;
  virtual const Literal* opMod(long double) const =0;
  virtual const Literal* opMod(int) const =0;

  virtual const Literal* floorDivide(const Literal& rhs) const =0;
  virtual const Literal* opFlrDiv(long double) const =0;
  virtual const Literal* opFlrDiv(int) const =0;

  virtual const Literal* pow(const Literal& rhs) const =0;
  virtual const Literal* opPow(long double) const =0;
  virtual const Literal* opPow(int) const =0;

  virtual const Literal* operator<<(const Literal& rhs) const =0;
  virtual const Literal* opLshift(long double) const =0;
  virtual const Literal* opLshift(int) const =0;

  virtual const Literal* operator>>(const Literal& rhs) const =0;
  virtual const Literal* opRshift(long double) const =0;
  virtual const Literal* opRshift(int) const =0;

  virtual const Literal* operator[](const Literal& rhs) const = 0;
  virtual const Literal* opIndex(long double) const = 0;
  virtual const Literal* opIndex(int) const = 0;
  virtual const Literal* opIndex(std::string) const = 0;
  virtual const Literal* opIndex(std::vector<Node*>) const = 0;

  virtual const Literal* operator<(const Literal& rhs) const = 0;
  virtual const Literal* opLess(long double) const = 0;
  virtual const Literal* opLess(int) const =0;
  virtual const Literal* opLess(std::string) const = 0;
  virtual const Literal* opLess(std::vector<Node*>) const =0;

  virtual const Literal* operator>(const Literal& rhs) const = 0;
  virtual const Literal* opGreater(long double) const = 0;
  virtual const Literal* opGreater(int) const =0;
  virtual const Literal* opGreater(std::string) const = 0;
  virtual const Literal* opGreater(std::vector<Node*>) const =0;

  virtual const Literal* operator==(const Literal& rhs) const = 0;
  virtual const Literal* opEqEqual(long double) const = 0;
  virtual const Literal* opEqEqual(int) const =0;
  virtual const Literal* opEqEqual(std::string) const = 0;
  virtual const Literal* opEqEqual(std::vector<Node*>) const =0;

  virtual const Literal* operator>=(const Literal& rhs) const = 0;
  virtual const Literal* opGreaterEqual(long double) const = 0;
  virtual const Literal* opGreaterEqual(int) const =0;
  virtual const Literal* opGreaterEqual(std::string) const = 0;
  virtual const Literal* opGreaterEqual(std::vector<Node*>) const =0;

  virtual const Literal* operator<=(const Literal& rhs) const = 0;
  virtual const Literal* opLessEqual(long double) const = 0;
  virtual const Literal* opLessEqual(int) const =0;
  virtual const Literal* opLessEqual(std::string) const = 0;
  virtual const Literal* opLessEqual(std::vector<Node*>) const =0;

  virtual const Literal* operator!=(const Literal& rhs) const = 0;
  virtual const Literal* opNotEqual(long double) const = 0;
  virtual const Literal* opNotEqual(int) const =0;
  virtual const Literal* opNotEqual(std::string) const = 0;
  virtual const Literal* opNotEqual(std::vector<Node*>) const =0;

  virtual const Literal* eval() const = 0;
  virtual void print() const {
    std::cout << "No Way" << std::endl;
  }
};

class FloatLiteral: public Literal {
public:
  FloatLiteral(long double _val): val(_val) {}

  virtual const Literal* operator+(const Literal& rhs) const  {  //accept function
    return rhs.opPlus(val);
  }
  virtual const Literal* opPlus(long double lhs) const  {  //visit function float + float
    const Literal* node = new FloatLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPlus(int lhs) const  {  //visit function float + int
    const Literal* node = new FloatLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPlus(std::string) const {
    throw std::string("TypeError: cannot concatenate 'str' and 'float' objects");
    return NULL;
  }
  virtual const Literal* opPlus(std::vector<Node*>) const {
    throw std::string("TypeError: can only concatenate list (not 'float') to list");
    return NULL;
  }

  virtual const Literal* operator-(const Literal& rhs) const  {
    return rhs.opSubt(val);
  }
  virtual const Literal* opSubt(long double lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opSubt(int lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator*(const Literal& rhs) const  {
    return rhs.opMult(val);
  }
  virtual const Literal* opMult(long double lhs) const  {
    const Literal* node = new FloatLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(int lhs) const  {
    const Literal* node = new FloatLiteral(static_cast<long double>(lhs) * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(std::string) const {
    throw std::string("TypeError: can't multiply sequence by non-int of type 'float'");
    return NULL;
  }
  virtual const Literal* opMult(std::vector<Node*>) const {
    throw std::string("TypeError: can't multiply sequence by non-int of type 'float'");
    return NULL;
  }

  virtual const Literal* operator/(const Literal& rhs) const  {
    return rhs.opDiv(val);
  }
  virtual const Literal* opDiv(long double lhs) const  {
    if ( val == 0 ) throw std::string("ZeroDivisionError: float division by zero");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opDiv(int lhs) const  {
    if ( val == 0 ) throw std::string("ZeroDivisionError: integer division or modulo by zero");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator%(const Literal& rhs) const  {
    return rhs.opMod(val);
  }
  virtual const Literal* opMod(long double lhs) const  {
    if (val == 0) throw std::string("ZeroDivisionError: float modulo");
    const Literal* node = new FloatLiteral(std::fmod(std::fmod(lhs,val) + val, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMod(int lhs) const  {
    if (val == 0) throw std::string("ZeroDivisionError: integer division or modulo by zero");
    const Literal* node = new FloatLiteral(std::fmod(std::fmod(lhs,val) + val, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* floorDivide(const Literal& rhs) const {
    return rhs.opFlrDiv(val);
  }
  virtual const Literal* opFlrDiv(long double lhs) const {
    if (val == 0) throw std::string("ZeroDivisionError: float divmod()");
    const Literal* node = new FloatLiteral(std::floor(lhs / val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opFlrDiv(int lhs) const {
    if (val == 0) throw std::string("ZeroDivisionError: integer division or modulo by zero");
    const Literal* node = new FloatLiteral(std::floor(lhs / val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* pow(const Literal& rhs) const {
    return rhs.opPow(val);
  }
  virtual const Literal* opPow(long double lhs) const{
    const Literal* node = new FloatLiteral(std::pow(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPow(int lhs) const {
    const Literal* node = new FloatLiteral(std::pow(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator<<(const Literal& rhs) const {
    return rhs.opLshift(val);
  }
  virtual const Literal* opLshift(long double lhs) const {
    std::cout << "TypeError: unsupported operand type(s) for <<: 'float' and 'float'" << std::endl;
    return NULL;
  }
  virtual const Literal* opLshift(int lhs) const {
    std::cout << "TypeError: unsupported operand type(s) for <<: 'int' and 'float'" << std::endl;
    return NULL;
  }

  virtual const Literal* operator>>(const Literal& rhs) const {
    return rhs.opRshift(val);
  }
  virtual const Literal* opRshift(long double lhs) const {
    std::cout << "TypeError: unsupported operand type(s) for >>: 'float' and 'float'" << std::endl;
    return NULL;
  }
  virtual const Literal* opRshift(int lhs) const {
    std::cout << "TypeError: unsupported operand type(s) for >>: 'int' and 'float'" << std::endl;
    return NULL;
  }

  virtual const Literal* operator[](const Literal& rhs) const {
    return rhs.opIndex(val);
  }
  virtual const Literal* opIndex(long double lhs) const {
    throw std::string("TypeError: 'float' object has no attribute '__getitem__'");
    return NULL;
  }
  virtual const Literal* opIndex(int lhs) const {
    throw std::string("TypeError: 'float' object has no attribute '__getitem__'");
    return NULL;
  }
  virtual const Literal* opIndex(std::string lhs) const {
    throw std::string("TypeError: string indices must be integers, not float");
    return NULL; }
  virtual const Literal* opIndex(std::vector<Node*> lhs) const {
    throw std::string("TypeError: list indices must be integers, not float");
    return NULL; }

  virtual const Literal* operator<(const Literal& rhs) const {
    return rhs.opLess(val);
  }
  virtual const Literal* opLess(long double lhs) const {
    const Literal* node = new FloatLiteral(lhs < val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLess(int lhs) const {
    const Literal* node = new FloatLiteral(lhs<val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLess(std::string lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opLess(std::vector<Node*> lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }

  virtual const Literal* operator>(const Literal& rhs) const {
    return rhs.opGreater(val);
  }
  virtual const Literal* opGreater(long double lhs) const {
    const Literal* node = new FloatLiteral(lhs > val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGreater(int lhs) const {
    const Literal* node = new FloatLiteral(lhs>val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGreater(std::string lhs) const {  //string always greater than numbers
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }

  virtual const Literal* opGreater(std::vector<Node*> lhs) const {  //list always greater than numbers
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }

  virtual const Literal* operator==(const Literal& rhs) const {
    return rhs.opEqEqual(val);
  }
  virtual const Literal* opEqEqual(long double lhs) const {
    //const Literal* node = new FloatLiteral(lhs == val);
    int equalFlag = 0;
    if (std::abs(lhs - val) < 1e-6) {
      equalFlag=1;
    }
    const Literal* node = new FloatLiteral(equalFlag);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opEqEqual(int lhs) const {
    //const Literal* node = new FloatLiteral(lhs == val);
    //PoolOfNodes::getInstance.add(node);
    return opEqEqual((long double)lhs);
  }
  virtual const Literal* opEqEqual(std::string lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opEqEqual(std::vector<Node*> lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }

  virtual const Literal* operator>=(const Literal& rhs) const {
    return rhs.opGreaterEqual(val);
  }
  virtual const Literal* opGreaterEqual(long double lhs) const {
    const Literal* node = new FloatLiteral(lhs >= val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGreaterEqual(int lhs) const {
    const Literal* node = new FloatLiteral(lhs>=val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGreaterEqual(std::string lhs) const {  //string always greater than numbers
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opGreaterEqual(std::vector<Node*> lhs) const {  //list always greater than numbers
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }

  virtual const Literal* operator<=(const Literal& rhs) const {
    return rhs.opLessEqual(val);
  }
  virtual const Literal* opLessEqual(long double lhs) const {
    const Literal* node = new FloatLiteral(lhs <= val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLessEqual(int lhs) const {
    const Literal* node = new FloatLiteral(lhs<=val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLessEqual(std::string lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opLessEqual(std::vector<Node*> lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }

  virtual const Literal* operator!=(const Literal& rhs) const {
    return rhs.opNotEqual(val);
  }
  virtual const Literal* opNotEqual(long double lhs) const {
    const Literal* node = new FloatLiteral(lhs > val || lhs < val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opNotEqual(int lhs) const {
    const Literal* node = new FloatLiteral(lhs > val || lhs < val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opNotEqual(std::string lhs) const {
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opNotEqual(std::vector<Node*> lhs) const {
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }

  long double getValue() const {return val;}
  virtual const Literal* eval() const { return this; }
  virtual void print() const {
    //std::cout << "FLOAT: " << val << std::endl;
    if (std::abs(std::floor(val)-val) < 1e-6 && val < 1e+16) {
      std::cout << val << ".0" <<std::endl;
    }
    else {
      std::cout << std::setprecision(12) << val << std::endl;
    }
  }
private:
  //float val;
  long double val;
};

class StringLiteral : public Literal{
public:
  StringLiteral(const std::string str) : val(str) { }

  virtual const Literal* operator+(const Literal& rhs) const {
    return rhs.opPlus(val);
  }
  virtual const Literal* opPlus(std::string lhs) const {
    const Literal* node = new StringLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPlus(long double) const {
    throw std::string("TypeError: cannot concatenate 'str' and 'float' objects");
    return NULL;
  }
  virtual const Literal* opPlus(int) const {
    throw std::string("TypeError: cannot concatenate 'str' and 'int' objects");
    return NULL;
  }
  virtual const Literal* opPlus(std::vector<Node*>) const {
    throw std::string("TypeError: cannot concatenate 'str' and 'list' objects");
    return NULL;
  }

  virtual const Literal* operator*(const Literal& rhs) const {
    return rhs.opMult(val);
  }
  virtual const Literal* opMult(long double) const {
    throw std::string("TypeError: can't multiply sequence by non-int of type 'float'");
    return NULL;
  }
  virtual const Literal* opMult(int lhs) const {
    std::string temp = "";
    for (int i = 0; i < lhs; i++){
      temp += val;
    }
    const Literal* node =new StringLiteral(temp);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(std::string lhs) const {
    throw std::string("TypeError: can't multiply sequence by non-int of type 'str'");
    return NULL;
  }
  virtual const Literal* opMult(std::vector<Node*>) const {
    throw std::string("TypeError: unsupported operand type(s) for -: 'str' and 'list'");
    return NULL;
  }

  virtual const Literal* operator-(const Literal& rhs) const {
    return NULL;
  }
  virtual const Literal* opSubt(long double) const {
    throw std::string("TypeError: unsupported operand type(s) for -: 'float' and 'str'");
    return NULL;
  }
  virtual const Literal* opSubt(int) const {
    throw std::string("TypeError: unsupported operand type(s) for -: 'int' and 'str'");
    return NULL;
  }

  virtual const Literal* operator/(const Literal& rhs) const {
    return NULL;
  }
  virtual const Literal* opDiv(long double) const {
    throw std::string("TypeError: unsupported operand type(s) for /: 'float' and 'str'");
    return NULL;
  }
  virtual const Literal* opDiv(int) const {
    throw std::string("TypeError: unsupported operand type(s) for /: 'int' and 'str'");
    return NULL;
  }

  virtual const Literal* operator%(const Literal& rhs) const {
    return NULL;
  }
  virtual const Literal* opMod(long double) const {
    throw std::string("TypeError: unsupported operand type(s) for mode: 'float' and 'str'");
    return NULL;
  }
  virtual const Literal* opMod(int) const {
    throw std::string("TypeError: unsupported operand type(s) for mode: 'int' and 'str'");
    return NULL;
  }

  virtual const Literal* floorDivide(const Literal& rhs) const {
    return NULL;
  }
  virtual const Literal* opFlrDiv(long double) const {
    throw std::string("TypeError: unsupported operand type(s) for //: 'float' and 'str'");
    return NULL;
  }
  virtual const Literal* opFlrDiv(int) const {
    throw std::string("TypeError: unsupported operand type(s) for //: 'int' and 'str'");
    return NULL;
  }

  virtual const Literal* pow(const Literal& rhs) const {
      return NULL;
  }
  virtual const Literal* opPow(long double) const {
    throw std::string("TypeError: unsupported operand type(s) for ** or pow(): 'float' and 'str'");
    return NULL;
  }
  virtual const Literal* opPow(int) const {
    throw std::string("TypeError: unsupported operand type(s) for ** or pow(): 'int' and 'str'");
    return NULL; }

  virtual const Literal* operator<<(const Literal& rhs) const {
    return NULL;
  }
  virtual const Literal* opLshift(long double) const {
    throw std::string("TypeError: unsupported operand type(s) for <<: 'float' and 'str'");
    return NULL;
  }
  virtual const Literal* opLshift(int) const {
    throw std::string("TypeError: unsupported operand type(s) for <<: 'int' and 'str'");
    return NULL; }

  virtual const Literal* operator>>(const Literal& rhs) const {
    return NULL;
  }
  virtual const Literal* opRshift(long double) const {
    throw std::string("TypeError: unsupported operand type(s) for >>: 'float' and 'str'");
    return NULL;
  }
  virtual const Literal* opRshift(int) const {
    throw std::string("TypeError: unsupported operand type(s) for >>: 'int' and 'str'");
    return NULL;
  }

  virtual const Literal* operator[](const Literal& rhs) const {
    return rhs.opIndex(val);
  }
  virtual const Literal* opIndex(long double) const {
    throw std::string("SyntaxError: invalid syntax");
    return NULL;
  }
  virtual const Literal* opIndex(int) const {
    throw std::string("SyntaxError: invalid syntax");
    return NULL;
  }
  virtual const Literal* opIndex(std::string) const {
    throw std::string("SyntaxError: invalid syntax");
    return NULL;
  }
  virtual const Literal* opIndex(std::vector<Node*>) const {
    throw std::string("TypeError: string indices must be integers, not tuple");
    return NULL; }

  virtual const Literal* operator<(const Literal& rhs) const {
    return rhs.opLess(val);
  }
  virtual const Literal* opLess(long double lhs) const {
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opLess(int lhs) const {
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opLess(std::string lhs) const {
    const Literal* node = new FloatLiteral(lhs < val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLess(std::vector<Node*> lhs) const { //string always greater than list
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }

  virtual const Literal* operator>(const Literal& rhs) const {
    return rhs.opGreater(val);
  }
  virtual const Literal* opGreater(long double lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opGreater(int lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opGreater(std::string lhs) const {
    const Literal* node = new FloatLiteral(lhs > val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGreater(std::vector<Node*> lhs) const { //string always greater than list
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }

  virtual const Literal* operator==(const Literal& rhs) const {
    return rhs.opEqEqual(val);
  }
  virtual const Literal* opEqEqual(long double lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opEqEqual(int lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opEqEqual(std::string lhs) const {
    const Literal* node = new FloatLiteral(lhs == val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opEqEqual(std::vector<Node*> lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }

  virtual const Literal* operator>=(const Literal& rhs) const {
    return rhs.opGreaterEqual(val);
  }
  virtual const Literal* opGreaterEqual(long double lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opGreaterEqual(int lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opGreaterEqual(std::string lhs) const {
    const Literal* node = new FloatLiteral(lhs >= val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGreaterEqual(std::vector<Node*> lhs) const { //string always greater than list
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }

  virtual const Literal* operator<=(const Literal& rhs) const {
    return rhs.opLessEqual(val);
  }
  virtual const Literal* opLessEqual(long double lhs) const {
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opLessEqual(int lhs) const {
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opLessEqual(std::string lhs) const {
    const Literal* node = new FloatLiteral(lhs <= val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLessEqual(std::vector<Node*> lhs) const { //string always greater than list
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }

  virtual const Literal* operator!=(const Literal& rhs) const {
    return rhs.opNotEqual(val);
  }
  virtual const Literal* opNotEqual(long double lhs) const {
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opNotEqual(int lhs) const {
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opNotEqual(std::string lhs) const {
    const Literal* node = new FloatLiteral(lhs != val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opNotEqual(std::vector<Node*> lhs) const { //string always greater than list
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }


  const Literal* slice(const Literal* start, const Literal* end, const Literal* step) const;

  std::string getValue() const {
    return val;
  }
  virtual const Literal* eval() const {
    return this;
  }
  virtual void print() const {
  //  std::cout<< "<str>" << val << std::endl;
      std::cout<< val << std::endl;
  }

private:
  std::string val;
};

class ListLiteral : public Literal {
public:
  ListLiteral(const std::vector<Node*> vec) : list(vec) { }

  virtual const Literal* operator+(const Literal& rhs) const {
    return rhs.opPlus(list);
  }
  virtual const Literal* opPlus(std::string lhs) const {
    throw std::string("TypeError: cannot concatenate 'str' and 'list' objects");
    return NULL; }
  virtual const Literal* opPlus(long double) const {
    throw std::string("TypeError: unsupported operand type(s) for +: 'float' and 'list'");
    return NULL; }
  virtual const Literal* opPlus(int) const {
    throw std::string("TypeError: unsupported operand type(s) for +: 'int' and 'list'");
    return NULL; }
  virtual const Literal* opPlus(std::vector<Node*> lhs) const {
    for (Node* n : list) {
      lhs.push_back(n);
    }
    const Literal* node = new ListLiteral(lhs);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator*(const Literal& rhs) const {
    return rhs.opMult(list);
  }
  virtual const Literal* opMult(long double) const {
    throw std::string("TypeError: can't multiply sequence by non-int of type 'float'");
    return NULL; }
  virtual const Literal* opMult(int lhs) const {
    std::vector<Node*>* temp = new std::vector<Node*>();
    for (int i = 0; i < lhs; i++) {
      for (Node* n : list) {
        temp->push_back(n);
      }
    }
    const Literal* node = new ListLiteral(*temp);
    PoolOfNodes::getInstance().add(node);
    delete temp;
    return node;
  }

  virtual const Literal* opMult(std::string lhs) const {
    throw std::string("TypeError: can't multiply sequence by non-int of type 'list'");
    return NULL; }
  virtual const Literal* opMult(std::vector<Node*>) const {
    throw std::string("TypeError: can't multiply sequence by non-int of type 'list'");
    return NULL;
  }

  virtual const Literal* operator-(const Literal& rhs) const { return NULL; }
  virtual const Literal* opSubt(long double) const {
    throw std::string("TypeError: unsupported operand type(s) for -: 'float' and 'list'");
    return NULL; }
  virtual const Literal* opSubt(int) const {
    throw std::string("TypeError: unsupported operand type(s) for -: 'int' and 'list'");
    return NULL; }

  virtual const Literal* operator/(const Literal& rhs) const { return NULL; }
  virtual const Literal* opDiv(long double) const {
    throw std::string("TypeError: unsupported operand type(s) for /: 'float' and 'list''");
    return NULL; }
  virtual const Literal* opDiv(int) const {
    throw std::string("TypeError: unsupported operand type(s) for /: 'int' and 'list'");
    return NULL; }

  virtual const Literal* operator%(const Literal& rhs) const { return NULL; }
  virtual const Literal* opMod(long double) const {
    throw std::string("TypeError: unsupported operand type(s) for %: 'float' and 'list'");
    return NULL; }
  virtual const Literal* opMod(int) const {
    throw std::string("TypeError: unsupported operand type(s) for %: 'int' and 'list'");
    return NULL; }

  virtual const Literal* floorDivide(const Literal& rhs) const { return NULL; }
  virtual const Literal* opFlrDiv(long double) const {
    throw std::string("TypeError: unsupported operand type(s) for //: 'float' and 'list'");
    return NULL; }
  virtual const Literal* opFlrDiv(int) const {
    throw std::string("TypeError: unsupported operand type(s) for //: 'int' and 'list'");
    return NULL; }

  virtual const Literal* pow(const Literal& rhs) const { return NULL; }
  virtual const Literal* opPow(long double) const {
    throw std::string("unsupported operand type(s) for ** or pow(): 'float' and 'list'");
    return NULL; }
  virtual const Literal* opPow(int) const {
    throw std::string("unsupported operand type(s) for ** or pow(): 'int' and 'list'");
    return NULL; }

  virtual const Literal* operator<<(const Literal& rhs) const { return NULL; }
  virtual const Literal* opLshift(long double) const {
    throw std::string("TypeError: unsupported operand type(s) for <<: 'float' and 'list'");
    return NULL; }
  virtual const Literal* opLshift(int) const {
    throw std::string("TypeError: unsupported operand type(s) for <<: 'int' and 'list'");
    return NULL; }

  virtual const Literal* operator>>(const Literal& rhs) const { return NULL; }
  virtual const Literal* opRshift(long double) const {
    throw std::string("TypeError: unsupported operand type(s) for >>: 'float' and 'list'");
    return NULL; }
  virtual const Literal* opRshift(int) const {
    throw std::string("TypeError: unsupported operand type(s) for >>: 'int' and 'list'");
    return NULL; }

  virtual const Literal* operator[](const Literal& rhs) const {
    return rhs.opIndex(list);
  }
  virtual const Literal* opIndex(long double) const {
    throw std::string("TypeError: 'float' object has no attribute '__getitem__'");
    return NULL; }
  virtual const Literal* opIndex(int) const {
    throw std::string("TypeError: 'int' object has no attribute '__getitem__'");
    return NULL; }
  virtual const Literal* opIndex(std::string) const {
    throw std::string("TypeError: string indices must be integers, not list");
    return NULL; }
  virtual const Literal* opIndex(std::vector<Node*>) const {
    throw std::string("TypeError: list indices must be integers, not list");
    return NULL; }

  virtual const Literal* operator<(const Literal& rhs) const {
    return rhs.opLess(list);
  }
  virtual const Literal* opLess(long double lhs) const {
    const Literal* trueNode =  new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opLess(int lhs) const {
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opLess(std::string lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opLess(std::vector<Node*> lhs) const;
  //{
  //  const Literal* node = new FloatLiteral(lsh < val);
    //PoolOfNodes::getInstance().add(node);
    //return node;
  //   return NULL;
  // }

  virtual const Literal* operator>(const Literal& rhs) const {
    return rhs.opGreater(list);
  }
  virtual const Literal* opGreater(long double lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opGreater(int lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opGreater(std::string lhs) const {
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const  Literal* opGreater(std::vector<Node*> lhs) const;
  // {
  //   return NULL;
  // }

  virtual const Literal* operator==(const Literal& rhs) const {
    return rhs.opEqEqual(list);
  }
  virtual const Literal* opEqEqual(long double lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opEqEqual(int lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opEqEqual(std::string lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opEqEqual(std::vector<Node*> lhs) const;
  // {
  //   return NULL;
  // }

  virtual const Literal* operator>=(const Literal& rhs) const {
    return rhs.opGreaterEqual(list);
  }
  virtual const Literal* opGreaterEqual(long double lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opGreaterEqual(int lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opGreaterEqual(std::string lhs) const {
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const  Literal* opGreaterEqual(std::vector<Node*> lhs) const;
  // {
  //   return NULL;
  // }

  virtual const Literal* operator<=(const Literal& rhs) const {
    return rhs.opLessEqual(list);
  }
  virtual const Literal* opLessEqual(long double lhs) const {
    const Literal* trueNode =  new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opLessEqual(int lhs) const {
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opLessEqual(std::string lhs) const {
    const Literal* falseNode = new FloatLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const  Literal* opLessEqual(std::vector<Node*> lhs) const; 
  // {
  //   return NULL;
  // }

  virtual const Literal* operator!=(const Literal& rhs)  const {
    return rhs.opNotEqual(list);
  }
  virtual const Literal* opNotEqual(long double lhs) const {
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opNotEqual(int lhs) const {
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opNotEqual(std::string lhs) const {
    const Literal* trueNode = new FloatLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opNotEqual(std::vector<Node*> lhs) const;
  //  {
  //   return NULL;
  // }

  const Literal* slice(const Literal* start, const Literal* end, const Literal* step) const;

  const std::vector<Node*> getValue() const { return list;}
  const std::string getValueString() const;
  virtual const Literal* eval() const { return this;}
  virtual void print() const {
    std::cout << getValueString() << std::endl;
  }

private:
  std::vector<Node*> list;
};

class IntLiteral: public Literal {
public:
 IntLiteral(int _val): val(_val) {}

  virtual const Literal* operator+(const Literal& rhs) const  {
    return rhs.opPlus(val);
  }
  virtual const Literal* opPlus(long double lhs) const  {
    const Literal* node = new FloatLiteral(static_cast<long double>(val) + lhs);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPlus(int lhs) const  {
    const Literal* node = new IntLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPlus(std::string) const {
    throw std::string("TypeError: cannot concatenate 'str' and 'int' objects");
    //std::cout <<"TypeError: cannot concatenate 'str' and 'int' objects"<<std::endl;
    return NULL;
  }
  virtual const Literal* opPlus(std::vector<Node*>) const {
    throw std::string("TypeError: can only concatenate list (not \"int\") to list");
    return NULL;
  }

  virtual const Literal* operator-(const Literal& rhs) const  {
    return rhs.opSubt(val);
  }
  virtual const Literal* opSubt(long double lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opSubt(int lhs) const  {
    const Literal* node = new IntLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator*(const Literal& rhs) const  {
    return rhs.opMult(val);
  }
  virtual const Literal* opMult(long double lhs) const  {
    const Literal* node = new FloatLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(int lhs) const  {
    const Literal* node = new IntLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(std::string lhs) const {
    std::string temp="";
    for (int i = 0; i < val; i ++) {
    temp += lhs;
  }
  const Literal* node = new StringLiteral(temp);
  PoolOfNodes::getInstance().add(node);
  return node;
  }
  virtual const Literal* opMult(std::vector<Node*> lhs) const {
    std::vector<Node*>* temp = new std::vector<Node*>();
    for (int i = 0; i < val; i++) {
      for (Node* n : lhs) {
        temp->push_back(n);
      }
    }
    const Literal* node = new ListLiteral(*temp);
    PoolOfNodes::getInstance().add(node);
    delete temp;
    return node;
  }

  virtual const Literal* operator/(const Literal& rhs) const  {
    return rhs.opDiv(val);
  }
  virtual const Literal* opDiv(long double lhs) const  {
    if ( val == 0 ) throw std::string("ZeroDivisionError: float division by zero");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opDiv(int lhs) const  {
    if ( val == 0 ) throw std::string("ZeroDivisionError: integer division or modulo by zero");
    //const Literal* node = new IntLiteral(lhs / val);
    int res = lhs / val;
    if (lhs * val < 0) {
      if (lhs % val != 0) {
        res--;
      }
    }
    const Literal* node = new IntLiteral(res);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator%(const Literal& rhs) const {
    return rhs.opMod(val);
  }
  virtual const Literal* opMod(long double lhs) const {
    if (val == 0) throw std::string("ZeroDivisionError: float modulo");
    const Literal* node = new FloatLiteral(std::fmod(std::fmod(lhs, val)+ val, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMod(int lhs) const {
    if (val == 0) throw std::string("ZeroDivisionError: integer division or modulo by zero");
    const Literal* node = new IntLiteral((lhs%val + val) % val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* floorDivide(const Literal& rhs) const {
    return rhs.opFlrDiv(val);
  }
  virtual const Literal* opFlrDiv(long double lhs) const {
    if (val == 0) throw std::string("ZeroDivisionError: float divmod()");
    const Literal* node = new FloatLiteral(std::floor(lhs / val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opFlrDiv(int lhs) const {
    return opDiv(lhs);
  }

  virtual const Literal* pow(const Literal& rhs) const {
    return rhs.opPow(val);
  }
  virtual const Literal* opPow(long double lhs) const {
    const Literal* node = new FloatLiteral(std::pow(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPow(int lhs) const {
    const Literal* node = new IntLiteral(std::pow(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator<<(const Literal& rhs) const {
    return rhs.opLshift(val);
  }
  virtual const Literal* opLshift(long double lhs) const {
    std::cout << "TypeError: unsupported operand type(s) for <<: 'float' and 'int'" << std::endl;
    return NULL;
  }
  virtual const Literal* opLshift(int lhs) const {
    const Literal* node = new IntLiteral(lhs * std::pow(2, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator>>(const Literal& rhs) const {
    return rhs.opRshift(val);
  }
  virtual const Literal* opRshift(long double lhs) const {
    std::cout << "TypeError: unsupported operand type(s) for <<: 'float' and 'int'" << std::endl;
    return NULL;
  }
  virtual const Literal* opRshift(int lhs) const {
    const Literal* node = new IntLiteral(lhs / std::pow(2, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator[](const Literal& rhs) const {
    return rhs.opIndex(val);
  }
  virtual const Literal* opIndex(long double) const {
    throw std::string("TypeError: 'float' object has no attribute '__getitem__'");
    return NULL;
  }
  virtual const Literal* opIndex(int) const {
    throw std::string("TypeError: 'int' object has no attribute '__getitem__'");
    return NULL;
  }
  virtual const Literal* opIndex(std::string lhs) const {
    //const Literal* node = new StringLiteral(lhs.substr(val, 1));
    const Literal* node;
    if (val < 0 ) {
      if (abs(val)>(int)lhs.size()){
        throw std::string("IndexError: string index out of range");
      }
      int index = lhs.size() + val;
      node = new StringLiteral(lhs.substr(index, 1));
    }
    else {
      if (val>=(int)lhs.size()){
        throw std::string("IndexError: string index out of range");
      }
      node = new StringLiteral(lhs.substr(val, 1));
    }
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opIndex(std::vector<Node*> lhs) const {
    if (val < 0) {
      if (abs(val)>(int)lhs.size()){
        throw std::string("IndexError: list index out of range");
      }
      int index = lhs.size() + val;
      return static_cast<const Literal*>(lhs[index]->eval());
    }
    else {
      if (val>=(int)lhs.size()){
        throw std::string("IndexError: list index out of range");
      }
    return static_cast<const Literal*>(lhs[val]->eval());
    }
  }

  virtual const Literal* operator<(const Literal& rhs) const {
    return rhs.opLess(val);
  }
  virtual const Literal* opLess(long double lhs) const {
    const Literal* node = new IntLiteral(lhs<val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLess(int lhs) const {
    const Literal* node = new IntLiteral(lhs<val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLess(std::string lhs) const {
    const Literal* falseNode = new IntLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opLess(std::vector<Node*> lhs) const {
    const Literal* falseNode = new IntLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }

  virtual const Literal* operator>(const Literal& rhs) const {
    return rhs.opGreater(val);
  }
  virtual const Literal* opGreater(long double lhs) const {
    const Literal* node = new IntLiteral(lhs>val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGreater(int lhs) const {
    const Literal* node = new IntLiteral(lhs>val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGreater(std::string lhs) const {
    const Literal* trueNode = new IntLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opGreater(std::vector<Node*> lhs) const {
    const Literal* trueNode = new IntLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* operator==(const Literal& rhs) const {
    return rhs.opEqEqual(val);
  }
  virtual const Literal* opEqEqual(long double lhs) const {
    int equalFlag = 0;
    if (std::abs(lhs - val) < 1e-6) {
      equalFlag = 1;
    }
    const Literal* node = new IntLiteral(equalFlag);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opEqEqual(int lhs) const {
    const Literal* node = new IntLiteral(lhs == val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opEqEqual(std::string lhs) const {
    const Literal* falseNode = new IntLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opEqEqual(std::vector<Node*> lhs) const {
    const Literal* falseNode = new IntLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }


  virtual const Literal* operator<=(const Literal& rhs) const {
    return rhs.opLessEqual(val);
  }
  virtual const Literal* opLessEqual(long double lhs) const {
    const Literal* node = new IntLiteral(lhs<=val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLessEqual(int lhs) const {
    const Literal* node = new IntLiteral(lhs<=val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLessEqual(std::string lhs) const {
    const Literal* falseNode = new IntLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }
  virtual const Literal* opLessEqual(std::vector<Node*> lhs) const {
    const Literal* falseNode = new IntLiteral(0);
    PoolOfNodes::getInstance().add(falseNode);
    return falseNode;
  }

  virtual const Literal* operator>=(const Literal& rhs) const {
    return rhs.opGreaterEqual(val);
  }
  virtual const Literal* opGreaterEqual(long double lhs) const {
    const Literal* node = new IntLiteral(lhs>=val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGreaterEqual(int lhs) const {
    const Literal* node = new IntLiteral(lhs>=val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGreaterEqual(std::string lhs) const {
    const Literal* trueNode = new IntLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opGreaterEqual(std::vector<Node*> lhs) const {
    const Literal* trueNode = new IntLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }

  virtual const Literal* operator!=(const Literal& rhs) const {
    return rhs.opNotEqual(val);
  }
  virtual const Literal* opNotEqual(long double lhs) const {
    const Literal* node  = new IntLiteral(lhs>val || lhs<val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opNotEqual(int lhs) const {
    const Literal* node = new IntLiteral(lhs != val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opNotEqual(std::string lhs) const {
    const Literal* trueNode = new IntLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }
  virtual const Literal* opNotEqual(std::vector<Node*>) const {
    const Literal* trueNode = new IntLiteral(1);
    PoolOfNodes::getInstance().add(trueNode);
    return trueNode;
  }



  int getValue() const{ return val; }
   const Literal* eval() const { return this; }
  virtual void print() const {
    //std::cout << "INT: " << val << std::endl;
    std::cout << val << std::endl;
  }
private:
  int val;
};
