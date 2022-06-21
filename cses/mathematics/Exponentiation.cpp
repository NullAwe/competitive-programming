#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

long long pow(long long a, long long b) {
  if (b < 1) return 1;
  long long base = pow(a, b / 2);
  base *= base;
  base %= 1000000007;
  if (b % 2 == 1) base *= a;
  base %= MOD;
  return base;
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    long long a, b;
    cin >> a >> b;
    cout << pow(a, b) << "\n";
  }
  return 0;
}

