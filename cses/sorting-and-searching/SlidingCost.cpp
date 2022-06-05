#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n, k; cin >> n >> k;
  vector<int> arr(n);
  multiset<int> s;
  for (int i = 0; i < k; ++i) {
    cin >> arr[i];
    s.insert(arr[i]);
  }
  ll ls = 0, rs = 0;
  multiset<int> l, r;
  while (s.size()) {
    ls += *s.begin(), l.insert(*s.begin()), s.erase(s.begin());
    if (s.size()) rs += *--s.end(), r.insert(*--s.end()), s.erase(--s.end());
  }
  cout << (l.size() - r.size()) * *--l.end() + rs - ls;
  for (int i = k; i < n; ++i) {
    cin >> arr[i];
    if (l.count(arr[i - k])) ls -= arr[i - k], l.erase(l.lower_bound(arr[i - k]));
    else rs -= arr[i - k], r.erase(r.lower_bound(arr[i - k]));
    if (!r.size() || arr[i] < *r.begin()) ls += arr[i], l.insert(arr[i]);
    else rs += arr[i], r.insert(arr[i]);
    while (r.size() > l.size()) ls += *r.begin(), l.insert(*r.begin()), rs -= *r.begin(), r.erase(r.begin());
    while (l.size() > r.size() + 1) rs += *--l.end(), r.insert(*--l.end()), ls -= *--l.end(), l.erase(--l.end());
    cout << ' ' << (l.size() - r.size()) * *--l.end() + rs - ls;
  }
  cout << '\n';
  return 0;
}

