#include <iostream>
using namespace std;

#define ll long long

const int MOD = 100000;

ll p(int x, int y) {
  ll ans = 1;
  for (int i = 0; i < y; ++i) ans = ans * x % MOD;
  return ans;
}

int main() {
  string str; cin >> str;
  str = to_string(p(stoi(string({str[0], str[2], str[4], str[3], str[1]})), 5));
  for (int i = 0; i < 5 - str.size(); ++i) cout << 0;
  cout << str << '\n';
  return 0;
}
