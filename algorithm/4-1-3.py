
def main():
    n = int(input())
    l = []
    for i in range(1, n+1):
        if n < i:
            l[-1] += n
            break
        else:
            l.append(i)
            n -= i
    print(len(l))
    for a in l:
        print(a, end=' ')
    

if __name__ == "__main__":
    main()


