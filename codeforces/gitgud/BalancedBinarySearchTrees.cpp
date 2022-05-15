#include <iostream>
using namespace std;

int main() {
  int n; cin >> n;
  int check = 1, last = 0;
  for (int j = 1; j <= 25; ++j) {
    check += (1 << j);
    if (last + 3 > n) {
      cout << "1\n";
      return 0;
    }
    last = check + (check - last - 3);
    if (last >= n) {
      cout << "0\n";
      return 0;
    }
  }
  cout << "1\n";
  return 0;
}
