#include <iostream>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

int main() {
  int n; cin >> n;
  ll a = 1, b = 0;
  for (int i = 1; i < n; ++i) {
    ll tmp = b;
    b = (a + b) * i % MOD;
    a = tmp;
  }
  cout << b << '\n';
  return 0;
}

