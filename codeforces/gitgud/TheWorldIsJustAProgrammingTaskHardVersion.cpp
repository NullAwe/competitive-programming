#include <bits/stdc++.h>
using namespace std;

int get(string& s) {
  int m = 0, at = s.size() - 1, sum = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == '(') ++sum;
    else --sum;
    if (sum < m) m = sum, at = i;
  }
  string t; for (int i = at + 1; i < at + s.size() + 1; ++i) t += s[i % s.size()];
  s = t;
  sum = 0;
  int ans = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == '(') ++sum;
    else --sum;
    if (!sum) ++ans;
  }
  return ans;
}

int main() {
  int n; cin >> n;
  string s; cin >> s;
  int m = 0, at = n - 1, sum = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '(') ++sum;
    else --sum;
    if (sum < m) m = sum, at = i;
  }
  if (sum) {
    cout << "0\n1 1\n";
    return 0;
  }
  string t; for (int i = at + 1; i < at + n + 1; ++i) t += s[i % n];
  s = t;
  int match = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '(') ++sum;
    else --sum;
    if (!sum) {
      match = i;
      break;
    }
  }
  int a = 0, b = 0;
  stack<int> starts;
  vector<int> cont(n);
  int me = -1, ma = 1, a2 = 1, b2 = 1;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '(') starts.push(i);
    else {
      int start = starts.top(); starts.pop();
      if (!start) cont[i] = 1;
      else cont[i] = cont[start - 1] + 1;
      if (starts.size() > 1) continue;
      if (starts.size() == 1) {
        if (cont[i - 1] > me) {
          me = cont[i - 1];
          a = start, b = i;
        }
      } else {
        if (cont[i - 1] + 1 > ma) {
          ma = cont[i - 1] + 1;
          a2 = start, b2 = i;
        }
      }
    }
  }
  string try1 = s, try2 = s;
  swap(try1[a], try1[b]); swap(try2[a2], try2[b2]);
  if (get(try2) > get(try1)) try1 = try2, a = a2, b = b2;
  cout << get(try1) << '\n' << (a + at + 1) % s.size() + 1 << ' ' << (b + at + 1) % s.size() + 1 << '\n';
  return 0;
}
