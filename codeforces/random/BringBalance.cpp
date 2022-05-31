#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n; n <<= 1;
  string str; cin >> str;
  vector<int> p(n + 1); for (int i = 0; i < n; ++i) p[i + 1] = p[i] + (str[i] == '(' ? 1 : -1);
  int first = -1, last = -1;
  for (int i = 0; i <= n; ++i) {
    if (first < 0 && p[i] < 0) first = i;
    if (p[i] < 0) last = i;
  }
  if (first < 0) {
    cout << 0 << '\n';
    return;
  }
  int start = 0, end = n;
  for (int i = 0; i < first; ++i) if (p[i] > p[start]) start = i;
  for (int i = last + 1; i <= n; ++i) if (p[i] > p[end]) end = i;
  string temp = str; reverse(temp.begin() + start, temp.begin() + end);
  int h = 0, m = 0;
  for (int i = 0; i < n; ++i) h += temp[i] == '(' ? 1 : -1, m = min(m, h);
  if (m == 0) {
    cout << 1 << '\n';
    cout << start + 1 << ' ' << end << '\n';
    return;
  }
  int ind = 0; for (int i = 1; i <= n; ++i) if (p[i] > p[ind]) ind = i;
  cout << 2 << '\n';
  cout << 1 << ' ' << ind << '\n';
  cout << ind + 1 << ' ' << n << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
