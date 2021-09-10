#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr.begin(), arr.end());
  ll sum = 0;
  for (int i = 0; i < n; ++i) {
    if (arr[i] > sum + 1) {
      // Output:
      cout << sum + 1 << endl;
      return 0;
    }
    else sum += arr[i];
  }
  // Output:
  cout << sum + 1 << endl;
  return 0;
}
