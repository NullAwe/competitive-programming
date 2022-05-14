#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  ll a = 0, b = 0;
  for (int i = 0; i < n; ++i) {
    if (i & 1) a += (arr[i] + 1) / 2, b += arr[i] / 2;
    else a += arr[i] / 2, b += (arr[i] + 1) / 2;
  }
  cout << min(a, b) << '\n';
}
