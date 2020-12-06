k, _ = map(int, input().split())

d = {}

for _ in range(k):
    s = input()
    d[s[3:]] = s[0]

s = input()
S = ''
while s:
    for i in range(1, len(s)+1):
        if s[:i] in d.keys():
            S += d[s[:i]]
            s = s[i:]
            break

print(S)
