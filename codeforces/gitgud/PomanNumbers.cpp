#include <bits/stdc++.h>
using namespace std;

#define ll long long

int pow(int y) {
  if (y <= 0) return 1;
  int base = pow(y / 2);
  base *= base;
  if (y % 2 == 1) base *= 2;
  return base;
}

int main() {
  ll n, k; cin >> n >> k;
  string str; cin >> str;
  // Adjusts k for two values, since these two values have fixed signs:
  k -= pow(str[n - 1] - 'a');
  k += pow(str[n - 2] - 'a');
  vector<int> pows(n - 2);
  for (int i = 0; i < n - 2; ++i) pows[i] = str[i] - 'a';
  sort(pows.begin(), pows.end());
  // Processes values from largest to smallest, we can choose any value.
  // We can do this because of the 2^(value) property:
  for (int i = n - 3; i >= 0; --i) {
    if (k > 0) k -= pow(pows[i]);
    else k += pow(pows[i]);
  }
  // Output:
  if (k == 0) cout << "Yes" << endl;
  else cout << "No" << endl;  
  return 0;
}
