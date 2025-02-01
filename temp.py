from collections import deque
from collections import defaultdict

def dfs(g, e):
    count = -1
    stack = [(e, 0)]
    visited = set()
    while stack:
        cur, level = stack.pop()
        if cur not in visited:
            visited.add(cur)
            count = max(count, level)
            for el in g[cur]:
                stack.append((el, level + 1))
    return count


t = int(input())
for _ in range(t):
    le = int(input())
    g = defaultdict(list)
    for e in range(le-1):
        n , m = map(int , input().split())
        g[n].append(m)
        g[m].append(n)
    ans = float('-inf')
    for e in g.keys():
        ans = max(ans , dfs(g , e))
    print(ans , end=" ")
    maxi = -1
    node = -1
    for e in g.items():
        if len(e[1]) > maxi:
            node = e[0]
            maxi = max(maxi , len(e[1]))
    print(g[node][-1] , g[node][0])
