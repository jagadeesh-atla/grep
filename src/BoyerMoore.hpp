#ifndef BOYERMOORE_H_
#define BOYERMOORE_H_

#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::string toLowerCase(const std::string& input) {
  std::string result = input;
  std::transform(result.begin(), result.end(), result.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return result;
}

inline int max(int x, int y) { return x > y ? x : y; }

class BoyerMoore {
 private:
  const int R = 256;
  std::vector<int> right, border;
  std::string pat;
  bool caseInsensitive;
  int prevIdx = 0;
  void preprocessGoodSuffix();

 public:
  BoyerMoore(std::string& pat, bool caseInsensitive = false);
  int search(std::string& txt);
  inline int next(std::string& txt);
  std::vector<int> findAll(std::string& txt);
  void printAllMatches(std::string& txt);
  std::map<int, int> findAllWithSize(std::string& txt);
};

#endif  // BOYERMOORE_H_

#ifdef BOYERMOORE_IMP_

BoyerMoore::BoyerMoore(std::string& pattern, bool caseInsensitive)
    : pat(pattern), caseInsensitive(caseInsensitive) {
  if (caseInsensitive) {
    pat = toLowerCase(pat);
  }
  right.resize(R, -1);
  for (int j = 0; j < pat.length(); j++) right.at(pat.at(j)) = j;

  preprocessGoodSuffix();
}

void BoyerMoore::preprocessGoodSuffix() {
  int m = pat.length();
  border.resize(m + 1, 0);
  std::vector<int> shift(m + 1, 0);

  int i = m, j = m + 1;
  border.at(i) = j;

  while (i > 0) {
    while (j <= m && pat.at(i - 1) != pat.at(j - 1)) {
      if (shift.at(j) == 0) shift.at(j) = j - i;
      j = border.at(j);
    }

    --i, --j;
    border.at(i) = j;
  }

  j = border.front();
  for (i = 0; i <= m; i++) {
    if (shift.at(i) == 0) shift.at(i) = j;
    if (i == j) j = border.at(j);
  }

  for (int k = 0; k <= m; k++) border.at(k) = shift.at(k);
}

int BoyerMoore::search(std::string& txt) {
  if (caseInsensitive) {
    txt = toLowerCase(txt);
  }

  int m = pat.length();
  int n = txt.length();
  int skip = 0;

  for (int i = prevIdx; i <= n - m; i += skip) {
    skip = 0;
    for (int j = m - 1; j >= 0; j--) {
      if (pat.at(j) != txt.at(i + j)) {
        int bcSkip = max(1, j - right.at(txt.at(i + j)));
        int gsSkip = border.at(j + 1);
        skip = max(bcSkip, gsSkip);
        break;
      }
    }
    if (skip == 0) {
      prevIdx = i + 1;
      return i;
    }
  }

  prevIdx = n;
  return n;
}

inline int BoyerMoore::next(std::string& txt) {
  if (prevIdx == pat.length()) {
    prevIdx = 0;
    return prevIdx;
  }
  return search(txt);
}

std::vector<int> BoyerMoore::findAll(std::string& txt) {
  int offset = search(txt);

  std::vector<int> matches;

  while (offset < txt.length()) {
    matches.push_back(offset);
    offset = next(txt);
  }
  prevIdx = 0;

  return matches;
}

std::map<int, int> BoyerMoore::findAllWithSize(std::string& txt) {
  auto idxs = findAll(txt);
  std::map<int, int> mp;
  for (auto idx : idxs) mp[idx] = pat.size();
  return mp;
}

inline void BoyerMoore::printAllMatches(std::string& txt) {
  auto idxs = findAll(txt);
  std::cout << "text:   " << txt << std::endl;
  for (int offset : idxs) {
    std::cout << "pattern:";
    for (int i = 0; i < offset; i++) std::cout << " ";
    std::cout << pat << std::endl;
  }

  std::cout << idxs.size() << " matches found!" << std::endl;
}

#endif  // BOYERMOORE_IMP_
