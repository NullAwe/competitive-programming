#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  ll n, r, s, t, d; cin >> n >> r >> t >> s >> d;
  vector<ll> mons(n); for (int i = 0; i < n; ++i) cin >> mons[i];
  // Finds answer using dynamic programming:
  vector<ll> memo(n + 1);
  for (int i = n - 1; i >= 0; --i) {
    ll thisMin = min(r + t, r * (mons[i] + 2));
    if (i == n - 1) {
      memo[i] = min(mons[i] * r + s, thisMin + 2 * d);
      continue;
    }
    ll nextMin = min(r + t, r * (mons[i + 1] + 2));
    memo[i] = min(mons[i] * r + s + d + memo[i + 1],
      min(thisMin + 3 * d + memo[i + 1], thisMin + nextMin + 4 * d + memo[i + 2]));
    if (i == n - 2) memo[i] = min(memo[i], min(thisMin + nextMin + 3 * d, thisMin + memo[i + 1] + 2 * d));
  }
  // Output:
  cout << memo[0] << endl;
  return 0;
}
