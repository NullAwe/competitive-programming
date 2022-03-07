#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<vector<int>> adj;
vector<int> leaf, up, down;

int init(int node) {
  if (!adj[node].size()) return 0;
  leaf[node] = INT_MAX;
  for (int next : adj[node]) leaf[node] = min(leaf[node], init(next) + 1);
  return leaf[node];
}

int solveUp(int node) {
  if (!leaf[node]) return up[node] = 1;
  for (int next : adj[node]) up[node] += solveUp(next);
  if (leaf[node] >= k) return up[node] = 0;
  return up[node];
}

int solveDown(int node) {
  if (!leaf[node]) return down[node] = 1;
  int sum = 0, gain = 0;
  for (int next : adj[node]) sum += up[next], gain = max(gain, solveDown(next) - up[next]);
  return down[node] = sum + gain;
}

int main() {
  cin >> n >> k;
  vector<int> parent(n); for (int i = 1; i < n; ++i) cin >> parent[i];
  adj = vector<vector<int>>(n);
  for (int i = 1; i < n; ++i) adj[parent[i] - 1].push_back(i);
  leaf = vector<int>(n), up = vector<int>(n), down = vector<int>(n);
  init(0);
  solveUp(0);
  cout << solveDown(0) << '\n';
  return 0;
}
