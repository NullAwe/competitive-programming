#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<int> t;
int n;

void modify(int p, int v) { for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1]; }

int query(int l, int r) {
  int ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans += t[l++];
    if (r & 1) ans += t[--r];
  }
  return ans;
}

int main() {
  cin >> n; t.resize(2 * n);
  int q; cin >> q;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<vector<pii>> qs(n);
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    qs[b].push_back({a, i});
  }
  map<int, int> last; for (int num : arr) last[num] = -1;
  vector<int> ans(q);
  for (int i = 0; i < n; ++i) {
    int num = arr[i];
    if (last[num] >= 0) modify(last[num], 0);
    modify(i, 1); last[num] = i;
    for (pii p : qs[i]) ans[p.second] = query(p.first, i + 1);
  }
  for (int num : ans) cout << num << '\n';
  return 0;
}
