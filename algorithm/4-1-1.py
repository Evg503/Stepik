# put your python code here
from operator import itemgetter
#input = raw_input

def main():
    n = int(input())
    l = [list(map(int, input().split())) for _ in range(n)]
    l.sort(key = itemgetter(1))
    p = []

    while len(l) > 0:
        a, b = l[0]
        p.append(b)
        while len(l) != 0 and l[0][0]<=b:
          l.pop(0)
          
           
    print (len(p))
    for a in p:
        print( a)


if __name__ == "__main__":
    main()


