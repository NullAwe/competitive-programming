#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
  vector<int> b(n); for (int i = 0; i < n; ++i) cin >> b[i];
  for (int i = 0; i < n; ++i) --a[i], --b[i];
  vector<int> ma(n); for (int i = 0; i < n; ++i) ma[a[i]] = i;
  vector<bool> been(n);
  vector<int> groups;
  for (int i = 0; i < n; ++i) {
    int size = 0, node = a[i];
    while (!been[node]) been[node] = true, ++size, node = b[ma[node]];
    groups.push_back((size >> 1) << 1);
  }
  sort(groups.begin(), groups.end());
  ll ans = 0, l = n;
  for (int size : groups) {
    ans += ((l - 1) + (l - size + 1)) * (size - 1) / 2 + l - size / 2;
    l -= size;
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
