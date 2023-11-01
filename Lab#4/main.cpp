#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

struct Vertex {

 public:
  std::map<const char, int> links;
  int parent = -1;
  int suffix_link = -1;
  int end_word_link = -1;
  int leafNumber = -1;
  char parent_char;
  bool leaf = false;

 public:

  bool isLeaf() const {
    return leafNumber != -1;
  }

  bool CheckKey(const char &key) {
    return links.find(key) != links.end();
  }

};

class Aho {

 private:
  const int ROOT_INDEX = 0;
  std::vector<Vertex> trie;
  std::vector<int> wordsLen;
  int size;
  int wordID;

 public:

  Aho() : trie{}, wordsLen{}, size{0}, wordID{0} {
    trie.emplace_back();
    ++size;
  }

  void AddString(const std::string &str) {
    int currVertex = ROOT_INDEX;
    for (auto &i : str) {
      if (!trie[currVertex].CheckKey(i)) {
        trie.emplace_back();
        trie[size].parent = currVertex;
        trie[size].parent_char = i;
        trie[currVertex].links[i] = size;
        ++size;
      }
      currVertex = trie[currVertex].links[i];
    }
    trie[currVertex].leaf = true;
    trie[currVertex].leafNumber = wordID;
    wordsLen.push_back(str.size());

    ++wordID;
  }

  void prepare() {
    std::queue<int> vertexQueue{};
    vertexQueue.push(ROOT_INDEX);

    while (!vertexQueue.empty()) {
      int curVertex = vertexQueue.front();
      vertexQueue.pop();

      CalcSuffLink(curVertex);

      for (const auto &child : trie[curVertex].links)
        vertexQueue.push(child.second);
    }
  }

  int process(const std::string &text) {
    int currentState = ROOT_INDEX;
    int result = 0;

    for (int j(0); j < text.size(); ++j) {
      while (true) {
        char symbol = text[j];
        if (trie[currentState].CheckKey(symbol)) {
          currentState = trie[currentState].links[symbol];
          break;
        }

        if (currentState == ROOT_INDEX) break;
        currentState = trie[currentState].suffix_link;
      }

      int checkState = currentState;
      while (true) {
        checkState = trie[checkState].end_word_link;

        if (checkState == ROOT_INDEX) break;

        result++;
        int indexOfMatch = j + 1 - wordsLen[trie[checkState].leafNumber];

        std::cout << "There was a match at index " << indexOfMatch << ": ";
        std::cout << text.substr(indexOfMatch, wordsLen[trie[checkState].leafNumber]) << std::endl;

        // Trying to find all matched patterns of smaller length
        checkState = trie[checkState].suffix_link;
      }
    }

    return result;
  }

 private:

  void CalcSuffLink(int vertex) {
    // Processing ROOT_INDEX (empty string)
    if (vertex == ROOT_INDEX) {
      trie[vertex].suffix_link = ROOT_INDEX;
      trie[vertex].end_word_link = ROOT_INDEX;
      return;
    }

    // Processing children of the ROOT_INDEX (one character substrings)
    if (trie[vertex].parent == ROOT_INDEX) {
      trie[vertex].suffix_link = ROOT_INDEX;

      if (trie[vertex].leaf) trie[vertex].end_word_link = vertex;
      else trie[vertex].end_word_link = trie[trie[vertex].suffix_link].end_word_link;

      return;
    }

    // Cases above are degenerate cases as for prefix function calculation; the
    // value is always 0 and links to the ROOT_INDEX vertex.

    // To calculate the suffix link for the current vertex, we need the suffix
    // link for the parent of the vertex and the character that moved us to the
    // current vertex.

    int curBetterVertex = trie[trie[vertex].parent].suffix_link;
    char chVertex = trie[vertex].parent_char;

    // From this vertex and its substring we will start to look for the maximum
    // prefix for the current vertex and its substring.

    while (true) {
      // If there is an edge with the needed char, we update our suffix link
      // and leave the cycle
      if (trie[curBetterVertex].links.find(chVertex) != trie[curBetterVertex].links.end()) {
        trie[vertex].suffix_link = trie[curBetterVertex].links[chVertex];
        break;
      }

      // Otherwise, we are jumping by suffix links until we reach the ROOT_INDEX
      // (equivalent of k == 0 in prefix function calculation) or we find a
      // better prefix for the current substring.
      if (curBetterVertex == ROOT_INDEX) {
        trie[vertex].suffix_link = ROOT_INDEX;
        break;
      }

      curBetterVertex = trie[curBetterVertex].suffix_link; // Go back by sufflink
    }

    // When we complete the calculation of the suffix link for the current
    // vertex, we should update the link to the end of the maximum length word
    // that can be produced from the current substring.
    if (trie[vertex].leaf) trie[vertex].end_word_link = vertex;
    else trie[vertex].end_word_link = trie[trie[vertex].suffix_link].end_word_link;
  }

};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Aho ak;

  {
    std::string pattern;
    while (getline(std::cin, pattern) && !pattern.empty()) {
      std::transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);
      ak.AddString(pattern);
    }
    ak.prepare();
  }

  std::vector<std::string> text;

  {
    std::string line;
    while (getline(std::cin, line)) {
      text.push_back(line);
    }
  }

  for (auto &line : text) {
    int matches = ak.process(line);
    std::cout << matches << " ";
  }
}



