#pragma once

#include <iostream>



// h ≤ logT((n+1) / 2)
// min grade factor
// T - 1 <= len(keys) <= 2T - 1
const int T = 3;

struct Node {
  int keyCount;
  bool isLeaf;
  std::string keys[2 * T - 1];
  uint64_t values[2 * T - 1];
  Node* children[2 * T];
};