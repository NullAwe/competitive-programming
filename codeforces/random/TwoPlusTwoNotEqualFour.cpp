#include <bits/stdc++.h>
using namespace std;

int main() {
  string str; cin >> str;
  int ans = 0, sign = 1, curNum = 0;
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] == '+') {
      ans += sign * curNum;
      curNum = 0;
      sign = 1;
    } else if (str[i] == '-') {
      ans += sign * curNum;
      curNum = 0;
      sign = -1;
    }
    curNum *= 10;
    curNum += str[i] - '0';
  }
  ans += sign * curNum;
  // Output:
  cout << ans << endl;
  return 0;
}
