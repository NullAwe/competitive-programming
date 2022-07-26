#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MAX_N = 2500;

int n, m, k, sum[MAX_N + 1][MAX_N + 1];
string arr[MAX_N];

inline int query(int u, int d, int l, int r, bool vert) {
  if (vert) swap(u, l), swap(d, r);
  return sum[d][r] - sum[d][l] - sum[u][r] + sum[u][l];
}

ll dnc(int u, int d, int l, int r) {
  if (d + r - u - l == 2) return arr[u][l] - '0' == k;
  bool vert = r - l < d - u;
  if (vert) swap(u, l), swap(d, r);
  ll count = 0;
  int mid = (l + r) >> 1;
  for (int top = u; top < d; ++top) {
    int l1[k + 2], r1[k + 2], il = 1, ir = 1; for (int i = 0; i <= k + 1; ++i) l1[i] = l - 1, r1[i] = r;
    l1[0] = mid - 1, r1[0] = mid;
    for (int i = mid - 1; i >= l && il <= k + 1; --i) if (query(top, top + 1, i, i + 1, vert)) l1[il++] = i;
    for (int i = mid; i < r && ir <= k + 1; ++i) if (query(top, top + 1, i, i + 1, vert)) r1[ir++] = i;
    for (int ol = 0; ol <= k; ++ol) {
      if (l1[ol] < l || r1[k - ol] >= r) continue;
      count += (l1[ol] - l1[ol + 1]) * (r1[k - ol + 1] - r1[k - ol]);
    }
    for (int bot = top + 1; bot < d; ++bot) {
      for (int i = 0; i <= k + 1; ++i) {
        while (l1[i] < mid - 1 && query(top, bot + 1, l1[i] + 1, mid, vert) >= i) ++l1[i];
        while (r1[i] > mid && query(top, bot + 1, mid, r1[i], vert) >= i) --r1[i];
      }
      for (int ol = 0; ol <= k; ++ol) {
        if (l1[ol] < l || r1[k - ol] >= r) continue;
        count += (l1[ol] - l1[ol + 1]) * (r1[k - ol + 1] - r1[k - ol]);
      }
    }
  }
  return (vert ? dnc(l, mid, u, d) + dnc(mid, r, u, d) : dnc(u, d, l, mid) + dnc(u, d, mid, r)) + count;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> m >> k;
  for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) sum[i][j] = 0;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
    sum[i + 1][j + 1] = sum[i][j + 1] + sum[i + 1][j] - sum[i][j] + arr[i][j] - '0';
  cout << dnc(0, n, 0, m) << '\n';
  return 0;
}

