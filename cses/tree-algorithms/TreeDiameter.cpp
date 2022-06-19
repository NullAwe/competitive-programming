#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<vector<int>> adj;

pii dfs(int v, int p) {
  pii ans = {v, 0};
  for (int u : adj[v]) {
    if (u == p) continue;
    pii next = dfs(u, v);
    if (next.second >= ans.second) ans.first = next.first, ans.second = next.second + 1;
  }
  return ans;
}

int main() {
  int n; cin >> n;
  adj = vector<vector<int>>(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  int node = dfs(0, 0).first;
  cout << dfs(node, node).second << '\n';
  return 0;
}

