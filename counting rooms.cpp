#include <iostream>
#include <vector>

using namespace std;

int r, c;
vector<vector<char>> graph;
vector<vector<bool>> visited;

void dfs(int row, int col) {
    if (row < 0 || row >= r || col < 0 || col >= c || visited[row][col] || graph[row][col] == '#') {
        return;
    }
    visited[row][col] = true;

    dfs(row + 1, col);
    dfs(row - 1, col);
    dfs(row, col + 1);
    dfs(row, col - 1);
}

int main() {
    cin >> r >> c;
    graph.resize(r, vector<char>(c));
    visited.resize(r, vector<bool>(c, false));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> graph[i][j];
        }
    }

    int count = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (graph[i][j] == '.' && !visited[i][j]) {
                dfs(i, j);
                count++;
            }
        }
    }

    cout << count << endl;
    return 0;
}