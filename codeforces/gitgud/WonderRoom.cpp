#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  ll n, a, b; cin >> n >> a >> b;
  n *= 6;
  // Takes care of the special case where the room is already large enough:
  if (a * b >= n) {
    cout << a * b << endl;
    cout << a << " " << b << endl;
    return 0;
  }
  // Guarantees that a <= b:
  bool swap = a > b;
  if (swap) {
    ll tmp = a;
    a = b;
    b = tmp;
  }
  ll to = (int) sqrt(n) + 1, ans = LLONG_MAX;
  ll fa, fb;
  for (int i = a; i < to; ++i) {
    if (i > n) break;
    ll j = n / i;
    if (n % i > 0) ++j;
    if (j >= b && i * j < ans) {
      ans = i * j;
      fa = i;
      fb = j;
    }
  }
  // Output:
  cout << ans << endl;
  // Outputs backwards if swapped earlier:
  if (swap) cout << fb << " " << fa << endl;
  else cout << fa << " " << fb << endl;
  return 0;
}

