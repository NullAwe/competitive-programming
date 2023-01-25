#include <bits/stdc++.h>
using namespace std;

int qry(int x) {
  cout << "? " << x << endl;
  int ans; cin >> ans;
  return ans;
}

int main() {
  int n; cin >> n;
  int lo = 0, hi = n + 1;
  while (lo < hi - 1) {
    int mid = (lo + hi) >> 1;
    int ans = qry(mid);
    if (ans > 0) hi = mid;
    else lo = mid;
    if (!ans) break;
  }
  cout << "= " << lo << endl;
  return 0;
}