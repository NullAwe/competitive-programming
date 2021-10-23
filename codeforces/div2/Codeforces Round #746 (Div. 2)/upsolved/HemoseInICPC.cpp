#include <bits/stdc++.h>
using namespace std;

void tour(int node, int parent, vector<vector<int>>& adj, vector<int>& path) {
  path.push_back(node);
  for (int next : adj[node]) {
    if (next == parent) continue;
    tour(next, node, adj, path);
    path.push_back(node);
  }
}

int main() {
  int n; cin >> n;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b;
    adj[a - 1].push_back(b - 1);
    adj[b - 1].push_back(a - 1);
  }
  vector<int> path;
  tour(0, -1, adj, path);
  // Finds maximum:
  string q = "? " + to_string(n);
  for (int i = 1; i <= n; ++i) q += " " + to_string(i);
  q += "\n";
  printf("%s", q.c_str());
  fflush(stdout);
  int m; scanf("%d", &m);
  // Binary searches for the answer:
  int lo = 0, hi = path.size() - 1;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    set<int> nodes;
    for (int i = lo; i <= mid; ++i) nodes.insert(path[i] + 1);
    q = "? " + to_string(nodes.size());
    for (int node : nodes) q += " " + to_string(node);
    q += "\n";
    printf("%s", q.c_str());
    fflush(stdout);
    int res; scanf("%d", &res);
    if (res == m) hi = mid;
    else lo = mid;
  }
  // Output:
  cout << "! " << path[lo] + 1 << ' ' << path[hi] + 1 << endl;
  return 0;
}