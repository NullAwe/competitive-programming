#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<pii> adj;
vector<int> ans;

bool dfs(int v, int l) {
  if (adj[v].first < 0 && adj[v].second < 0) {
    if (l) return false;
    ans.push_back(v);
    return true;
  }
  if (adj[v].first >= 0) {
    int u = adj[v].first;
    adj[v].first = -1;
    if (dfs(u, l - 1)) {
      ans.push_back(v);
      return true;
    }
    adj[v].first = u;
  }
  if (adj[v].second >= 0) {
    int u = adj[v].second;
    adj[v].second = -1;
    if (dfs(u, l - 1)) {
      ans.push_back(v);
      return true;
    }
    adj[v].second = u;
  }
  return false;
}

int main() {
  int n; cin >> n; --n;
  if (!n) {
    cout << "01\n";
    return 0;
  }
  adj = vector<pii>(1 << n);
  for (int i = 0; i < (1 << n); ++i) adj[i] = {(i << 1) & ~(1 << n), ((i << 1) & ~(1 << n)) ^ 1};
  dfs(0, 1 << (n + 1));
  reverse(ans.begin(), ans.end());
  for (int i = 0; i < n - 1; ++i) cout << 0;
  for (int num : ans) cout << (num & 1);
  cout << '\n';
  return 0;
}

