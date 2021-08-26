#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  string s; cin >> s;
  int t; cin >> t;
  // Takes care of a corner case:
  if (t == 1) {
    int count = 0;
    for (int i = 0; i < n; ++i) if (s[i] == '?') ++count;
    cout << count << endl;
    return 0;
  }
  // Computes number of question marks replaced if we find the pattern starting at an index:
  vector<int> repl(n);
  int count = 0;
  for (int i = 0; i < t; ++i)
    if (s[i] == '?') ++count;
  repl[0] = count;
  for (int i = 0; i + t < n; ++i) {
    if (s[i] == '?') --count;
    if (s[i + t] == '?') ++count;
    repl[i + 1] = count;
  }
  // Precomputes furthest "ababa..." pattern and first question mark in suffix chain:
  vector<int> pattern(n);
  for (int i = n - 1; i >= 0; --i) {
    if (i + 2 >= n) {
      if (s[i] == 'a' || s[i] == '?') pattern[i] = 1;
      if (i + 1 < n && (s[i] == 'a' || s[i] == '?') && (s[i + 1] == 'b' || s[i + 1] == '?')) pattern[i] = 2;
    } else {
      if (s[i] == 'b') continue;
      bool cont = (s[i] == 'a' || s[i] == '?') && (s[i + 1] == 'b' || s[i + 1] == '?');
      if (pattern[i + 2] > 0 && cont) pattern[i] = pattern[i + 2] + 2;
      else pattern[i] = cont ? 2 : 1;
    }
  }
  // Finds answer with dynamic programming:
  vector<pair<int, int>> memo(n + 1);
  for (int i = n - 1; i >= 0; --i) {
    memo[i] = memo[i + 1];
    if (pattern[i] < t) continue;
    pair<int, int> comp = memo[i + t];
    ++comp.first;
    comp.second += repl[i];
    if (comp.first > memo[i].first || (comp.first == memo[i].first && comp.second < memo[i].second)) memo[i] = comp;
  }
  // Output:
  cout << memo[0].second << endl;
  return 0;
}
