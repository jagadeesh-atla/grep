#include <ctime>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <thread>

std::set<char> escape{'\\', '\"', '\'', '\n', '\t'};

// Function to escape special characters
char* escape_string(const char* str) {
  if (str == NULL) return NULL;

  // Calculate the new length considering the escape characters
  size_t len = strlen(str);
  size_t new_len = len;
  for (size_t i = 0; i < len; ++i) {
    if (escape.count(str[i])) {
      new_len++;
    }
  }

  // Allocate memory for the new escaped string
  char* escaped_str = (char*)malloc(new_len + 1);  // +1 for the null terminator
  if (!escaped_str) {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }

  // Build the escaped string
  size_t j = 0;
  for (size_t i = 0; i < len; ++i) {
    switch (str[i]) {
      case '\\':
        escaped_str[j++] = '\\';
        escaped_str[j++] = '\\';
        break;
      case '\"':
        escaped_str[j++] = '\\';
        escaped_str[j++] = '\"';
        break;
      case '\'':
        escaped_str[j++] = '\\';
        escaped_str[j++] = '\'';
        break;
      case '\n':
        escaped_str[j++] = '\\';
        escaped_str[j++] = 'n';
        break;
      case '\t':
        escaped_str[j++] = '\\';
        escaped_str[j++] = 't';
        break;
      default:
        escaped_str[j++] = str[i];
    }
  }
  escaped_str[j] = '\0';

  return escaped_str;
}

void PrintMatches2(std::string str, std::regex reg) {
  // This holds the first match
  std::sregex_iterator currentMatch(str.begin(), str.end(), reg);
  std::sregex_iterator lastMatch;

  while (currentMatch != lastMatch) {
    std::smatch match = *currentMatch;
    std::cout << match.str() << "\n";
    currentMatch++;
  }
  std::cout << std::endl;
}

void print(std::string str, std::regex reg) {
  std::smatch matches;

  while (std::regex_search(str, matches, reg)) {
    std::cout << matches.str(1) << "\n";
    str = matches.suffix().str();
  }

  std::cout << "\n";
}

int main(int argc, char* argv[]) {
  std::ifstream file("input.txt");
  std::string line;

  while (getline(file, line)) {
    std::string str = line;
    std::cout << str << std::endl;
    getline(file, line);
    std::cout << line << std::endl;
    std::regex reg(line);
    PrintMatches2(str, reg);
  }

  file.close();

  return 0;
}
