#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  set<int> todo;
  for (int i = 1; i <= n; ++i) todo.insert(i);
  bool skip = false;
  while (todo.size()) {
    set<int> rem;
    for (int num : todo) {
      skip = !skip;
      if (skip) continue;
      rem.insert(num);
      // Output:
      cout << num << ' ';
    }
    for (int num : rem) todo.erase(num);
  }
  // Output:
  cout << endl;
  return 0;
}
