#include <bits/stdc++.h>
using namespace std;

int getSwaps(string& str, int one, int two, vector<int>& d) {
  if (d[one] == 0 || d[two] == 0) return INT_MAX;
  // Checks a special case where number is already valid:
  if (str[str.size() - 1] - '0' == two && str[str.size() - 2] - '0' == one) return 0;
  // Finds the two indices for the two digits closest to the end of the string:
  int ind1 = -1, ind2 = -1;
  for (int i = str.size() - 1; i >= 0; --i) {
    if (str[i] == (char) (one + '0') && ind1 < 0) {
      ind1 = i;
    } else if (str[i] == (char) (two + '0') && ind2 < 0) {
      ind2 = i;
    }
  }
  // Finds one index closest to the front of the string in case it must be moved to prevent leading zeroes:
  int saveInd = -1;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] != '0' && i != ind1 && i != ind2) {
      saveInd = i;
      break;
    }
  }
  // Calculates total number of swaps:
  int swaps = 0;
  if ((ind1 == 0 || ind2 == 0) && d[0] > 0) {
    if (saveInd < 0) return INT_MAX;
    swaps += saveInd;
    if (saveInd > ind1) --swaps;
    if (saveInd > ind2) --swaps;
  }
  swaps += str.size() - 1 - ind2;
  swaps += str.size() - 2 - ind1;
  if (ind1 > ind2) ++swaps;
  return swaps;
}

int main() {
  string str; cin >> str;
  vector<int> d(10);
  for (int i = 0; i < str.size(); ++i) ++d[str[i] - '0'];
  int ans = INT_MAX;
  // Finds minimum swaps to reach a number ending with (00):
  if (d[0] > 1) {
    int swaps = 0;
    bool doneFirst = false;
    for (int i = str.size() - 1; i >= 0; --i) {
      if (str[i] == '0') {
        if (!doneFirst) {
          swaps += str.size() - 1 - i;
          doneFirst = true;
        } else {
          swaps += str.size() - 2 - i;
          break;
        }
      }
    }
    ans = min(ans, swaps);
  }
  // Finds answer, which is the minimum between current ans and minimum swaps to reach a number ending in
  // (25), (50), or (75):
  ans = min(ans, min(getSwaps(str, 2, 5, d), min(getSwaps(str, 5, 0, d), getSwaps(str, 7, 5, d))));
  // Output:
  cout << (ans == INT_MAX ? -1 : ans) << endl;
  return 0;
}
