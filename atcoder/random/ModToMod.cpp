#include <iostream>
using namespace std;

int main() {
  // 2^64 - 1e9+7 = 18446744072709551609
  // inverse of 998244353 = 996491785301655553
  // inverse of 9 = 10248191152060862009
  // inverse of 2 (mod 998244353) = 499122177
  // multiply by -1 = 18446744073709551615
  cout << "67\n";
  // First time:
  cout << "mul D A B\n";
  cout << "rem E D\n";
  cout << "mul F E 18446744073709551615\n";
  cout << "add G D F\n";
  cout << "mul H G 996491785301655553\n";
  cout << "mul I H 1000000007\n";
  cout << "add I I 1000000007\n";
  cout << "mul J D 18446744073709551615\n";
  cout << "add K I J\n";
  // Flip five more times:
  for (int i = 0; i < 5; ++i) {
    cout << "rem E K\n";
    cout << "mul F E 18446744073709551615\n";
    cout << "add G K F\n";
    cout << "mul H G 996491785301655553\n";
    cout << "mul I H 1000000007\n";
    cout << "add I I 1000000007\n";
    cout << "mul J K 18446744073709551615\n";
    cout << "add K I J\n";
  }
  // Last filter on K:
  cout << "add D K 18446744072709551609\n";
  cout << "rem E D\n";
  cout << "mul F E 18446744073709551615\n";
  cout << "add G D F\n";
  cout << "mul G G 996491785301655553\n";
  cout << "rem E G\n";
  cout << "mul F E 18446744073709551615\n";
  cout << "add G G F\n";
  cout << "mul G G 996491785301655553\n";
  cout << "mul G G 10248191152060862009\n";
  cout << "mul G G 499122177\n";
  cout << "rem G G\n";
  cout << "mul H G 18446744073709551615\n";
  cout << "add H H 1\n";
  cout << "mul J H 1000000007\n";
  cout << "mul J J 18446744073709551615\n";
  cout << "add K K J\n";
  // Port to C:
  cout << "mul C K 1\n";
  return 0;
}