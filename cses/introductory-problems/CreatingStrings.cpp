#include <bits/stdc++.h>
using namespace std;

vector<string> getCombos(vector<int> letters) {
  vector<string> combos;
  for (int i = 0; i < 26; ++i) {
    if (letters[i] == 0) continue;
    // Finds all combinations starting with this letter:
    --letters[i];
    vector<string> next = getCombos(letters);
    ++letters[i];
    for (string str : next) {
      str = (char) (i + 'a') + str;
      combos.push_back(str);
    }
    if (next.empty()) combos.push_back(string(1, (char) (i + 'a')));
  }
  return combos;
}

int main() {
  string str; cin >> str;
  vector<int> letters(26);
  for (int i = 0; i < str.size(); ++i) ++letters[str[i] - 'a'];
  vector<string> combos = getCombos(letters);
  // Output:
  cout << combos.size() << endl;
  for (string str : combos) cout << str << endl;
  return 0;
}
