#include <bits/stdc++.h>
using namespace std;

void fillZ(string str, vector<int>& z) {
  int n = str.length();
  int l = 0, r = 0, k;
  for (int i = 1; i < n; ++i) {
    if (i > r) {
      l = r = i;
      while (r < n && str[r - l] == str[r]) r++;
      z[i] = r - l;
      --r;
    } else {
      k = i - l;
      if (z[k] < r - i + 1) z[i] = z[k];
      else {
        l = i;
        while (r < n && str[r - l] == str[r]) r++;
        z[i] = r - l;
        r--;
      }
    }
  }
}

int has(string text, string pattern) {
  string concat = pattern + "$" + text;
  int n = concat.size();
  vector<int> z(n);
  fillZ(concat, z);
  for (int i = 0; i < n; ++i)
    if (z[i] == pattern.size()) return i - pattern.size() - 1;
  return -1;
}

int main() {
  string s, t; cin >> s >> t;
  string rev = s;
  for (int i = 0; i < rev.size() / 2; ++i) {
    char tmp = rev[i];
    rev[i] = rev[rev.size() - i - 1];
    rev[rev.size() - i - 1] = tmp;
  }
  int ind = 0, ans = 0;
  vector<pair<int, int>> moves;
  while (ind < t.size()) {
    // Finds longest possible next segment to be covered using binary search:
    string rest = t.substr(ind);
    int lo = -1, hi = rest.size();
    while (lo < hi - 1) {
      int mid = (lo + hi) / 2;
      if (has(s, rest.substr(0, mid + 1)) >= 0 || has(rev, rest.substr(0, mid + 1)) >= 0) lo = mid;
      else hi = mid;
    }
    // Executes if we cannot cover the next square:
    if (lo < 0) {
      cout << -1 << endl;
      return 0;
    }
    ++ans;
    ind += lo + 1;
    int one = has(s, rest.substr(0, lo + 1)), two = has(rev, rest.substr(0, lo + 1));
    if (one >= 0) moves.push_back({one + 1, one + lo + 1});
    else moves.push_back({s.size() - two, s.size() - two - lo});
  }
  // Output:
  cout << ans << endl;
  for (pair<int, int> m : moves) cout << m.first << " " << m.second << endl;
  return 0;
}
