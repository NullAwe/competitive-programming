#include <iostream>
using namespace std;

#define ll long long

int main() {
  ll x; cin >> x;
  x = (-((x % 360 + 360) % 360) + 360) % 360;
  ll ans = LLONG_MAX, turns;
  for (int i = 0; i < 4; ++i) {
    ll turned = (x + 90 * i) % 360, comp = min(turned, 360 - turned);
    if (comp < ans) ans = comp, turns = i;
  }
  cout << turns << '\n';
}
