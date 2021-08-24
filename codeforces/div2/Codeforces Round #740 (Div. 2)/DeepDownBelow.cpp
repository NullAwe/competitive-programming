#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<pair<ll, ll>> caves(n);
  for (int i = 0; i < n; ++i) {
    int k; cin >> k;
    // Finds the minimum level on entrance to a cave to beat the cave:
    int lvl = 0;
    for (int j = 0; j < k; ++j) {
      int c; cin >> c;
      lvl = max(lvl, c - j + 1);
    }
    caves[i] = {lvl, k};
  }
  sort(caves.begin(), caves.end());
  // Finds the minimum level on start of the game to beat the game:
  ll lvl = 0, add = 0;
  for (pair<ll, ll> p : caves) {
    lvl = max(lvl, p.first - add);
    add += p.second;
  }
  // Output:
  cout << lvl << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
