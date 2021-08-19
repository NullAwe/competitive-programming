#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll GCD(ll a, ll b) {
  if (b == 0) return a;
  return GCD(b, a % b);
}

ll LCM(ll a, ll b) {
  return a * b / gcd(a, b);
}

int main() {
  ll a, b; cin >> a >> b;
  // Guarantees that b is larger:
  if (a > b) {
    // Swaps a and b:
    ll tmp = a;
    a = b;
    b = tmp;
  }
  // Corner case:
  if (a % b == 0) { // LCM is b when k = 0, which is already the smallest.
    cout << 0 << endl;
    return 0;
  }
  ll diff = b - a;
  vector<ll> divs;
  // Finds all the divisors of diff:
  for (ll div = 1; div * div <= diff; ++div) {
    if (diff % div > 0) continue; // div is not a divisor of diff.
    divs.push_back(div);
    divs.push_back(diff / div);
  }
  ll leastLCM = LLONG_MAX, k;
  // Iterates through all divisors of b - a to find minimum LCM:
  for (ll div : divs) {
    ll add = div - ((a - 1) % div + 1);
    ll compare = LCM(a + add, b + add);
    if (compare < leastLCM) {
      leastLCM = compare;
      k = add;
    } else if (compare == leastLCM) {
      k = min(k, add);
    }
  }
  // Output:
  cout << k << endl;
  return 0;
}