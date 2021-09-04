#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct Node {
  pair<Node*, Node*> children;
};

struct Trie {

  Node* head = new Node;

  void addNode(ll num) {
    Node* cur = head;
    for (int i = 39; i >= 0; --i) {
      int ind = (int) ((num >> i) & 1);
      if (ind == 0) {
        if (cur->children.first == nullptr) cur->children.first = new Node;
        cur = cur->children.first;
      } else {
        if (cur->children.second == nullptr) cur->children.second = new Node;
        cur = cur->children.second;
      }
    }
  }

  ll getComplement(ll num) {
    ll ans = 0;
    Node* cur = head;
    for (int i = 39; i >= 0; i--) {
      int opp = 1 - (int) ((num >> i & 1));
      Node* child = opp == 0 ? cur->children.first : cur->children.second;
      int n = child == nullptr ? 1 - opp : opp;
      ans = ans * 2 + n;
      cur = n == 0 ? cur->children.first : cur->children.second;
    }
    return ans;
  }
};

int main() {
  int n; cin >> n;
  vector<ll> sausage(n); for (int i = 0; i < n; ++i) cin >> sausage[i];
  ll ans = 0, prefXOR = 0, postXOR = 0;
  for (int i = 0; i < n; ++i) prefXOR ^= sausage[i];
  Trie trie;
  trie.addNode(postXOR);
  // Iterates through all possible prefixes:
  for (int i = n - 1; i >= 0; i--) {
    prefXOR ^= sausage[i];
    postXOR ^= sausage[i];
    trie.addNode(postXOR);
    // Finds the corresponding postfix that maximizes the XOR:
    ans = max(ans, prefXOR ^ trie.getComplement(prefXOR));
  }
  // Output:
  cout << ans << endl;
  return 0;
}
