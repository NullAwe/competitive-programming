#include <bits/stdc++.h>
using namespace std;

const long long MOD1 = 1000000006, MOD2 = 1000000007;

long long pow(long long a, long long b, long long mod) {
  if (b < 1) return 1;
  long long base = pow(a, b / 2, mod);
  base *= base;
  base %= mod;
  if (b % 2 == 1) base *= a;
  base %= mod;
  return base;
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    long long a, b, c;
    cin >> a >> b >> c;
    cout << pow(a, pow(b, c, MOD1), MOD2) << "\n";
  }
  return 0;
}

