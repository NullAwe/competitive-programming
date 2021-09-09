#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n; cin >> n;
  vector<ll> prefix(n + 1);
  int neg = INT_MIN;
  for (int i = 1; i <= n; ++i) {
    int a; cin >> a;
    neg = max(neg, a);
    prefix[i] = prefix[i - 1] + a;
  }
  if (neg < 0) {
    cout << neg << endl;
    return 0;
  }
  ll mi = 0, ma = 0;
  for (int i = 1; i <= n; ++i) {
    ma = max(ma, prefix[i] - mi);
    mi = min(mi, prefix[i]);
  }
  cout << ma << endl;
  return 0;
}
