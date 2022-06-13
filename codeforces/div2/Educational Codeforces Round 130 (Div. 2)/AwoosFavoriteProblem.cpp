#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  string s, t; cin >> s >> t;
  vector<int> count(3);
  for (int i = 0; i < n; ++i) ++count[s[i] - 'a'], --count[t[i] - 'a'];
  if (count[0] || count[1] || count[2]) {
    cout << "NO\n";
    return;
  }
  vector<pair<char, int>> a, b;
  for (int i = 0; i < n; ++i) {
    if (s[i] != 'b') a.push_back({s[i], i});
    if (t[i] != 'b') b.push_back({t[i], i});
  }
  bool can = a.size() == b.size();
  for (int i = 0; i < a.size() && can; ++i) {
    if (a[i].first != b[i].first ||
        (a[i].first == 'a' && a[i].second > b[i].second) ||
        (a[i].first == 'c' && a[i].second < b[i].second)) can = false;
  }
  cout << (can ? "YES\n" : "NO\n");
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}