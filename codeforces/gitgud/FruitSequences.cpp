#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n; cin >> n;
  string str; cin >> str;
  vector<int> ones(n); ones[0] = str[0] == '1';
  for (int i = 1; i < n; ++i) ones[i] = str[i] == '0' ? 0 : ones[i - 1] + 1;
  vector<pair<int, int>> starts;
  starts.push_back({-1, 1000000});
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    if (ones[i] > 1) starts.resize(starts.size() - 1);
    if (ones[i]) {
      if (starts.size() > 1) {
        --starts[starts.size() - 1].first, --starts[starts.size() - 1].second;
        if (starts[starts.size() - 1].second == 0) starts.resize(starts.size() - 1);
      }
      starts.push_back({i, ones[i]});
    }
    int cur = 0;
    for (int i = starts.size() - 1; i > 0; --i) {
      int num = starts[i].second;
      ans += (ll) num * (2 * cur + num + 1) / 2;
      cur += num;
      ans += (ll) cur * (starts[i].first - starts[i - 1].first - num);
    }
  }
  cout << ans << '\n';
  return 0;
}
