#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int BF = 444;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string str; cin >> str;
  int n = str.size();
  vector<int> p(n + 1); for (int i = 0; i < n; ++i) p[i + 1] = p[i] + (str[i] - '0');
  ll ans = 0;
  vector<int> tracker(n * (BF + 1));
  for (int i = 1; i <= BF; ++i) {
    for (int j = 0; j <= n; ++j) ans += tracker[j - i * p[j] + n * BF - 1]++;
    for (int j = 0; j <= n; ++j) --tracker[j - i * p[j] + n * BF - 1];
  }
  vector<int> ones; for (int i = 0; i < n; ++i) if (str[i] - '0') ones.push_back(i);
  ones.push_back(n);
  for (int i = 1; i <= n / BF; ++i) {
    for (int j = 0; j < n; ++j) {
      int no = lower_bound(ones.begin(), ones.end(), j) - ones.begin();
      if (no + i >= ones.size()) break;
      int l = ones[no + i - 1], r = ones[no + i] - 1;
      int lv = l - j + 1, rv = r - j + 1;
      if (lv % i) lv = lv / i + 1;
      else lv = lv / i;
      rv = rv / i;
      lv = max(lv, BF + 1);
      if (rv >= lv) ans += rv - lv + 1;
    }
  }
  cout << ans << '\n';
  return 0;
}

