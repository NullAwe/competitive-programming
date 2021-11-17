#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < arr.size(); ++i) {
    int num = arr[i], mult = 2;
    ll prod = 1;
    while (mult <= i + 2 && prod <= num) {
      if (prod % mult) {
        int prime = 0;
        for (int i = 2; i * i <= mult; ++i) {
          if (mult % i == 0) {
            prime = i;
            break;
          }
        }
        if (prime == 0) prod *= mult;
        else {
          while (prod % prime == 0) prod /= prime;
          prod *= mult;
        }
      }
      ++mult;
    }
    if (num % prod == 0) {
      // Output:
      cout << "NO" << endl;
      return;
    }
  }
  // Output:
  cout << "YES" << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}