#include <bits/stdc++.h>
using namespace std;

int main() {
  string str; cin >> str;
  vector<int> d(26);
  for (int i = 0; i < str.size(); ++i) ++d[str[i] - 'A'];
  int odds = 0;
  for (int num : d) if (num % 2 == 1) ++odds;
  // Outputs if we cannot create a palindrome:
  if (odds > 1) {
    cout << "NO SOLUTION" << endl;
    return 0;
  }
  string half = "";
  char middle = ' ';
  for (int i = 0; i < d.size(); ++i) {
    for (int j = 0; j < d[i] / 2; ++j) half += (char) (i + 'A');
    if (d[i] % 2 == 1) middle = (char) (i + 'A');
  }
  // Output:
  cout << half;
  for (int i = 0; i < half.size() / 2; ++i) {
    char tmp = half[i];
    half[i] = half[half.size() - i - 1];
    half[half.size() - i - 1] = tmp;
  }
  if (middle != ' ') cout << middle;
  cout << half << endl;
  return 0;
}
