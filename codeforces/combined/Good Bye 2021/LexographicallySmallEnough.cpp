#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <utility>
#include <climits>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define ll long long

const int MOD = 1000000007;

void modify(vector<int>& t, int n, int p, int value) {
  for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
}

int query(vector<int>& t, int n, int l, int r) {
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) res += t[l++];
    if (r & 1) res += t[--r];
  }
  return res;
}

void solve() {
  int n; cin >> n;
  string a, b; cin >> a >> b;
  string copy = a;
  sort(copy.begin(), copy.end());
  if (copy >= b) {
    cout << -1 << endl;
    return;
  }
  vector<vector<int>> m(26);
  for (int i = 0; i < 26; ++i) m[i].push_back(1);
  for (int i = 0; i < n; ++i) m[a[i] - 'a'].push_back(i);
  set<int> taken; for (int i = 0; i < n; ++i) taken.insert(i);
  vector<int> t(2 * n);
  ll ans = LLONG_MAX, swaps = 0;
  for (int i = 0; i < n; ++i) {
    int ai = *taken.begin();
    if (a[ai] < b[i]) {
      ans = min(ans, swaps);
      cout << ans << endl;
      return;
    }
    int key = b[i] - 'a', lm = INT_MAX, ind;
    for (int j = key - 1; j >= 0; --j) {
      if (m[j][0] >= m[j].size()) continue;
      ind = m[j][m[j][0]]; ind += query(t, n, ind, n);
      lm = min(lm, abs(ind - i));
    }
    if (lm < INT_MAX) ans = min(ans, swaps + lm);
    if (m[key][0] >= m[key].size()) break;
    ind = m[key][m[key][0]++];
    taken.erase(ind);
    modify(t, n, ind, 1);
    ind += query(t, n, ind, n) - 1;
    swaps += abs(ind - i);
  }
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
