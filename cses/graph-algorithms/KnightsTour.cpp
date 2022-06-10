#include <bits/stdc++.h>
using namespace std;

const vector<int> dx = {-2, -2, -1, -1, 1, 1, 2, 2}, dy = {-1, 1, -2, 2, -2, 2, -1, 1};
const int N = 64;

vector<set<int>> adj(N);
vector<int> ans;

bool dfs(int v, int l) {
  if (!adj[v].size()) {
    if (l) return false;
    ans.push_back(v);
    return true;
  }
  vector<int> back;
  for (int i = 0; i < N; ++i) if (adj[i].count(v)) adj[i].erase(v), back.push_back(i);
  vector<int> next; for (int u : adj[v]) next.push_back(u);
  sort(next.begin(), next.end(), [](int a, int b) {
    return adj[a].size() < adj[b].size();
  });
  for (int u : next) {
    if (!dfs(u, l - 1)) continue;
    ans.push_back(v);
    return true;
  }
  for (int i : back) adj[i].insert(v);
  return false;
}

int main() {
  int a, b; cin >> a >> b;
  for (int i = 0; i < 8; ++i) for (int j = 0; j < 8; ++j) for (int dir = 0; dir < 8; ++dir)
    if (i + dx[dir] >= 0 && j + dy[dir] >= 0 && i + dx[dir] < 8 && j + dy[dir] < 8) adj[i * 8 + j].insert((i + dx[dir]) * 8 + j + dy[dir]);
  dfs((b - 1) * 8 + a - 1, 63);
  vector<vector<int>> board(8, vector<int>(8));
  for (int i = N - 1; i >= 0; --i) board[ans[i] / 8][ans[i] % 8] = N - i;
  for (vector<int> row : board) {
    for (int cell : row) cout << cell << ' ';
    cout << '\n';
  }
  return 0;
}
