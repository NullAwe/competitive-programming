#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, at;
bool up = true;

bool qry(int x) {
  at += up ? x : -x, up = !up;
  cout << "? " << at << endl;
  bool ans; cin >> ans;
  return ans;
}

int32_t main() {
  cin >> n;
  bool added = true;
  int l = 0, r = n;
  at = 1;
  while (l < r - 1) {
    l = (l + r) / 2;
    int keep = l;
    l = (l + r) / 2, at += (l - keep);
  }
  cout << "? " << at << endl;
  int tmp; cin >> tmp;
  int lo = 0, hi = n;
  while (lo < hi - 1) {
    int mid = (lo + hi) >> 1;
    if (qry(mid)) hi = mid;
    else lo = mid;
  }
  cout << "= " << hi << '\n';
  return 0;
}
