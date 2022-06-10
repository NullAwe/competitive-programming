#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m; cin >> n >> m;
  vector<set<int>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].insert(b);
    adj[b].insert(a);
  }
  vector<set<int>> copy = adj;
  stack<int> s; s.push(0);
  vector<int> ans;
  while (s.size()) {
    int v = s.top();
    if (!adj[v].size()) {
      ans.push_back(v);
      s.pop();
    } else {
      int u = *adj[v].begin();
      adj[v].erase(u), adj[u].erase(v);
      s.push(u);
    }
  }
  bool bad = ans.size() <= m || ans.front() || ans.back();
  for (int i = 1; i < ans.size(); ++i) bad |= !copy[ans[i - 1]].count(ans[i]);
  if (bad) cout << "IMPOSSIBLE";
  else for (int num : ans) cout << num + 1 << ' ';
  cout << '\n';
  return 0;
}
