import sys

kor=1000001

numbs = [60, 456,232,11,678]

lp = [0]*(kor+1)
primes=[]
for i in range (2,kor+1):
    if (lp[i] == 0):
        lp[i] = i
        primes.append(i)
    for p in primes:
        if ((p > lp[i]) | (i * p >= kor+1)):
            break
        lp[i * p] = p
'''
for num in numbs:
    while (num > 1):
        sys.stdout.write(str(lp[num]) + ' ')
        num = int(num/lp[num])
    sys.stdout.write('\n')
'''

n = int(sys.stdin.readline().strip())

for _ in range(n):
    num = int(sys.stdin.readline().strip())
    while (num > 1):
        sys.stdout.write(str(lp[num]) + ' ')
        num = int(num/lp[num])
    sys.stdout.write('\n')
