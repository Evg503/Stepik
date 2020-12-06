

n = int(input())
A = list(map(int, input().split()))

def merge_sort(A, b, e):
    global inv

    if e-b > 1:
        s = b + (e - b) // 2
        merge_sort(A, b, s)
        merge_sort(A, s, e)
        tmp = []
        i1 = b
        i2 = s
        while i1<s or i2<e:
            if A[i2] < A[i1]:
                inv+=s-i1
                tmp.append(A[i2])
                i2+=1
            else:
                tmp.append(A[i1])
                i1+=1

            if i1==s:
                tmp.extend(A[i2:e])
                break

            if i2==e:
                tmp.extend(A[i1:s])
                break

        for i in range(b, e):
            A[i] = tmp[i-b]



inv = 0
merge_sort(A, 0, n)
print(inv)

