#include <bits/stdc++.h>
using namespace std;

void modify(vector<int>& t, int n, int p, int v) {
  for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
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
  vector<pair<int, int>> arr(n);
  vector<int> keep(n);
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    arr[i].first = keep[i] = x;
    arr[i].second = n - i;
  }
  sort(arr.begin(), arr.end());
  int q; cin >> q;
  vector<pair<pair<int, int>, int>> queries(q);
  for (int i = 0; i < q; ++i) cin >> queries[i].first.first >> queries[i].first.second;
  for (int i = 0; i < q; ++i) queries[i].second = i;
  sort(queries.begin(), queries.end());
  int ind = 0;
  vector<int> t(2 * n), ans(q);
  for (int i = 1; i <= n; ++i) {
    modify(t, n, n - arr[n - i].second, 1);
    while (ind < q && queries[ind].first.first == i) {
      int index = queries[ind].first.second - 1;
      int lo = 0, hi = n + 1;
      while (lo < hi - 1) {
        int mid = (lo + hi) >> 1;
        int before = query(t, n, 0, mid);
        if (before <= index) lo = mid;
        else hi = mid;
      }
      ans[queries[ind++].second] = keep[lo];
    }
  }
  for (int num : ans) cout << num << '\n';
}
