#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream in("feast.in");
  ofstream out("feast.out");
  int t, a, b; in >> t >> a >> b;
  // Finds largest fullness with no water with dynamic programming:
  vector<int> drank(t + 1);
  for (int i = t; i >= 0; --i) {
    drank[i] = i;
    if (i + a <= t) drank[i] = max(drank[i], drank[i + a]);
    if (i + b <= t) drank[i] = max(drank[i], drank[i + b]);
  }
  // Finds largest fullness with water with dynamic programming:
  vector<int> notDrank(t + 1);
  for (int i = t; i >= 0; --i) {
    notDrank[i] = max(i, drank[i / 2]);
    if (i + a <= t) notDrank[i] = max(notDrank[i], notDrank[i + a]);
    if (i + b <= t) notDrank[i] = max(notDrank[i], notDrank[i + b]);
  }
  // Output:
  out << notDrank[0] << endl;
  return 0;
}
