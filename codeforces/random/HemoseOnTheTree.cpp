#include <bits/stdc++.h>
using namespace std;

int n, val;
vector<vector<int>> adj;
map<pair<int, int>, int> m;
vector<int> nodes;
vector<int> edges;

void dfs(int v, int p) {
  int ev = val, nv = val + (1 << n);
  if (nodes[p] >= (1 << n)) swap(ev, nv);
  edges[m[{v, p}]] = ev, nodes[v] = nv;
  ++val;
  for (int next : adj[v]) if (next != p) dfs(next, v);
}

void solve() {
  cin >> n;
  adj = vector<vector<int>>(1 << n);
  nodes = vector<int>(1 << n);
  edges = vector<int>((1 << n) - 1);
  for (int i = 1; i < (1 << n); ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b), adj[b].push_back(a);
    m[{a, b}] = m[{b, a}] = i - 1;
  }
  cout << 1 << '\n';
  nodes[0] = (1 << n);
  val = 1;
  for (int next : adj[0]) dfs(next, 0);
  for (int node : nodes) cout << node << ' ';
  cout << '\n';
  for (int edge : edges) cout << edge << ' ';
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
