#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define vi vector<int>
#define vvi vector<vi>

int main() {
  ifstream in("redistricting.in");
  ofstream out("redistricting.out");
  int n, k; in >> n >> k;
  string str; in >> str;
  vi vals(n + 1); vals[n] = n; int shift = n;
  for (int i = n - 1; i >= 0; --i) vals[i] = shift += str[i] == 'H' ? 1 : -1;
  vvi ss(2 * n + 1);
  for (int i = 0; i < n; ++i) ss[vals[i]].push_back(i);
  ss[n].push_back(n);
  vi lb(n), lp2(n), mn(n);
  set<pii> nk; nk.insert({n, n});
  mn[n - 1] = str[n - 1] == 'H' ? -1 : n - 1;
  for (int i = n - 1; i >= 0; --i) {
    int s = vals[i];
    while (ss[s].size() && ss[s].back() >= i + k) ss[s].resize(ss[s].size() - 1);
    while (s - 2 >= 0 && ss[s - 2].size() && ss[s - 2].back() >= i + k) ss[s - 2].resize(ss[s - 2].size() - 1);
    int val = (s - 2 < 0 || !ss[s - 2].size()) ? 0 : ss[s - 2].back();
    lb[i] = ss[s].back() - 1, lp2[i] = val - 1;
    nk.insert({s, i});
    pii ms = *--nk.end();
    mn[i] = s > ms.first ? -1 : ms.second - 1;
    if (i + k <= n) nk.erase({vals[i + k], i + k});
  }
  vi lo(n);
  if (str[n - 1] == 'H') lo[n - 1] = n - 1;
  for (int i = n - 2; i >= 0; --i) {
    if (str[i] == 'H') lo[i] = lb[i + 1];
    else lo[i] = lp2[i + 1];
  }
  vi ans(n + 1, INT_MAX); ans[n] = 0;
  for (int i = n - 1; i >= 0; --i) {
    if (lo[i] >= 0) ans[i] = ans[lo[i] + 1];
    if (mn[i] >= 0) ans[i] = min(ans[i], ans[mn[i] + 1] + 1);
  }
  out << ans[0] << '\n';
  return 0;
}
