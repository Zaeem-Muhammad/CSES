#include <iostream>
#include <vector>
#include <queue>
#include <tuple> // Required for tie()
#include <algorithm>

using namespace std;

int r, c;
vector<string> graph;
pair<int, int> starting, ending;

// Directions and labels
vector<pair<int, int>> directions = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
vector<char> direction_labels = {'L', 'R', 'D', 'U'};

vector<vector<bool>> visited;
vector<vector<pair<int, int>>> parent;
vector<vector<char>> direction_taken;

vector<char> bfs(pair<int, int> s, pair<int, int> e) {
    queue<pair<int, int>> q;
    q.push(s);
    visited[s.first][s.second] = true;

    while (!q.empty()) {
        pair<int, int> current = q.front();  // Replaces structured binding
        int x = current.first, y = current.second;
        q.pop();

        if (current == e) {
            vector<char> path;
            while (current != s) {
                path.push_back(direction_taken[current.first][current.second]);
                current = parent[current.first][current.second]; // No need for tie()
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + directions[i].first;
            int ny = y + directions[i].second;

            if (nx >= 0 && nx < r && ny >= 0 && ny < c && !visited[nx][ny] && graph[nx][ny] != '#') {
                q.push({nx, ny});
                visited[nx][ny] = true;
                parent[nx][ny] = {x, y};
                direction_taken[nx][ny] = direction_labels[i];
            }
        }
    }
    return {};
}

int main() {
    cin >> r >> c;
    graph.resize(r);
    visited.assign(r, vector<bool>(c, false));
    parent.assign(r, vector<pair<int, int>>(c, {-1, -1}));
    direction_taken.assign(r, vector<char>(c, ' '));

    for (int i = 0; i < r; i++) {
        cin >> graph[i];
        for (int j = 0; j < c; j++) {
            if (graph[i][j] == 'A') {
                starting = {i, j};
            } else if (graph[i][j] == 'B') {
                ending = {i, j};
            }
        }
    }

    vector<char> ans = bfs(starting, ending);

    if (ans.empty()) {
        cout << "NO\n";
    } else {
        cout << "YES\n" << ans.size() << "\n";
        for (char d : ans) {
            cout << d;
        }
        cout << "\n";
    }

    return 0;
}
