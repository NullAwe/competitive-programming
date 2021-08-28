#include <bits/stdc++.h>
using namespace std;

int main() {
  string str; cin >> str;
  char cur = ' ';
  int ans = 0, num = 0;
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] != cur) {
      ans = max(ans, num);
      cur = str[i];
      num = 1;
    } else ++num;
  }
  ans = max(ans, num);
  // Output:
  cout << ans << endl;
}
