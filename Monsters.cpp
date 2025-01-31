#include <bits/stdc++.h>
using namespace std;

struct Node {
    int x, y;
    char move;
};

vector<char> bfs(vector<string>& grid, int n, int m) {
    map<char, pair<int, int>> directions = {{'D', {1, 0}}, {'U', {-1, 0}}, {'L', {0, -1}}, {'R', {0, 1}}};
    queue<pair<int, int>> M, P;
    vector<vector<int>> mt(n, vector<int>(m, -1)), pt(n, vector<int>(m, -1));
    map<pair<int, int>, Node> parent;
    pair<int, int> player;
    bool foundPlayer = false;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'M') {
                M.push({i, j});
                mt[i][j] = 0;
            } else if (grid[i][j] == 'A') {
                P.push({i, j});
                pt[i][j] = 0;
                player = {i, j};
                foundPlayer = true;
            }
        }
    }

    if (!foundPlayer) {
        return {};
    }

    if (player.first == 0 || player.second == 0 || player.first == n - 1 || player.second == m - 1) {
        return {'E'};  //
    }

    while (!M.empty()) {
        auto [x, y] = M.front(); M.pop();
        for (auto [_, dir] : directions) {
            int nx = x + dir.first, ny = y + dir.second;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '.' && mt[nx][ny] == -1) {
                mt[nx][ny] = mt[x][y] + 1;
                M.push({nx, ny});
            }
        }
    }

    while (!P.empty()) {
        auto [x, y] = P.front(); P.pop();
        if (x == 0 || y == 0 || x == n - 1 || y == m - 1) {
            vector<char> path;
            while (make_pair(x, y) != player) {
                auto [xp, yp, mo] = parent[{x, y}];
                path.push_back(mo);
                x = xp; y = yp;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (auto [move, dir] : directions) {
            int nx = x + dir.first, ny = y + dir.second;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '.' && pt[nx][ny] == -1) {
                if (mt[nx][ny] == -1 || pt[x][y] + 1 < mt[nx][ny]) {
                    pt[nx][ny] = pt[x][y] + 1;
                    P.push({nx, ny});
                    parent[{nx, ny}] = {x, y, move};
                }
            }
        }
    }
    return {};
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];

    vector<char> ans = bfs(grid, n, m);
    if (!ans.empty()) {
        if (ans.size() == 1 && ans[0] == 'E') {
            cout << "YES\n0\n";
        } else {
            cout << "YES\n" << ans.size() << "\n";
            for (char c : ans) cout << c;
            cout << "\n";
        }
    } else {
        cout << "NO\n";
    }
    return 0;
}
