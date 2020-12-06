from math import *

fs = [
    lambda x : log(log(x,2),2),#0
    lambda x : sqrt(log(x,4)), #1
    lambda x : log(x,3),#2
    lambda x : log(x,2)**2,#3
    lambda x : sqrt(x),#4
    lambda x : x/log(x,5),#5
    lambda x : log(factorial(x),2), #6 #2
    lambda x : 3**log(x,2),#7
    lambda x : x**2,#8
    lambda x : 7**log(x,2),#9
    lambda x : log(x,2)**log(x,2),#10
    lambda x : x**log(x,2),#11
    lambda x : x**sqrt(x),#12
    lambda x : 2**x,#13
    lambda x : 4**x,#14
    lambda x : 2**(3*x),#15 #3
    lambda x : factorial(x), #16 #4
    #lambda x : 2**(2**x), #17 #5
    ]


x = 50

def ff(f, x):
    try:
        return f(x)
    except OverflowError :
        return "---------"

for i, f in enumerate(fs[:12]):
    print i, ff(f, 5e4)

x=5000

print fs[12](x)< fs[13](x)
print fs[13](x)< fs[15](x)
print fs[15](x)< fs[16](x)
