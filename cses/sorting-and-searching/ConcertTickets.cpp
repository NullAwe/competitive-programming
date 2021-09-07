#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m; cin >> n >> m;
  multiset<int> tck;
  vector<int> ppl(m);
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    tck.insert(a);
  }
  for (int i = 0; i < m; ++i) {
    int a; cin >> a;
    auto it = tck.upper_bound(a);
    // Output:
    if (it == tck.begin()) cout << -1 << endl;
    else {
      --it;
      cout << *it << endl;
      // Deletes element because each ticket can only be used once:
      tck.erase(it);
    }
  }
  return 0;
} 
