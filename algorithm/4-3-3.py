
class Heap:
    def __init__(self, n):
        self.h=[0]*n
        self.l=0

    def ExtractMax(self):
        res = self.h[1]
        self.h[1] = self.h[self.l]
        self.l -= 1
        self.shiftDown(1)
        return res

    def shiftDown(self, i):
        i2 = 2*i
        if i2 > self.l:
            return
        if i2 < self.l and self.h[i2] <  self.h[i2+1]:
            i2+=1

        if self.h[i] < self.h[i2]:
            self.h[i], self.h[i2] = self.h[i2], self.h[i]
        self.shiftDown(i2)


    def shiftUp(self, i):
        i2 =  i // 2
        if i2 == 0:
            return

        if self.h[i] > self.h[i2]:
            self.h[i], self.h[i2] = self.h[i2], self.h[i]
        else:
            return
        self.shiftUp(i2)

    def insert(self, v):
        self.l +=1
        self.h[self.l] = v
        self.shiftUp(self.l)

n = int(input())
heap = Heap(n)

for _ in range(n):
    c = input()
    if c =="ExtractMax":
        print(heap.ExtractMax())
    else:
        heap.insert(int(c[7:]))

