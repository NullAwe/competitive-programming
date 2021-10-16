#include <bits/stdc++.h>
using namespace std;

vector<int> m, m2;
vector<vector<int>> adj;
vector<map<int, int>> store;

void dfs(int node, int parent, int lvl) {
  m2[node] = store[node][lvl] = 1;
  for (int next : adj[node]) {
    if (next == parent) continue;
    dfs(next, node, lvl + 1);
    // Ensures small-to-large merging for O(n log n) time complexity:
    if (store[next].size() > store[node].size()) {
      m[node] = m[next] + 1; m2[node] = m2[next];
      swap(store[node], store[next]);
    }
    for (auto& s : store[next]) {
      store[node][s.first] += s.second;
      if (store[node][s.first] > m2[node]) {
        m2[node] = store[node][s.first];
        m[node] = s.first - lvl;
      } else if (store[node][s.first] == m2[node] && m[node] > s.first - lvl) m[node] = s.first - lvl;
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  m = vector<int>(n); m2 = vector<int>(n);
  adj = vector<vector<int>>(n);
  store = vector<map<int, int>>(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b;
    --a; --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  // Finds answer by DFSing on the tree:
  dfs(0, -1, 0);
  // Output:
  for (int i = 0; i < n; ++i) cout << m[i] << endl;
  return 0;
}
