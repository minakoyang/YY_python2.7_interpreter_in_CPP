def f(x):
    print x
    x += 4
    print x
    y = x * 6
    y += 5
    print y

f(34)


def foo(val1, val2, val3):
    return val1 + val2 + val3

print foo(1, 2, 3)


# Function definition is here
def printme( str ):
   "This prints a passed string into this function"
   print str
   return;

# Now you can call printme function
printme("I'm first call to user defined function!")
printme("Again second call to the same function")


def changeme( mylist ):
   "This changes a passed list into this function"
   mylist = [1,2,3,4]; # This would assig new reference in mylist
   print mylist
   return

# Now you can call changeme function
mylist = [10,20,30];
changeme( mylist );
print mylist
