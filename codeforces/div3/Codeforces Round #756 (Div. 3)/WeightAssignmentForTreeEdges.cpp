#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> ps(n); for (int i = 0; i < n; ++i) cin >> ps[i];
  vector<int> perm(n); for (int i = 0; i < n; ++i) cin >> perm[i];
  // Makes everything zero-based:
  for (int i = 0; i < n; ++i) { --ps[i]; --perm[i]; }
  // Finds the tree's root:
  int root = 0;
  for (int i = 0; i < n; ++i) if (ps[i] == i) root = i;
  if (perm[0] != root) {
    // Output:
    cout << -1 << endl;
    return;
  }
  // Assigns distances to each node:
  vector<int> dists(n);
  int desired = 1;
  for (int i : perm) {
    if (i == root) continue;
    // Outputs if the parent has not been assigned a distance yet (which makes it impossible):
    if (dists[ps[i]] == 0 && ps[i] != root) {
      cout << -1 << endl;
      return;
    }
    dists[i] = desired++;
  }
  // Output:
  for (int i = 0; i < n; ++i) cout << dists[i] - dists[ps[i]] << ' ';
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
