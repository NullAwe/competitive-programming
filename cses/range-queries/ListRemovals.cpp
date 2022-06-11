#include <bits/stdc++.h>
using namespace std;

vector<int> t;
int n;

void modify(int p, int v) {
  for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
}

int query(int l, int r) {
  int ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans += t[l++];
    if (r & 1) ans += t[--r];
  }
  return ans;
}

int main() {
  cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  t.resize(2 * n);
  for (int i = 0; i < n; ++i) modify(i, 1);
  for (int i = 0; i < n; ++i) {
    int ind; cin >> ind; --ind;
    int lo = 0, hi = n;
    while (lo < hi - 1) {
      int mid = (lo + hi) / 2;
      if (query(0, mid) <= ind) lo = mid;
      else hi = mid;
    }
    modify(lo, 0);
    cout << arr[lo] << ' ';
  }
  cout << '\n';
  return 0;
}
