
import sys
import bisect

n, m = map(int, next(sys.stdin).split())
l = []
r = []
for i in range(n):
    a, b = map(int, next(sys.stdin).split())
    l.append(a)
    r.append(b)

l.sort()
r.sort()
ps = map(int, next(sys.stdin).split())

for p in ps:

    # ll = bisect.bisect_left(l, p)
    # rr = bisect.bisect_right(r, p)
    lr = bisect.bisect_left(r, p)
    rl = bisect.bisect_right(l, p)

    print( rl-lr, end=' ')


"""
------
2 3
0 5
7 10
1 6 11
------
1 0 0
------
6 6
0 3
1 3
2 3
3 4
3 5
3 6
1 2 3 4 5 6
------
2 3 6 3 2 1
------
10 5
-2 3
0 3
-1 0
-1 3
0 1
-2 -1
1 3
2 3
1 2
2 3
-3 -1 0 2 3
------
0 4 5 7 6
"""