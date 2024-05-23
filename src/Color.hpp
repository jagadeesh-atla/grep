#ifndef COLOR_H_
#define COLOR_H_

#include <algorithm>
#include <set>
#include <string>

namespace COLOR {
typedef const char* Color;

Color BLACK = "\e[0;30m";
Color RED = "\e[0;31m";
Color GREEN = "\e[0;32m";
Color YELLOW = "\e[0;33m";
Color BLUE = "\e[0;34m";
Color MAGENTA = "\e[0;35m";
Color CYAN = "\e[0;36m";
Color WHITE = "\e[0;35m";

Color BRIGHT_BLACK = "\e[0;90m";
Color BRIGHT_RED = "\e[0;91m";
Color BRIGHT_GREEN = "\e[0;92m";
Color BRIGHT_YELLOW = "\e[0;93m";
Color BRIGHT_BLUE = "\e[0;94m";
Color BRIGHT_MAGENTA = "\e[0;95m";
Color BRIGHT_CYAN = "\e[0;96m";
Color BRIGHT_WHITE = "\e[0;95m";

Color END = "\e[0m";

inline std::string color(Color with, const std::string& str) {
  return with + str + "\e[0m";
}

// color the string [from, to) by COLOR::with
std::string colorAt(int from, int to, Color with, const std::string& str) {
  if (to <= from || from >= str.length()) return str;
  if (to > str.length()) to = str.length();

  std::string colrd;
  colrd.reserve(str.length() + 11);

  colrd.append(str.substr(0, from));
  colrd.append(color(with, str.substr(from, to - from)));
  colrd.append(str.substr(to));

  return colrd;
}

std::string colorAll(std::map<int, int>& idxs, const std::string& str,
                     Color color1, Color color2) {
  if (idxs.empty() || str.empty()) return str;

  std::string nstr;

  bool clr = false;
  for (int i = 0; i < str.length(); i++) {
    if (idxs.count(i)) {
      nstr.append(color((clr ? color1 : color2), str.substr(i, idxs[i])));
      i += idxs[i] - 1;

      clr = !clr;
    } else {
      nstr.push_back(str[i]);
    }
  }

  return nstr;
}

};  // namespace COLOR

#endif  // COLOR_H_
