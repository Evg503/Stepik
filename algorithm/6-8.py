n = input()
l = map(int, input().split())
c = [0]*10

for i in l:
    c[i] += 1

for i in range(10):
    print((str(i)+" ")*c[i], end='')
