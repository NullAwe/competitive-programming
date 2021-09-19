#include <bits/stdc++.h>
using namespace std;

int main() {
  int x, n; cin >> x >> n;
  set<int> lights;
  multiset<int> dists;
  lights.insert(0);
  lights.insert(x);
  dists.insert(x);
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    // Finds the two traffic lights that surround the new one:
    auto higher = lights.upper_bound(a), lower = prev(higher);
    // Splits the space in between in two:
    lights.insert(a);
    dists.erase(dists.find(*higher - *lower));
    dists.insert(a - *lower);
    dists.insert(*higher - a);
    // Output:
    cout << *(prev(dists.end())) << ' ';
  }
  return 0;
}
