
def bisect(l, x, a, b):
    while a<b:
        m = (a+b) // 2
        print(a, m, b)
        if l[m] > x:
            if a == m:
                break
            a = m+1
        else:
            b = m
    return b

def simplemain():
    n = int(input())
    l = list(map(int, input().split()))

    d = [-1]*n
    prev = [-1]*n
    dmi = 0

    for i in range(n):
        for j in range(i):
            if l[j] >= l[i] and d[j]+1 > d[i]:
                d[i] = d[j]+1
                print(j,  bisect(d, d[i], 0, n))
                prev[i] = j
                if d[i]>d[dmi]:
                    dmi = i

    print(d[dmi])
    ans = [0]*d[dmi]
    j = d[dmi] - 1
    k = dmi
    while k >= 0:
        ans[j] = k
        j -= 1
        k = prev[k]
    for a in ans:
        print(a+1, end=' ')


def n2main():
    n = int(input())
    l = list(map(int, input().split()))

    d = [-1]*(n+1)
    d[0] = 10**10
    #prev = [-1]*n
    #dmi = 0

    for i in range(n):
        for j in reversed(range(n+1)):
            if d[j - 1] >= l[i] >= d[j]:
                k = bisect(d, l[i], 0, n+1)
                d[j] = l[i]
                print(j, k)
                break
        print(j, ":", d)

    print("ANSWER:", d)
'''
5
5 3 4 4 2
-----------
4
1 3 4 5
*************************************
10
5 3 4 4 2 5 3 4 4 2


'''
def main():
    n = int(input())
    l = list(map(int, input().split()))

    d = [10**10]*n
    d[0] = -10**10
    dm = 0


    for i in range(n):
        j = bisect(d, l[i], 0, n)
        print("j =", j)
        if d[j-1] > l[i] and l[i] > d[j]:
            d[j] = l[i]
        if dm < d[j]:
            dm = d[j]
    print(d)

    print(dm)


def test():
    assert 2 == bisect([5, 4, 3, 2, 1], 3, 0, 5)

    for i in range(6):
        print(bisect([5, 4, 3, 2, 1], i, 0, 5))
if __name__ == "__main__":
    n2main()
    #test()
