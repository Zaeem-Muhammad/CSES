from collections import deque


def bfs(start, end, graph, r, c):
    directions = [(0, -1, 'L'), (0, 1, 'R'), (1, 0, 'D'), (-1, 0, 'U')]
    visited = [[False] * c for _ in range(r)]
    parent = [[None] * c for _ in range(r)]

    q = deque([start])
    visited[start[0]][start[1]] = True

    while q:
        x, y = q.popleft()

        if (x, y) == end:
            path = []
            while (x, y) != start:
                px, py, d = parent[x][y]
                path.append(d)
                x, y = px, py
            return path[::-1]

        for dx, dy, d in directions:
            nx, ny = x + dx, y + dy

            if 0 <= nx < r and 0 <= ny < c and not visited[nx][ny] and graph[nx][ny] != '#':
                q.append((nx, ny))
                visited[nx][ny] = True
                parent[nx][ny] = (x, y, d)

    return []


def main():
    r, c = map(int, input().split())
    graph = [list(input().strip()) for _ in range(r)]

    for i in range(r):
        for j in range(c):
            if graph[i][j] == 'A':
                start = (i, j)
            elif graph[i][j] == 'B':
                end = (i, j)

    ans = bfs(start, end, graph, r, c)

    if not ans:
        print("NO")
    else:
        print("YES")
        print(len(ans))
        print("".join(ans))


main()
