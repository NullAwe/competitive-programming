#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<bool> vowels(26);
  vowels[0] = vowels[4] = vowels[8] = vowels[14] = vowels[20] = true;
  int t; cin >> t;
  for (int i = 1; i <= t; ++i) {
    string str; cin >> str;
    int m = INT_MAX;
    // Checks number of operations to make string consistent with all possible consistent strings:
    for (int j = 0; j < 26; ++j) {
      int secs = 0;
      for (int k = 0; k < str.size(); ++k) {
        int id = str[k] - 'A';
        if (id == j) continue;
        ++secs;
        if (vowels[id] == vowels[j]) ++secs;
      }
      m = min(m, secs);
    }
    // Output:
    cout << "Case #" << i << ": " << m << endl;
  }
  return 0;
}
