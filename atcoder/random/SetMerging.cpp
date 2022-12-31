#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

int n;
vector<int> t;

void upd(int p, int v) { for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]); }

int qry(int l, int r) {
  int ans = INT_MAX;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = min(ans, t[l++]);
    if (r & 1) ans = min(ans, t[--r]);
  }
  return ans;
}

vector<int> t2;

void upd2(int p, int v) { for (t2[p += n] = v; p > 1; p >>= 1) t2[p >> 1] = t2[p] + t2[p ^ 1]; }

int qry2(int l, int r) {
  int ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = ans + t2[l++];
    if (r & 1) ans = ans + t2[--r];
  }
  return ans;
}

int main() {
  cin >> n; t.resize(2 * n, INT_MAX);
  vector<pii> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i].first >> arr[i].second;
  vector<int> perm(n);
  set<int> un; for (int i = 1; i <= n; ++i) un.insert(i);
  for (int i = 0; i < n; ++i) {
    if (i == 0 || arr[i].second > arr[i - 1].second) {
      perm[i] = arr[i].second;
      un.erase(arr[i].second);
      upd(i, perm[i]);
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    if (i == n - 1 || arr[i].first < arr[i + 1].first) {
      if (perm[i] == arr[i].first) continue;
      if (perm[i] || !un.count(arr[i].first)) {
        cout << -1 << '\n';
        return 0;
      }
      perm[i] = arr[i].first;
      un.erase(arr[i].first);
      upd(i, perm[i]);
    }
  }
  int l = 0;
  int mx = 0;
  for (int i = 0; i < n; ++i) {
    if (perm[i]) {
      int r = i - 1;
      int mn = qry(r, n);
      for (int j = l; j <= r; ++j) {
        auto it = un.upper_bound(mn);
        if (it == un.end() || (*it) > mx) {
          cout << -1 << '\n';
          return 0;
        }
        un.erase(it);
        perm[j] = *it;
      }
      l = i + 1;
    }
    mx = max(mx, perm[i]);
  }
  if (un.size()) {
    cout << -1 << '\n';
    return 0;
  }
  t2.resize(2 * n);
  for (int i = 0; i < n; ++i) {
    upd(i, perm[i]);
    if (!perm[i]) {
      cout << -1 << '\n';
      return 0;
    }
  }
  mx = 0;
  for (int i = 0; i < n; ++i) {
    mx = max(mx, perm[i]);
    int mn = qry(i, n);
    if (mn != arr[i].first || mx != arr[i].second) {
      cout << -1 << '\n';
      return 0;
    }
  }
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    ans += qry2(perm[i], n);
    upd2(perm[i] - 1, 1);
  }
  cout << ans << '\n';
  return 0;
}