#include <bits/stdc++.h>
using namespace std;

void solve() {
  string str; cin >> str;
  // Splits the string into two numbers:
  vector<int> nums(2);
  for (int i = 0; i < str.size(); ++i) nums[i % 2] = nums[i % 2] * 10 + str[i] - '0';
  ++nums[0]; ++nums[1];
  // Output:
  cout << nums[0] * nums[1] - 2 << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}