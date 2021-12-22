#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

vector<ll> fact;

ll p(ll x, ll y) {
  if (y <= 0) return 1;
  ll base = p(x, y / 2);
  base = (base * base) % MOD;
  if (y % 2) base *= x;
  return base % MOD;
}

ll inv(ll x) {
  return p(x, MOD - 2);
}

ll nCr(ll n, ll r) {
  return (fact[n] * inv(fact[r]) % MOD) * inv(fact[n - r]) % MOD;
}

int main() {
  int n; cin >> n;
  fact = vector<ll>(n + 1);
  fact[0] = 1;
  for (int i = 1; i <= n; ++i) fact[i] = (fact[i - 1] * i) % MOD;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr.begin(), arr.end());
  ll sum = 0; for (int num : arr) sum += num;
  // Takes care of the edge case where no permutations exist:
  if (sum % n) {
    cout << 0 << endl;
    return 0;
  }
  ll average = sum / n;
  int nl = 0, nm = 0;
  bool dl = false, dm = false;
  for (int num : arr) {
    if (num >= average) break;
    if (num != arr[0]) dl = true;
    ++nl;
  }
  for (int num : arr) {
    if (num <= average) continue;
    if (num != arr[n - 1]) dm = true;
    ++nm;
  }
  // Takes care of the edge case where any permutation works:
  if (nl == 1 || nm == 1) {
    set<int> nums;
    map<int, int> m;
    for (int num : arr) {
      nums.insert(num);
      ++m[num];
    }
    ll ans = fact[n];
    for (int num : nums) ans = ans * inv(fact[m[num]]) % MOD;
    cout << ans << endl;
    return 0;
  }
  // Takes care of the edge case where only the average is present:
  if (nl == 0 && nm == 0) {
    cout << 1 << endl;
    return 0;
  }
  set<int> nums;
  map<int, int> m;
  for (int num : arr) {
    nums.insert(num);
    ++m[num];
  }
  ll div1 = 1, div2 = 1;
  for (int num : nums) {
    if (num < average) div1 = div1 * fact[m[num]] % MOD;
    else if (num > average) div2 = div2 * fact[m[num]] % MOD;
  }
  ll mult = ((inv(div1) * inv(div2) % MOD) * (fact[nl] * fact[nm] % MOD)) % MOD;
  ll ans = 0;
  for (int cf = nl; cf <= n - nm; ++cf) ans = (ans + (nCr(cf - 1, nl - 1) * nCr(n - cf, nm) % MOD) * mult % MOD) % MOD;
  // Output:
  cout << ans * 2 % MOD << endl;
  return 0;
}
