#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k; cin >> n >> k;
  string str; cin >> str;
  // Takes care of the special case where no beautiful string is possible:
  if (n % k > 0) {
    cout << -1 << endl;
    return;
  }
  // Binary searches for the most characters that can match the string (prefix):
  int lo = 0, hi = n + 1;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    vector<int> letters(26);
    for (int i = 0; i < mid; ++i) ++letters[str[i] - 'a'];
    int sum = 0;
    for (int letter : letters) sum += (k - letter % k) % k;
    if (sum > n - mid) hi = mid;
    else {
      // Checks if we can have (mid) amount of characters matching the string prefix:
      bool done = false, possible = true;
      // Makes the largest possible string out of the remaining characters and compares it with the suffix:
      for (int i = mid; i < n - sum; ++i) {
        if (str[i] < 'z') {
          done = true;
          break;
        }
      }
      for (int i = n - sum; i < n; ++i) {
        if (done || !possible) break;
        for (int j = 25; j >= str[i] - 'a'; --j) {
          if (letters[j] % k > 0) {
            ++letters[j];
            if (j > str[i] - 'a') done = true;
            break;
          } else if (j == str[i] - 'a') possible = false;
        }
      }
      if (possible) lo = mid;
      else hi = mid;
    }
  }
  // Outputs the matching prefix:
  for (int i = 0; i < lo; ++i) cout << str[i];
  // Takes care of the special case where the prefix is the entire string:
  if (lo == n) {
    cout << endl;
    return;
  }
  // Finds the smallest suffix made to satisfy the problem constraints:
  vector<int> letters(26);
  for (int i = 0; i < lo; ++i) ++letters[str[i] - 'a'];
  int sum = 0;
  for (int letter : letters) sum += (k - letter % k) % k;
  int spare = (n - sum - lo) / k;
  if (spare) {
    // Outputs the next character:
    cout << (char) (str[lo] + 1);
    ++letters[str[lo] - 'a' + 1];
    if (letters[str[lo] - 'a' + 1] % k == 1) --spare;
    for (int i = 0; i < k * spare; ++i) cout << 'a';
  } else {
    for (int i = str[lo] - 'a' + 1; i < 26; ++i) {
      if (letters[i] % k > 0) {
        // Outputs the next character:
        cout << (char) (i + 'a');
        ++letters[i];
        break;
      }
    }
  }
  // Remaining output:
  for (int i = 0; i < 26; ++i) for (int j = letters[i]; j % k > 0; ++j) cout << (char) (i + 'a');
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
