

A = list(map(int, input().split()))
n = A[0]

K = map(int, input().split()[1:])


def binsearch(k, A, l, r):
    while l <= r:
        m = l + (r-l)//2
        if A[m] == k:
            return m
        else:
            if A[m] > k:
                r = m-1
            else:
                l = m+1
    return -1

for k in K:
    print(binsearch(k, A, 1, n), end=" ")

