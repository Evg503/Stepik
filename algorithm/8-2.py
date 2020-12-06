
def main():
    n = int(input())
    l = list(map(int, input().split()))

    d = [0]*n
    dm = 0

    for i in range(n):
        d[i] = 1 + max([0]+[d[j] for j in range(i) if l[i] % l[j] ==0 ])
        if d[i]>dm:
            dm = d[i]

    print(dm)


if __name__ == "__main__":
    main()
