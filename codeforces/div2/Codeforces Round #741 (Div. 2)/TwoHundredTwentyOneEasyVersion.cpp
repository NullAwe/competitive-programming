#include <bits/stdc++.h>
using namespace std;

pair<int, int> pairMinus(pair<int, int> a, pair<int, int> b) {
  return {a.first - b.first, a.second - b.second};
}

void solve() {
  int n, q; cin >> n >> q;
  string str; cin >> str;
  // Stores prefix sums for "+" and "-" for alternating indices:
  vector<pair<int, int>> pref1(n + 1); // {+, -}
  vector<pair<int, int>> pref2(n + 1); // {+, -}
  pref1[0] = {0, 0};
  pref2[0] = {0, 0};
  for (int i = 1; i <= n; ++i) {
    pref1[i] = pref1[i - 1];
    pref2[i] = pref2[i - 1];
    if (i % 2 == 1) {
      if (str[i - 1] == '+') ++pref1[i].first;
      else ++pref1[i].second;
    } else {
      if (str[i - 1] == '+') ++pref2[i].first;
      else ++pref2[i].second;
    }
  }
  for (int i = 0; i < q; ++i) {
    int l, r; cin >> l >> r;
    pair<int, int> first = pairMinus(pref1[r], pref1[l - 1]);
    pair<int, int> second = pairMinus(pref2[r], pref2[l - 1]);
    // Output:
    if (first.first == second.first && first.second == second.second) cout << 0 << endl;
    else if ((r - l) % 2 == 0) cout << 1 << endl;
    else cout << 2 << endl;
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
