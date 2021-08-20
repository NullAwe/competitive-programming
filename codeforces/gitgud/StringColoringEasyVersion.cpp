#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  string str; cin >> str;
  // Desired final product:
  string copy = str; sort(copy.begin(), copy.end());
  // Finds sequence (or if sequence is impossible, output "NO"):
  int ind = n - 1;
  vector<char> avail;
  vector<int> colors(n);
  for (int i = n - 1; i >= 0; --i) {
    // Characters match:
    if (str[i] == copy[ind]) {
      --ind;
      colors[i] = 1;
    } else {
      // Put it in the unmatched characters list:
      avail.insert(avail.begin(), str[i]);
      // If the unmatched characters list (order can't change) is out of order, answer is "NO":
      if (avail.size() > 1 && avail[0] > avail[1]) {
        cout << "NO" << endl;
        return 0;
      }
    }
    // Checks if any of the characters in the unmatched characters list now match:
    while (!avail.empty() && avail[avail.size() - 1] == copy[ind]) {
      --ind;
      avail.resize(avail.size() - 1);
    }
  }
  // Output:
  cout << "YES" << endl;
  for (int color : colors) cout << color;
  cout << endl;
  return 0;
}
