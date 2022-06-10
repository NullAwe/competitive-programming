#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n; --n;
  if (!n) {
    cout << "01\n";
    return 0;
  }
  vector<vector<int>> adj(1 << n);
  for (int i = 0; i < (1 << n); ++i)
    adj[i].push_back((i << 1) & ~(1 << n)), adj[i].push_back(((i << 1) & ~(1 << n)) ^ 1);
  vector<set<int>> copy(n);
  for (int i = 0; i < n; ++i) for (int num : adj[i]) copy[i].insert(num);
  stack<int> s; s.push(0);
  vector<int> ans;
  while (s.size()) {
    int v = s.top();
    if (!adj[v].size()) {
      ans.push_back(v);
      s.pop();
    } else {
      int u = adj[v].back();
      adj[v].pop_back();
      s.push(u);
    }
  }
  reverse(ans.begin(), ans.end());
  for (int i = 0; i < n - 1; ++i) cout << 0;
  for (int num : ans) cout << (num & 1);
  cout << '\n';
  return 0;
}
