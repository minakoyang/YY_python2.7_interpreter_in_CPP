def g():
  x = 0
  while x < 9:
    if x < 3:
      print x
    elif x < 5:
      print x+3
    else:
      print x+1
    x += 1
  else:
    print x*2


sum = 0
n = 1
while n <= 100:
    sum = sum + n
    n = n + 1
print sum

# Example to illustrate
# the use of else statement
# with the while loop

counter = 0

while counter < 3:
    print "Inside loop"
    counter = counter + 1
else:
    print "Inside else"

g() 
