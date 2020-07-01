 # coding: utf-8

with open("input.txt", "r") as file:
    n, k = map( int, file.readline().strip().split(' ') )
    costs = list( map( int, file.readline().strip().split(' ') ) )

values = [-100, 0] + costs + [0]
dp = [-100] + [0] * n
path = []

for i in range(2, n + 1):
    num_max = i - 1
    for j in range( max(1, i - k), i ):
        if dp[j] > dp[num_max]:
            num_max = j
    dp[i] = dp[num_max] + values[i]

    if num_max not in path:
        path.append(num_max)

if k == 1:
    path = list( range(1, n + 1) )
    s = n - 1

path = path + [n]
s = len(path) - 1

if k == 1:
    path = list( range(1, n + 1) )
    s = n - 1

if n == 2:
    path = [1, 2]
    s = 1

output_text = '\n'.join( [ str(dp[-1]), str(s), ' '.join(map(str, path)) ] )

with open("output.txt","w") as out:
    out.write(output_text)
