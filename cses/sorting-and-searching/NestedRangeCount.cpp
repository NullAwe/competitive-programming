#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

void inc(vector<int>& t, int n, int p) {
  for (++t[p += n]; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
}

int query(vector<int>& t, int n, int l, int r) {
  int ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans += t[l++];
    if (r & 1) ans += t[--r];
  }
  return ans;
}

int main() {
  int n; cin >> n;
  vector<pii> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i].second >> arr[i].first;
  for (int i = 0; i < n; ++i) arr[i].second = 1000000001 - arr[i].second;
  set<int> has; for (int i = 0; i < n; ++i) has.insert(arr[i].second);
  int id = 0;
  map<int, int> comp; for (int num : has) comp[num] = ++id;
  for (int i = 0; i < n; ++i) arr[i].second = comp[arr[i].second];
  map<pii, int> m; for (int i = 0; i < n; ++i) m[arr[i]] = i;
  vector<pii> ans(n);
  sort(arr.begin(), arr.end());
  vector<int> l(2 * n + 2);
  for (pii p : arr) {
    ans[m[p]].first = query(l, n + 1, 0, p.second + 1);
    inc(l, n + 1, p.second);
  }
  reverse(arr.begin(), arr.end());
  l = vector<int>(4 * n + 2);
  for (pii p : arr) {
    ans[m[p]].second = query(l, n + 1, p.second, n + 1);
    inc(l, n + 1, p.second);
  }
  for (int i = 0; i < n; ++i) cout << ans[i].first << ' ';
  cout << '\n';
  for (int i = 0; i < n; ++i) cout << ans[i].second << ' ';
  cout << '\n';
  return 0;
}
