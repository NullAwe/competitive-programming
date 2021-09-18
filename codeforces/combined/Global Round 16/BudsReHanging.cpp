#include <bits/stdc++.h>
using namespace std;

#define ll long long

int getNumLeaves(vector<vector<int>>& adj, int node, int parent) {
  int l = 0;
  bool did = false;
  for (int next : adj[node]) {
    if (next == parent) continue;
    did = true;
    l += getNumLeaves(adj, next, node);
  }
  if (!did) return 1;
  return l;
}

int getNumBuds(int node, vector<bool>& isLeaf, vector<bool>& canDo, vector<vector<int>>& adj, int parent) {
  if (isLeaf[node]) return 0;
  canDo[node] = false;
  int ans = 0;
  for (int next : adj[node]) {
    if (!canDo[next]) continue;
    if (!isLeaf[next]) ans += getNumBuds(next, isLeaf, canDo, adj, node);
  }
  bool isBud = true;
  int c = 0;
  for (int next : adj[node]) {
    if (!canDo[next]) continue;
    ++c;
  }
  if (c == 0) isBud = false;
  if (!isBud) {
    canDo[node] = true;
    --ans;
  } else ++ans;
  return ans;
}

void solve() {
  int n; cin >> n;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n; ++i) {
    vector<int> v;
    adj[i] = v;
  }
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b;
    --a; --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<bool> isLeaf(n, false);
  for (int i = 1; i < n; ++i) {
    if (adj[i].size() == 1) isLeaf[i] = true;
  }
  vector<bool> canDo(n, true);
  canDo[0] = false;
  int ans = 0;
  for (int num : adj[0]) ans += getNumLeaves(adj, num, 0);
  bool has = false;
  for (int num : adj[0]) {
    ans -= getNumBuds(num, isLeaf, canDo, adj, 0);
    if (canDo[num]) has = true;
  }
  if (!has) ++ans;
  // Output:
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}