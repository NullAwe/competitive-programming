#include <bits/stdc++.h>
using namespace std;

vector<int> getZ(string s) {
  int n = s.length();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r) z[i] = min (r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}

int main() {
  int n, m, k; cin >> n >> m >> k;
  string s, t; cin >> s >> t;
  vector<int> z1 = getZ(t + "#" + s);
  z1 = vector<int>(z1.begin() + m + 1, z1.end());
  if (m <= k) {
    for (int i = 0; i < n; ++i) {
      if (z1[i] == m) {
        i = min(i, n - k);
        cout << "Yes\n";
        if (i >= k) cout << 1 << ' ' << i + 1 << '\n';
        else cout << i + 1 << ' ' << n - k + 1 << '\n';
        return 0;
      }
    }
  }
  reverse(s.begin(), s.end()), reverse(t.begin(), t.end());
  vector<int> z2 = getZ(t + "#" + s);
  z2 = vector<int>(z2.begin() + m + 1, z2.end());
  reverse(z2.begin(), z2.end()), reverse(s.begin(), s.end()), reverse(t.begin(), t.end());
  set<int> df, dl; for (int i = 0; i <= m; ++i) df.insert(i), dl.insert(i);
  vector<int> first(m + 1, INT_MAX), last(m + 1, -1);
  for (int i = 0; i < n; ++i) {
    while (df.size()) {
      auto it = df.upper_bound(z1[i]);
      if (it == df.begin()) break;
      int len = *--it;
      if (i - (k - len) < 0) break;
      first[len] = i;
      df.erase(len);
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    while (dl.size()) {
      auto it = dl.upper_bound(z2[i]);
      if (it == dl.begin()) break;
      int len = *--it;
      if (i + (k - len) >= n) break;
      last[len] = i;
      dl.erase(len);
    }
  }
  for (int i = max(m - k, 0); i <= min(m, k); ++i) {
    int f = first[i], l = last[m - i];
    if (f == INT_MAX || l < 0 || l - f + 1 < m) continue;
    cout << "Yes\n" << f - k + i + 1 << ' ' << l - m + i + 2 << '\n';
    return 0;
  }
  cout << "No\n";
  return 0;
}

