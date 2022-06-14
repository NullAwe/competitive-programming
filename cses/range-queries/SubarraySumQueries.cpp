#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct STV {
  ll sum, maxSum, sumL, sumR;
  STV(ll sum, ll maxSum, ll sumL, ll sumR) : sum(sum), maxSum(maxSum), sumL(sumL), sumR(sumR) {}
};

vector<STV> t;
int n;

void modify(int v, int tl, int tr, int p, int val) {
  if (tl == tr) {
    int sums = max(val, 0);
    t[v] = STV(val, sums, sums, sums);
    return;
  }
  int m = (tl + tr) / 2;
  if (p <= m) modify(v << 1, tl, m, p, val);
  else modify((v << 1) + 1, m + 1, tr, p, val);
  STV l = t[v << 1], r = t[(v << 1) + 1];
  t[v] = STV(l.sum + r.sum, max(max(l.maxSum, r.maxSum), l.sumR + r.sumL), max(l.sumL, l.sum + r.sumL), max(r.sumR, r.sum + l.sumR));
}

STV query(int v, int tl, int tr, int l, int r) {
  if (l > r) return STV(0, 0, 0, 0);
  if (tl == l && tr == r) return t[v];
  int m = (tl + tr) / 2;
  if (r <= m) return query(v << 1, tl, m, l, r);
  if (l > m) return query((v << 1) + 1, m + 1, tr, l, r);
  STV ln = query(v << 1, tl, m, l, m), rn = query((v << 1) + 1, m + 1, tr, m + 1, r);
  return STV(ln.sum + rn.sum, max(max(ln.maxSum, rn.maxSum), ln.sumR + rn.sumL), max(ln.sumL, ln.sum + rn.sumL), max(rn.sumR, rn.sum + ln.sumR));
}

int main() {
  cin >> n; t.reserve(3 * n); for (int i = 0; i < 3 * n; ++i) t.push_back(STV(0, 0, 0, 0));
  int m; cin >> m;
  for (int i = 0; i < n; ++i) { int x; cin >> x; modify(1, 0, n - 1, i, x); }
  for (int i = 0; i < m; ++i) {
    int p, x; cin >> p >> x; --p;
    modify(1, 0, n - 1, p, x);
    cout << query(1, 0, n - 1, 0, n - 1).maxSum << '\n';
  }
  return 0;
}

