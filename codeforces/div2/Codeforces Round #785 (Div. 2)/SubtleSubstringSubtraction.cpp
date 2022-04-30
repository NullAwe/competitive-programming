#include <iostream>
using namespace std;

void solve() {
  string str; cin >> str;
  int total = 0;
  for (int i = 0; i < str.size(); ++i) total += str[i] - 'a' + 1;
  int alice = total; if (str.size() % 2) alice -= min(str[0], str[str.size() - 1]) - 'a' + 1;
  cout << (alice > total - alice ? "Alice " : "Bob ") << abs(total - 2 * alice) << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
