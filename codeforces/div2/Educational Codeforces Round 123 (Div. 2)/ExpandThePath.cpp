#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  ll n; cin >> n;
  string str; cin >> str;
  ll x = 1, y = 1;
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] == 'R') ++y;
    else ++x;
  }
  ll lx = n - x, ly = n - y, ans = 1;
  bool r = false, d = false;
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] == 'R') r = true;
    else d = true;
    if (i == str.size() - 1) {
      if (r && d) ans += (lx + 1) * (ly + 1);
      else if (r) ans += ly + 1;
      else if (d) ans += lx + 1;
    } else {
      if (str[i + 1] == 'R') {
        if (d) ans += lx + 1;
        else ++ans;
      } else {
        if (r) ans += ly + 1;
        else ++ans;
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
