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
  vector<int> ids(n); int id = 0;
  for (int i = n - 1; i >= 0; --i) {
    if (vis[order[i]]) continue;
    getComp(order[i]);
    ++id;
    for (int num : comp) ids[num] = id;
    comp.clear();
  }
  cout << id << '\n';
  for (int num : ids) cout << num << ' ';
  cout << '\n';
  return 0;
}

