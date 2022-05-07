#include <bits/stdc++.h>
using namespace std;

void query(vector<int>& nodes) {
  printf("? %d", nodes.size());
  for (int node : nodes) printf(" %d", node + 1);
  printf("\n"); fflush(stdout);
}

void getNodes(int node, int parent, int level, int desire, vector<vector<int>>& adj, vector<int>& nodes) {
  if (level == desire) {
    nodes.push_back(node);
    return;
  }
  for (int next : adj[node]) if (next != parent) getNodes(next, node, level + 1, desire, adj, nodes);
}

int getDepth(int node, int parent, vector<vector<int>>& adj) {
  int level = 0;
  for (int next : adj[node]) if (next != parent) level = max(level, getDepth(next, node, adj) + 1);
  return level;
}

void solve() {
  int n; cin >> n;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a; --b;
    adj[a].push_back(b); adj[b].push_back(a);
  }
  vector<int> all(n); for (int i = 0; i < n; ++i) all[i] = i;
  query(all);
  int root, dist; scanf("%d", &root); scanf("%d", &dist);
  --root;
  int lo = dist / 2 - 1, hi = min(getDepth(root, -1, adj), dist) + 1, wn = root;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    vector<int> nodes; getNodes(root, -1, 0, mid, adj, nodes);
    query(nodes);
    int tn, td; scanf("%d", &tn); scanf("%d", &td);
    --tn;
    if (td == dist) lo = mid, wn = tn;
    else hi = mid;
  }
  root = wn;
  vector<int> nodes; getNodes(root, -1, 0, dist, adj, nodes);
  query(nodes);
  int second; scanf("%d", &second); scanf("%d", &dist);
  printf("! %d %d\n", root + 1, second); fflush(stdout);
  string verdict; cin >> verdict;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
