#include <iostream>
using namespace std;

#define ll long long

int main() {
  ll x; cin >> x;
  cout << x - (x / 2 + x / 3 + x / 5 + x / 7 - x / 6 - x / 10 - x / 14 - x / 15 - x / 21 - x / 35 + x / 30 + x / 42 + x / 70 + x / 105 - x / 210) << '\n';
  return 0;
}
