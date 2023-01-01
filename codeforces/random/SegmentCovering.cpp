#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

const int MOD = 998244353;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, q; cin >> n >> q;
  vector<pii> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i].first >> arr[i].second;
  sort(arr.begin(), arr.end(), [](const pii& lhs, const pii& rhs) {
    if (lhs.second != rhs.second) return lhs.second < rhs.second;
    return lhs.first > rhs.first;
  });
  vector<pii> na; na.push_back(arr[0]);
  for (int i = 1; i < n; ++i) {
    if (arr[i].first <= na.back().first) continue;
    na.push_back(arr[i]);
  }
  arr = na, n = na.size();
  set<int> ss, es;
  map<int, int> ps, bps;
  for (int i = 0; i < n; ++i)
    ss.insert(arr[i].first), es.insert(arr[i].second),
    ps[arr[i].first] = arr[i].second, bps[arr[i].second] = arr[i].first;
  vector<int> ss2; for (int num : ss) ss2.push_back(num);
  map<int, int> furthest;
  for (int i = n - 1; i >= 0; --i) {
    auto nxt = --ss.upper_bound(arr[i].second);
    if (*nxt == arr[i].first) furthest[arr[i].first] = arr[i].second;
    else furthest[arr[i].first] = furthest[*nxt];
  }
  vector<vector<int>> up(n + 1, vector<int>(30, n));
  for (int i = 0; i < n; ++i) {
    auto nxt = ss.upper_bound(arr[i].second);
    if (nxt == ss.end()) up[i][0] = n;
    else up[i][0] = lower_bound(ss2.begin(), ss2.end(), *nxt) - ss2.begin();
  }
  for (int i = 1; i < 30; ++i) for (int j = 0; j < n; ++j) up[j][i] = up[up[j][i - 1]][i - 1];
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b;
    if (furthest[a] < b || ps[a] > b || !es.count(b)) cout << 0 << '\n';
    else if (ps[a] == b) cout << MOD - 1 << '\n';
    else {
      int top = lower_bound(ss2.begin(), ss2.end(), bps[b]) - ss2.begin();
      int bot = lower_bound(ss2.begin(), ss2.end(), a) - ss2.begin();
      int c1 = 0, c2 = 0, at = bot, at2 = bot + 1;
      for (int j = 29; j >= 0; --j) if (up[at][j] <= top) c1 += (1 << j), at = up[at][j];
      for (int j = 29; j >= 0; --j) if (up[at2][j] <= top) c2 += (1 << j), at2 = up[at2][j];
      if (at == at2 || (at != top && at2 != top)) cout << 0 << '\n';
      else cout << (((c1 + c2) & 1) ? MOD - 1 : 1) << '\n';
    }
  }
  return 0;
}
