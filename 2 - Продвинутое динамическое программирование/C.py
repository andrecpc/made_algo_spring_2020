from collections import defaultdict

n = int(input())
tree = []
dp = []

for _ in range(n):
    tree.append(int(input()) - 1)

for _ in range(n):
    dp.append([0, 1])

childs_mapping = defaultdict(list)

for id, parent_id in enumerate(tree):
    if parent_id == -1:
        root_id = id
    else:
        childs_mapping[parent_id].append(id)

nodes_stack = [(root_id, 0)]

while nodes_stack:
    node, status = nodes_stack.pop()
    if status == 1:
        for child_node in childs_mapping[node]:
            dp[node][0] += max(dp[child_node])
            dp[node][1] += dp[child_node][0]
    elif node in childs_mapping:
        nodes_stack.append((node, 1))
        for child_node in childs_mapping[node]:
            nodes_stack.append((child_node, 0))

print(max(dp[root_id]))
