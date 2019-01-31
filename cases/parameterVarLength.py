def multiply(*args):
    z = 1
    for num in args:
        z *= num
    print z

multiply(4, 5)
multiply(10, 9)

def some_args(arg_1, arg_2, arg_3):
    print arg_1
    print arg_2
    print arg_3

my_list = [2, 3]
some_args(1, *my_list)
