#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj, rev;
vector<bool> vis;
vector<int> order, comp;

void topo(int v) {
  if (vis[v]) return;
  vis[v] = true;
  for (int u : adj[v]) topo(u);
  order.push_back(v);
}

void gc(int v) {
  if (vis[v]) return;
  vis[v] = true;
  comp.push_back(v);
  for (int u : rev[v]) gc(u);
}

int main() {
  int n, m; cin >> n >> m;
  adj = vector<vector<int>>(2 * m), rev = vector<vector<int>>(2 * m);
  for (int i = 0; i < n; ++i) {
    char ia, ib; int a, b;
    cin >> ia >> a >> ib >> b; --a, --b;
    bool inca = ia - '-', incb = ib - '-';
    adj[(!inca) * m + a].push_back(incb * m + b);
    rev[incb * m + b].push_back((!inca) * m + a);
    adj[(!incb) * m + b].push_back(inca * m + a);
    rev[inca * m + a].push_back((!incb) * m + b);
  }
  vis = vector<bool>(2 * m);
  for (int i = 0; i < 2 * m; ++i) topo(i);
  vis = vector<bool>(2 * m);
  reverse(order.begin(), order.end());
  vector<int> no;
  for (int v : order) {
    gc(v);
    set<int> s;
    for (int num : comp) s.insert(num >= m ? num - m : num);
    if (s.size() != comp.size()) {
      cout << "IMPOSSIBLE\n";
      return 0;
    }
	for (int num : comp) no.push_back(num);
    comp.clear();
  }
  set<int> s;
  vector<bool> have(m);
  for (int v : no) {
    int raw = v - (v >= m) * m;
    if (s.count(raw)) continue;
    s.insert(raw);
    have[raw] = !(v - raw);
  }
  for (bool b : have) cout << (b ? '+' : '-') << ' ';
  cout << '\n';
  return 0;
}
