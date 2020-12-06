
def toDict(d, t, prefix = ''):
    _, c, t0, t1 = t
    if c != '':
        d[c] = prefix if prefix !='' else '0'
    else:
        toDict(d, t0, prefix + '0')
        toDict(d, t1, prefix + '1')

# (f, char, Tree0, Tree1)
s = input()

d = {}

for c in s:
    d.setdefault(c, 0)
    d[c] += 1

l = [(f, k, None, None) for k, f in d.items()]
l.sort()

K = len(l)

while len(l)>1:
    a, b = l[0:2]
    c = (a[0]+b[0], '', a, b)
    l = l[2:]
    l.append(c)
    l.sort()

t = l[0]

d = {}
toDict(d, t)

S = "".join([d[c] for c in s])
print(K, len(S))
for char, code in d.items():
    print(char+": "+code)

print(S)

