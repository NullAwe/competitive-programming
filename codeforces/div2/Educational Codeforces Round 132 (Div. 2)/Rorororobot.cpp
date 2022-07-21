#include <bits/stdc++.h>
using namespace std;

vector<int> t;

void build(vector<int>& arr) {
  int n = arr.size(); t.resize(2 * n);
  for (int i = 0; i < n; ++i) t[i + n] = arr[i];
  for (int i = n - 1; i > 0; --i) t[i] = max(t[2 * i], t[2 * i + 1]);
}

int query(int n, int l, int r) {
  int ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = max(ans, t[l++]);
    if (r & 1) ans = max(ans, t[--r]);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  vector<int> arr(m); for (int i = 0; i < m; ++i) cin >> arr[i];
  build(arr);
  int q; cin >> q;
  for (int i = 0; i < q; ++i) {
    int x1, y1, x2, y2, k; cin >> x1 >> y1 >> x2 >> y2 >> k; --x1, --y1, --x2, --y2; x1 = n - 1 - x1, x2 = n - 1 - x2;
    if (n - query(m, min(y1, y2), max(y1, y2) + 1) <= x1 % k || abs(y2 - y1) % k || abs(x2 - x1) % k) cout << "NO\n";
    else cout << "YES\n";
  }
  return 0;
}
