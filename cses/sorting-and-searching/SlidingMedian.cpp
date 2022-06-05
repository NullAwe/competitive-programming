#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k; cin >> n >> k;
  vector<int> arr(n);
  multiset<int> s;
  for (int i = 0; i < k; ++i) {
    cin >> arr[i];
    s.insert(arr[i]);
  }
  multiset<int> l, r;
  while (s.size()) {
    l.insert(*s.begin()), s.erase(s.begin());
    if (s.size()) r.insert(*--s.end()), s.erase(--s.end());
  }
  cout << *--l.end();
  for (int i = k; i < n; ++i) {
    cin >> arr[i];
    if (l.count(arr[i - k])) l.erase(l.lower_bound(arr[i - k]));
    else r.erase(r.lower_bound(arr[i - k]));
    if (!r.size() || arr[i] < *r.begin()) l.insert(arr[i]);
    else r.insert(arr[i]);
    while (r.size() > l.size()) l.insert(*r.begin()), r.erase(r.begin());
    while (l.size() > r.size() + 1) r.insert(*--l.end()), l.erase(--l.end());
    cout << ' ' << *--l.end();
  }
  cout << '\n';
  return 0;
}
