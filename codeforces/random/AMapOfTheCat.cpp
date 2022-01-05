#include <bits/stdc++.h>
using namespace std;

int main() {
  for (int i = 0; i < 10; ++i) {
    cout << i << endl;
    string str; getline(cin, str);
    if (str == "no") continue;
    // Output:
    if (str == "don't think so" || str == "don't touch me" || str == "not bad" ||
            str == "cool" || str == "great") cout << "normal" << endl;
    else cout << "grumpy" << endl;
    return 0;
  }
}
