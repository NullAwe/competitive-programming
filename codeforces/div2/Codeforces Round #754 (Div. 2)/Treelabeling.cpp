#include <bits/stdc++.h>
using namespace std;

void inflate(int n, int p, int l, vector<vector<int>>& adj, vector<vector<int>>& levels) {
  if (levels.size() <= l) {
    vector<int> newL;
    levels.push_back(newL);
  }
  levels[l].push_back(n);
  for (int next : adj[n]) {
    if (next == p) continue;
    inflate(next, n, l + 1, adj, levels);
  }
}

void solve() {
  int n; cin >> n;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b;
    adj[a - 1].push_back(b - 1);
    adj[b - 1].push_back(a - 1);
  }
  vector<vector<int>> levels;
  inflate(0, -1, 0, adj, levels);
  vector<int> perm(n);
  vector<int> sizes(levels.size());
  for (int i = 0; i < levels.size(); ++i) sizes[i] = levels[i].size();
  int two = 1;
  while (two * 2 <= n) two *= 2;
  // Processes by powers of two:
  for (int i = two; i >= 1; i /= 2) {
    int even = 0, odd = 0;
    for (int j = 0; j < sizes.size(); j += 2) even += sizes[j];
    for (int j = 1; j < sizes.size(); j += 2) odd += sizes[j];
    int m = (i * 2 > n ? n : i * 2 - 1);
    // Chooses the parity with the most space for each iteration:
    int ind = 0;
    if (odd > even) ind = 1;
    for (int j = i; j <= m; ++j) {
      while (sizes[ind] == 0) {
        ind += 2;
      }
      perm[levels[ind][levels[ind].size() - sizes[ind]]] = j;
      --sizes[ind];
    }
  }
  // Output:
  for (int num : perm) cout << num << ' ';
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
