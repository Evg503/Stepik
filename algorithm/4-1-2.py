
def main():
    n, W = map(int, input().split())
    l = [list(map(int, input().split())) for _ in range(n)]
    l.sort(key = lambda item: item[0]/item[1], reverse=True)
    C = 0
    
    while len(l) > 0 and W >= l[0][1]:
        c, w = l[0]
        C += c
        W -= w
        l.pop(0)


    if len(l) > 0 and W >= 0:
        c, w = l[0]
        C += W*(c/w) 

    print (C)

if __name__ == "__main__":
    main()


