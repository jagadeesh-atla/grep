#include <iostream>
#include <string>

#define BOYERMOORE_IMP_
#include "BoyerMoore.hpp"
#include "Color.hpp"

int main(void) {
  std::string txt;
  std::string pat;

  std::cin >> pat >> txt;

  BoyerMoore* bm = new BoyerMoore(pat);

  auto idxs = bm->findAll(txt);

  for (int offset : idxs) {
    std::cout << "        "
              << COLOR::colorAt(offset, offset + pat.size(), COLOR::RED, txt)
              << std::endl;
  }

  // std::cout << "text:   " << txt << std::endl;
  // for (int offset : idxs) {
  //   std::cout << "pattern:";
  //   for (int i = 0; i < offset; i++) std::cout << " ";
  //   std::cout << pat << std::endl;
  // }

  std::cout << idxs.size() << " matches found!" << std::endl;

  return 0;
}
