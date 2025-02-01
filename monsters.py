from collections import deque

def bfs(grid, n, m):
    directions = {'D': (1, 0), 'U': (-1, 0), 'L': (0, -1), 'R': (0, 1)}
    M, P = deque(), deque()
    mt = [[-1] * m for _ in range(n)]
    pt = [[-1] * m for _ in range(n)]
    parent = {}
    player = None

    for i in range(n):
        for j in range(m):
            if grid[i][j] == 'M':
                M.append((i, j))
                mt[i][j] = 0
            elif grid[i][j] == 'A':
                P.append((i, j))
                pt[i][j] = 0
                player = (i, j)

    if player is None:
        return []

    if player[0] == 0 or player[1] == 0 or player[0] == n - 1 or player[1] == m - 1:
        return ['E']

    while M:
        x, y = M.popleft()
        for dx, dy in directions.values():
            nx, ny = x + dx, y + dy
            if 0 <= nx < n and 0 <= ny < m and grid[nx][ny] == '.' and mt[nx][ny] == -1:
                mt[nx][ny] = mt[x][y] + 1
                M.append((nx, ny))

    # BFS for player
    while P:
        x, y = P.popleft()
        if x == 0 or y == 0 or x == n - 1 or y == m - 1:
            path = []
            while (x, y) != player:
                x, y, move = parent[(x, y)]
                path.append(move)
            path.reverse()
            return path

        for move, (dx, dy) in directions.items():
            nx, ny = x + dx, y + dy
            if 0 <= nx < n and 0 <= ny < m and grid[nx][ny] == '.' and pt[nx][ny] == -1:
                if mt[nx][ny] == -1 or pt[x][y] + 1 < mt[nx][ny]:
                    pt[nx][ny] = pt[x][y] + 1
                    P.append((nx, ny))
                    parent[(nx, ny)] = (x, y, move)

    return []

def main():
    n, m = map(int, input().split())
    grid = [input().strip() for _ in range(n)]

    ans = bfs(grid, n, m)
    if ans:
        if len(ans) == 1 and ans[0] == 'E':
            print("YES\n0")
        else:
            print("YES")
            print(len(ans))
            print("".join(ans))
    else:
        print("NO")

main()
