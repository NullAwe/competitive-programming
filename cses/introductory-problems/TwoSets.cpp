#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  if (n % 4 == 1 || n % 4 == 2) {
    // Output if it is impossible:
    cout << "NO" << endl;
    return 0;
  }
  // Output if it is possible:
  cout << "YES" << endl;
  if (n % 4 == 3) {
    cout << n / 2 << endl;
    cout << "3 ";
    for (int i = 1; i < n / 2; i += 2) cout << 3 + (i + 1) / 2 << " " << n - (i + 1) / 2 + 1 << " ";
    cout << endl;
    cout << n / 2 + 1 << endl;
    cout << "1 2 ";
    for (int i = 2; i < n / 2 + 1; i += 2) cout << 3 + n / 4 + i / 2 << " " << n - n / 4 - i / 2 + 1 << " ";
    cout << endl;
    return 0;
  }
  cout << n / 2 << endl;
  for (int i = 0; i < n / 2; i += 2) cout << i / 2 + 1 << " " << n - i / 2 << " ";
  cout << endl;
  cout << n / 2 << endl;
  for (int i = 0; i < n / 2; i += 2) cout << n / 4 + i / 2 + 1 << " " << n - n / 4 - i / 2 << " ";
  cout << endl;
  return 0;
}
