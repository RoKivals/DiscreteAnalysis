#include <map>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <queue>

typedef std::string TLetter;

struct Vertex {
  std::map<TLetter, Vertex *> links;
  Vertex *sufflink = nullptr;
  std::vector<int> success; //pattern id

  bool CheckKey(const std::string &key) {
    return links.find(key) != links.end();
  }
};

class AhoTrie {
  Vertex *root;
  int patternSize;
  int pieces;

 public:
  std::vector<int> pieceIndex;

  AhoTrie() : patternSize(0), pieces(0) {
    root = new Vertex;
    root->sufflink = root;
  }

  Vertex *Move(Vertex *item, TLetter letter) {
    if (item->CheckKey(letter)) item = item->links.at(letter);
    else {
      if (item == root)
        item = root;
      else
        item = Move(item->sufflink, letter);
    }
    return item;
  }

  Vertex *Next(Vertex *item, TLetter letter) {

    if (!item)
      return nullptr;
    try {
      item = item->links.at(letter);
    } catch (std::out_of_range &) {
      item = nullptr;
    }
    return item;
  }

  void Linkate() {

    Vertex *node, *child;
    std::queue<Vertex *> queue;
    queue.push(root);
    while (!queue.empty()) {
      node = queue.front();
      queue.pop();
      std::map<TLetter, Vertex *>::iterator childPairIt;
      for (childPairIt = node->links.begin(); childPairIt != node->links.end();
           ++childPairIt) {
        child = childPairIt->second;
        queue.push(child);
        child->sufflink = FindSufflink(child, node, childPairIt->first);

        child->success.insert(child->success.end(),
                              child->sufflink->success.begin(),
                              child->sufflink->success.end());

        child->success.shrink_to_fit();
      }
    }
  }

  Vertex *FindSufflink(Vertex *child, Vertex *parent,
                       const TLetter letter) {
    Vertex *linkup = parent->sufflink, *check;
    while (true) {
      check = Next(linkup, letter);
      if (check)
        return (check != child) ? check : root;
      if (linkup == root)
        return root;
      linkup = linkup->sufflink;

    }
  }

  void Push(const std::vector<TLetter> &str) {

    Vertex *bohr = root, *next;
    for (size_t i = 0; i < str.size(); ++i) {
      next = Next(bohr, str[i]);
      if (!next) {
        next = new Vertex;
        next->sufflink = root;
        bohr->links.insert(std::pair<TLetter, Vertex *>(str[i], next));
      }
      bohr = next;
    }
    bohr->success.push_back(pieces);
    pieces++;
  }
  void Search(std::vector<TLetter> &text,
              std::vector<std::pair<int, int> > &grid) {

    Linkate();
    int m = text.size();
    Vertex *node = root;
    int occurrence;
    int c;
    for (c = 0; c < m; ++c) {

      for (size_t i = 0; i < node->success.size(); ++i) {
        occurrence = c - pieceIndex[node->success[i]];
        std::cout << grid[occurrence].first << ", " << grid[occurrence].second << ", " << node->success[i] + 1
                  << std::endl;
      }

      node = Move(node, text[c]);

    }

    for (size_t i = 0; i < node->success.size(); ++i) {
      occurrence = c - pieceIndex[node->success[i]];
      std::cout << grid[occurrence].first << ", " << grid[occurrence].second << ", " << node->success[i] + 1
                << std::endl;
    }
  }

};

int main() {
  std::vector<std::pair<int, int> > grid;
  std::vector<TLetter> input;
  std::vector<TLetter> patterns;
  std::string line, word;
  TLetter pattern;
  AhoTrie b;
  int index = 0;
  while (std::getline(std::cin, pattern) && !pattern.empty()) {
    std::stringstream AlineStream(pattern);
    while (AlineStream >> word) {
      for (unsigned int i = 0; i < word.length(); ++i) {
        word[i] = tolower(word[i]);
      }

      patterns.push_back(word);
      index++;
    }

    b.Push(patterns);
    b.pieceIndex.push_back(index);

    index = 0;
    pattern.clear();
    patterns.clear();

  }

  int lineIndex = 1, wordIndex = 1;

  while (std::getline(std::cin, line)) {
    std::stringstream lineStream(line);
    while (lineStream >> word) {
      for (unsigned int i = 0; i < word.length(); ++i) {
        word[i] = tolower(word[i]);
      }
      input.push_back(word);
      grid.push_back(std::make_pair(lineIndex, wordIndex));
      wordIndex++;
    }

    wordIndex = 1;
    lineIndex++;

  }
  input.shrink_to_fit();
  grid.shrink_to_fit();
  b.Search(input, grid);
  return 0;
}