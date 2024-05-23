#include <iostream>
#include <string>

#define BOYERMOORE_IMP_
#include "BoyerMoore.hpp"

int main(void) {
  std::string txt;
  std::string pat;

  std::cin >> pat >> txt;

  BoyerMoore* bm = new BoyerMoore(pat);
  bm->printAllMatches(txt);

  return 0;
}