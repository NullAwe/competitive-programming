#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define vvi vector<vi>
#define vvl vector<vector<ll>>

int n;
ll k;
vi arr, t;
vvi pos;
vvl ts;

void modify(int p, int v) { for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]); }

int query(int l) {
  int ans = 0, r = n;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = max(ans, t[l++]);
    if (r & 1) ans = max(ans, t[--r]);
  }
  return ans;
}

void modify(int i, int p, ll v) {
  p = lower_bound(pos[i].begin(), pos[i].end(), p) - pos[i].begin();
  for (ts[i][p += pos[i].size()] = v; p > 1; p >>= 1) ts[i][p >> 1] = min(ts[i][p] + ts[i][p ^ 1], k);
}

ll query(int i, int l) {
  l = lower_bound(pos[i].begin(), pos[i].end(), l) - pos[i].begin();
  int r = pos[i].size();
  ll ans = 0;
  for (l += pos[i].size(), r += pos[i].size(); l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = min(ans + ts[i][l++], k);
    if (r & 1) ans = min(ans + ts[i][--r], k);
  }
  return ans;
}

vi kth() {
  vi lis(n);
  for (int i = n - 1; i >= 0; --i) modify(arr[i], lis[i] = query(arr[i] + 1) + 1);
  int sz = 0; for (int num : lis) sz = max(sz, num + 1);
  pos.resize(sz), ts.resize(sz);
  for (int i = 0; i < n; ++i) pos[lis[i]].push_back(arr[i]);
  for (int i = 1; i < sz; ++i) sort(pos[i].begin(), pos[i].end()), ts[i].resize(2 * pos[i].size());
  for (int i = n - 1; i >= 0; --i) {
    if (lis[i] == 1) modify(1, arr[i], 1);
    else modify(lis[i], arr[i], query(lis[i] - 1, arr[i] + 1));
  }
  vi at(n); for (int i = 0; i < n; ++i) at[arr[i]] = i;
  int ind = -1;
  ll sum = 0;
  vi ans(sz - 1);
  for (int i = sz - 1; i > 0; --i) {
    int j;
    for (j = pos[i].size() - 1; j >= 0; --j) {
      if (at[pos[i][j]] < ind) continue;
      if (sum + ts[i][j + pos[i].size()] >= k) break;
      sum += ts[i][j + pos[i].size()];
    }
    ans[sz - 1 - i] = pos[i][j];
    ind = at[pos[i][j]];
  }
  return ans;
}

int main() {
  ifstream in("itout.in");
  ofstream out("itout.out");
  in >> n >> k;
  arr.resize(n), t.resize(2 * n);
  for (int i = 0; i < n; ++i) { in >> arr[i]; --arr[i]; }
  vi lis = kth(), ans(n - lis.size());
  for (int i = 0, j = 0, l = 0; i < n; ++i) {
    if (j < lis.size() && lis[j] == i) ++j;
    else ans[l++] = i + 1;
  }
  out << ans.size() << '\n';
  for (int num : ans) out << num << '\n';
}
