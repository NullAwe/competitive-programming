#include <bits/stdc++.h>
using namespace std;

#define ll long long

int dp[1 << 20];
ll sums[1 << 20], sumlax[1 << 20];
bitset<(1 << 20)> vis;

void dfs(int mask) {
  if (vis[mask]) return;
  int lowest = 1;
  while ((mask & lowest) == 0) lowest <<= 1;
  int bef = mask ^ lowest;
  bool spec = bef & (lowest * 2);
  bef |= lowest * 2;
  dfs(bef);
  if (spec) sumlax[mask] = sums[bef] - (ll) dp[mask] * lowest;
  else sumlax[mask] = sumlax[bef] - (ll) dp[mask] * lowest;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, q; cin >> n >> q;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int num : arr) ++dp[num];
  for (int bit = 0; bit < 20; ++bit) {
    for (int i = 0; i < (1 << 20); ++i) {
      if (i & (1 << bit)) continue;
      dp[i] += dp[i ^ (1 << bit)];
    }
  }
  for (int num : arr) {
    ll s = 0;
    for (int i = 0; i < 20; ++i) {
      if (num & (1 << i)) sums[num - s] += s;
      sumlax[1 << i] += s;
      s += num & (1 << i);
      vis[1 << i] = true;
    }
  }
  for (int bit = 0; bit < 20; ++bit) {
    for (int i = 0; i < (1 << 20); ++i) {
      if (i & (1 << bit)) continue;
      if (!(i & ((1 << bit) - 1))) continue;
      sums[i] += sums[i ^ (1 << bit)];
    }
  }
  for (int i = 1; i < (1 << 20); ++i) {
    if (!vis[i]) dfs(i);
  }
  int start = 61;
  int tmp = n;
  while (tmp) start -= 1, tmp >>= 1;
  ll sum = 0;
  for (int num : arr) sum += num;
  for (int i = 0; i < q; ++i) {
    ll x; cin >> x;
    ll msk = 0, cnt = 0;
    bool done = false;
    for (int bit = start; bit >= 0; --bit) {
      ll shft = 1LL << bit;
      ll sm = 0;
      if (bit < 20) sm = sumlax[msk ^ shft] - sums[msk ^ shft];
      else sm = sum;
      int num = n - cnt;
      if (bit < 20) num -= dp[msk ^ shft];
      ll fromCnt = (ll) cnt * shft;
      ll fromSm = (ll) num * shft - sm;
      if (fromCnt + fromSm <= x) {
        x -= fromCnt + fromSm;
        msk ^= shft;
        cnt += num;
        if (bit >= 20) {
          done = true;
          break;
        }
      }
    }
    if (done) msk += x / n;
    cout << msk << '\n';
  }
  return 0;
}