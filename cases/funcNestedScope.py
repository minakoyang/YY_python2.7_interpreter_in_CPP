x=5
def f():
 print x
def g():
 x=10
 print x
 return f()
g() 
