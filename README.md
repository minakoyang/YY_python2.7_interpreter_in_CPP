# YY_python2.7_intepreter_in_CPP

Name: Yuzhe Yang

Course: CPSC8270

Clemson Email Address: yuzhey@g.clemson.edu

Project no: 6

Project due date: 12/12/2018

Project Description:

Design and implement an Abstract Syntax Tree (AST) to represent and interpret the Python code.

The program translates those constructs from the previous project, including integer and float values and variables, both string and list values and variables. It handles print, assignment, and the expressions specified in the previous project, including relational operators for int/float/string/list, if/elif/else statements, Python functions with Lexical Scope resolution, and for/while loop statements.

The new features for the program include actual parameters and formal parameters, recursion such as factorial and Fibonacci, and variable length argument lists (*args) used both as parameters and arguments.

1. Actual parameters and formal parameters
The ParamNode and ArgNode are defined to represent the parameters and arguments in functions. Specifically, The parameters are retrieved as vector of Node* and are stored in ParamNode. Similarly, the arguments are retrieved as vector of Node* and are stored in ArgNode. A new map. std::map<std::string, const Node*> paramTable, has been used to relate function name with parameters. In the CallNode, the parameters and arguments are compared to pass the arguments into functions. The static scope resolution for Python functions are maintained when parameters are passed into functions.

2. Recursion
When pushing scope for new functions, the functionTable is searched for existing function in table. If found, use it for the recursive call of functions. When returning that function inside itself, the program implements recursions. The program can solve factorials and Fibonacci problems with recursions.

3. variable length arguments (*args)
The VarParamNode and VarArgNode are defined to represent the variable length arguments (*args) in functions. When used as parameters, *args collects extra arguments into the list and process the list in the function body. When used as arguments, *args will be unpacked to match the parameters.

A sample test case for *args with for loop:
def multiply(*args):
    z = 1
    for num in args:
         z *= num
    print z

multiply(4, 5)
multiply(10, 9)

4. Tests
The test.py script processes all test cases in the cases folder, generating the .out files from python results and comparing them with MyPy results. All test cases in the cases folder passed the test.
Test cases for parameters and arguments: parameter.py
Test cases for recursion: recursion.py, factorial.py, fibonacci.py
Test cases for variable length arguments (*args): parameterVarLength.py

5. Memory Leak
The program has no memory leaks. For example, the following command "valgrind ./run cases/factorial.py" gives the result as below.
All heap blocks were freed -- no leaks are possible

6. Summary of Python translator project
	a) translates integer and float values and variables, both string and list values and variables.
	b) translates print, assignment, and the expressions, specifically string and list concatenation and multiplication, indexing and slicing
	c) relational operators for int/float/string/list
	d) if/elif/else statements
	e) for/while loop statements
	f) Python functions with Static Scope resolution
	g) Function parameters and arguments
	h) variable length arguments
	i) recursion
