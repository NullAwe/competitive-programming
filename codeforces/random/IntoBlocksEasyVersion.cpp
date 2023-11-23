#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

const int MAX_X = 200001;

int main() {
  int n, k; cin >> n >> k;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> first(MAX_X, -1), last(MAX_X, -1);
  for (int i = 0; i < n; ++i) {
    if (first[arr[i]] < 0) first[arr[i]] = i;
    last[arr[i]] = i;
  }
  set<pii> s;
  for (int i = 0; i < n; ++i) if (first[i] >= 0) s.insert({first[i], last[i]});
  set<pii> real;
  int ll = -1, lr = -1;
  for (pii p : s) {
    if (ll < 0) ll = p.first, lr = p.second;
    else if (p.first < lr) ll = min(ll, p.first), lr = max(lr, p.second);
    else {
      real.insert({ll, lr});
      ll = p.first, lr = p.second;
    }
  }
  if (ll >= 0) real.insert({ll, lr});
  int ans = 0;
  for (pii p : real) {
    map<int, int> m;
    set<int> cnt;
    for (int i = p.first; i <= p.second; ++i) ++m[arr[i]], cnt.insert(arr[i]);
    int mx = 0;
    for (int num : cnt) mx = max(mx, m[num]);
    ans += p.second - p.first + 1 - mx;
  }
  cout << ans << '\n';
  return 0;
}