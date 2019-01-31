a = ["Hello", [2.00, 4, 4 + 5], 2 * 4.9, "World" * 3]
print a
print a[1][2]
print a[1][::]

b = ["Hello", [2.00, 4, 4 + 5], [[2 * 4.9], [1, 2, 3] + [4, 5, 6]], "World" * 3]
print b
print b[1][0]
print b[2][1]
print b[2][0][0]
print b[2][::]
print b[2][0][::] 
