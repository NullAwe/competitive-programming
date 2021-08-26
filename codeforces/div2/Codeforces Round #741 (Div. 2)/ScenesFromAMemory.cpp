#include <bits/stdc++.h>
using namespace std;

bool contains(string s, string t) {
  int ind = 0;
  for (int i = 0; i < s.size() && ind < t.size(); ++i)
    if (s[i] == t[ind]) ++ind;
  return ind == t.size();
}

void solve(vector<bool>& sieve) {
  int k; cin >> k;
  string str; cin >> str;
  // Checks all non-prime integers (should stop before 100):
  for (int i = 1; i < sieve.size(); ++i) {
    if (!sieve[i]) continue;
    string t = to_string(i);
    if (contains(str, t)) {
      // Output:
      cout << t.size() << endl;
      cout << t << endl;
      return;
    }
  }
}

int main() {
  // Computes all non-prime integers less than 1000000:
  vector<bool> sieve(1000000);
  sieve[1] = true;
  for (int i = 2; i < sieve.size(); ++i) {
    if (sieve[i]) continue;
    for (int j = 2 * i; j < sieve.size(); j += i) sieve[j] = true;
  }
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve(sieve);
  return 0;
}
