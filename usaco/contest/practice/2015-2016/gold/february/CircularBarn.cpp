#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll sq(ll x) { return x * x; }

int main() {
  ifstream in("cbarn.in");
  ofstream out("cbarn.out");
  int n; in >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) in >> arr[i];
  // Finds the starting point (where the first cow in the first room goes):
  int ind = 0, sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += arr[i];
    ind = max(ind, i + 1 - sum);
  }
  // Finds the answer:
  int curInd = 0;
  ll ans = 0;
  for (int i = ind; i < ind + n; ++i) {
    while (arr[curInd] == 0) ++curInd;
    --arr[curInd];
    ans += sq(i - curInd);
  }
  // Output:
  out << ans << endl;
}
