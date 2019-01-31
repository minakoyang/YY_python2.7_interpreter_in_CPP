if ( [1] == [1] ):
   print "Line 1 - a is equal to b"
else:
   print "Line 1 - a is not equal to b"

if ( [1] != [1.0] ):
   print "Line 2 - a is not equal to b"
else:
   print "Line 2 - a is equal to b"

if ( [1.0] <> [1] ):
   print "Line 3 - a is not equal to b"
else:
   print "Line 3 - a is equal to b"

if ( [1] < [2.0] ):
   print "Line 4 - a is less than b"
else:
   print "Line 4 - a is not less than b"

if ( [1] > [1, 1] ):
   print "Line 5 - a is greater than b"
else:
   print "Line 5 - a is not greater than b"

if ( [11.0] <= [1, 1] ):
   print "Line 6 - a is either less than or equal to  b"
else:
   print "Line 6 - a is neither less than nor equal to  b"

if ( [1, 1, 2] >= [1, 1.0, 3.0] ):
   print "Line 7 - a is either greater than  or equal to b"
else:
   print "Line 7 - a is neither greater than  nor equal to b"


if ( ["1"] == [1] ):
   print "Line 1 - a is equal to b"
else:
   print "Line 1 - a is not equal to b"

if ( [[1]] != [1.0] ):
   print "Line 2 - a is not equal to b"
else:
   print "Line 2 - a is equal to b"

if ( [1.0] <> "1" ):
   print "Line 3 - a is not equal to b"
else:
   print "Line 3 - a is equal to b"

if ( [[1]] < 2.0 ):
   print "Line 4 - a is less than b"
else:
   print "Line 4 - a is not less than b"

if ( "1" > ["1", 1] ):
   print "Line 5 - a is greater than b"
else:
   print "Line 5 - a is not greater than b"

if ( [11.0] <= [[1], 1] ):
   print "Line 6 - a is either less than or equal to  b"
else:
   print "Line 6 - a is neither less than nor equal to  b"

if ( [1, [1, 3]] >= [1, 1.0, 3.0] ):
   print "Line 7 - a is either greater than  or equal to b"
else:
   print "Line 7 - a is neither greater than  nor equal to b"
