#include <bits/stdc++.h>
#include "books.h"
using namespace std;

#define ll long long

void solve(int n, int k, ll a, int s) {
  int lo = -1, hi = n;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    if (skim(mid + 1) <= a) lo = mid;
    else hi = mid;
  }
  vector<ll> vals(n);
  for (int i = 0; i < k; ++i) vals[i] = skim(i + 1);
  for (int i = max(hi - k, 0); i < min(hi + 1, n); ++i) vals[i] = skim(i + 1);
  ll sum = 0;
  vector<int> ans(k);
  for (int i = 0; i < k - 1; ++i) sum += vals[i], ans[i] = i + 1;
  if (hi < n) {
    sum += vals[hi], ans[k - 1] = hi + 1;
    if (sum <= 2 * a) {
      answer(ans);
      return;
    }
    sum -= vals[hi];
  }
  sum += vals[k - 1], ans[k - 1] = k;
  if (sum > 2 * a) {
    impossible();
    return;
  }
  if (sum >= a) {
    answer(ans);
    return;
  }
  int base = max(k, hi - k);
  for (int i = 0; base + i < hi; ++i) {
    sum -= vals[ans[i] - 1];
    sum += vals[base + i], ans[i] = base + i + 1;
    if (sum >= a) {
      answer(ans);
      return;
    }
  }
  impossible();
}
