#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj, rev;
vector<bool> vis;
vector<int> order, comp;

void findOrder(int v) {
  if (vis[v]) return;
  vis[v] = true;
  for (int u : adj[v]) findOrder(u);
  order.push_back(v);
}

void getComp(int v) {
  if (vis[v]) return;
  vis[v] = true;
  comp.push_back(v);
  for (int u : rev[v]) getComp(u);
}

int main() {
  int n, m; cin >> n >> m;
  adj = vector<vector<int>>(n), rev = vector<vector<int>>(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    rev[b].push_back(a);
  }
  vis = vector<bool>(n);
  for (int i = 0; i < n; ++i) findOrder(i);
  vis = vector<bool>(n);
  getComp(order.back());
  if (comp.size() == n) {
    cout << "YES\n";
    return 0;
  }
  cout << "NO\n";
  comp.push_back(-1);
  sort(comp.begin(), comp.end());
  for (int i = 1; i < comp.size(); ++i) {
    if (comp[i] != comp[i - 1] + 1) {
      cout << comp[i] << ' ' << comp[i] + 1 << '\n';
      return 0;
    }
  }
  cout << comp.back() + 2 << ' ' << comp.back() + 1 << '\n';
  return 0;
}
