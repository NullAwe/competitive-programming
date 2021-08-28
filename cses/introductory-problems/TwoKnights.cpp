#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  ll n; cin >> n;
  // Output:
  for (ll i = 1; i <= n; ++i)
    cout << (i - 1) * (i + 4) * (i * i - 3 * i + 4) / 2 << endl;
  return 0;
}
