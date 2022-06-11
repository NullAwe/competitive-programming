#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n, q; cin >> n >> q;
  vector<ll> pref(n + 1);
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    pref[i + 1] = pref[i] + x;
  }
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b;
    cout << pref[b] - pref[a - 1] << '\n';
  }
  return 0;
}
