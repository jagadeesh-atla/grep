#ifndef CMDLINE_PARSER_H_
#define CMDLINE_PARSER_H_

#include <getopt.h>

#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

#define BOYERMOORE_IMP_
#include "BoyerMoore.hpp"
#include "Color.hpp"
#include "re/Regex.hpp"

class CommandLineParser {
 public:
  CommandLineParser()
      : fixedStr_flag(0),
        ignoreCase_flag(0),
        invertMatch_flag(0),
        countLines_flag(0),
        withNoFilename_flag(0),
        prefixLine_flag(0),
        noIgnoreCase_flag(1),
        withFilename_flag(1),
        regex_flag(1) {}

  static void printUsage(std::string prg = "GREP");
  void parse(int argc, char** argv);
  void processFiles();

 private:
  int fixedStr_flag;
  int ignoreCase_flag;
  int invertMatch_flag;
  int countLines_flag;
  int withNoFilename_flag;
  int prefixLine_flag;
  int noIgnoreCase_flag;
  int withFilename_flag;
  int regex_flag;
  std::string pattern;
  std::vector<std::string> files;

  static struct option long_options[];

  void processStream(std::istream& in, const std::string& fileName);
};

#endif  // CMDLINE_PARSER_H_

#ifdef CMDLINE_PARSER_IMP_

struct option CommandLineParser::long_options[] = {
    {"fixed-string", required_argument, 0, 'F'},
    {"regexp", required_argument, 0, 'G'},
    {"no-ignore-case", no_argument, 0, 'I'},
    {"ignore-case", no_argument, 0, 'i'},
    {"invert-match", no_argument, 0, 'v'},
    {"count", no_argument, 0, 'c'},
    {"with-filename", no_argument, 0, 'H'},
    {"no-filename", no_argument, 0, 'h'},
    {"line-number", no_argument, 0, 'n'},
    {"help", no_argument, 0, '?'},
    {0, 0, 0, 0}};

void CommandLineParser::printUsage(std::string prg) {
  std::cout << "Usage: " << prg << " [options][file...] " << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -F, --fixed-string=STRING    Use fixed string matching"
            << std::endl;
  std::cout << "  -G, --regexp=PATTERN         Use regular expression matching "
               "(default)"
            << std::endl;
  std::cout << "  -i, --ignore-case            Ignore case distinctions"
            << std::endl;
  std::cout << "  -I, --no-ignore-case         Do not ignore case distinctions "
               "(default)"
            << std::endl;
  std::cout
      << "  -v, --invert-match           Invert the sense of matching, to "
         "select non-matching lines"
      << std::endl;
  std::cout
      << "  -c, --count                  Print only a count of matching lines "
         "per FILE"
      << std::endl;
  std::cout
      << "  -H, --with-filename          Print the file name for each match "
         "(default)"
      << std::endl;
  std::cout
      << "  -h, --no-filename            Suppress the file name prefix on "
         "output"
      << std::endl;
  std::cout
      << "  -n, --line-number            Prefix each line of output with the "
         "line number within its input file"
      << std::endl;
};

void CommandLineParser::parse(int argc, char** argv) {
  int c;

  while (true) {
    int option_idx = 0;
    c = getopt_long(argc, argv, "F:G:IivcHhn", long_options, &option_idx);
    if (c == -1) break;
    switch (c) {
      case 'F':
        fixedStr_flag = 1;
        regex_flag = 0;  // Ensure regexp is disabled
        pattern = optarg;
        break;

      case 'G':
        // if (fixedStr_flag) {
        //   std::cerr << "Error: Options -F and -G are mutually exclusive."
        //             << std::endl;
        //   exit(1);
        // }
        regex_flag = 1;
        pattern = optarg;
        break;

      case 'i':
        // if (noIgnoreCase_flag) {
        //   std::cerr << "Error: Options -i and --no-ignore-case are mutually "
        //                "exclusive."
        //             << std::endl;
        //   exit(1);
        // }
        ignoreCase_flag = 1;
        noIgnoreCase_flag = 0;
        break;

      case 'I':
        // if (ignoreCase_flag) {
        //   std::cerr << "Error: Options -i and --no-ignore-case are mutually "
        //                "exclusive."
        //             << std::endl;
        //   exit(1);
        // }
        noIgnoreCase_flag = 1;
        ignoreCase_flag = 0;
        break;

      case 'v':
        invertMatch_flag = 1;
        break;

      case 'c':
        countLines_flag = 1;
        break;

      case 'H':
        withFilename_flag = 1;
        withNoFilename_flag = 0;  // Ensure no-filename is disabled
        break;

      case 'h':
        withNoFilename_flag = 1;
        withFilename_flag = 0;  // Ensure with-filename is disabled
        break;

      case 'n':
        prefixLine_flag = 1;
        break;

      case '?':
        printUsage(argv[0]);
        exit(0);

      default:
        abort();
    }
  }

  // Store the remaining arguments (file names)
  for (int index = optind; index < argc; index++) {
    files.push_back(argv[index]);
  }
}

void CommandLineParser::processFiles() {
  for (const auto& file : files) {
    std::ifstream infile(file);
    if (!infile.is_open()) {
      std::cerr << "Error: Could not open file " << file << std::endl;
      continue;
    }
    processStream(infile, file);
  }
}

void CommandLineParser::processStream(std::istream& in,
                                      const std::string& filename) {
  std::string line;
  int line_number = 0;
  int match_count = 0;

  while (getline(in, line)) {
    line_number++;
    bool is_match = false;

    std::map<int, int> matches;

    if (fixedStr_flag) {
      BoyerMoore bm(pattern, ignoreCase_flag);
      matches = bm.findAllWithSize(line);
      is_match = !matches.empty();
    } else if (regex_flag) {
      // TODO: Need to implement case insensitive matching
      Regex* r = new Regex(pattern);
      r->compile();
      matches = r->matchAll(line);
      is_match = !matches.empty();
      // std::regex_constants::syntax_option_type syntax_options =
      //     std::regex_constants::ECMAScript;
      // if (ignoreCase_flag) {
      //   syntax_options |= std::regex_constants::icase;
      // }
      // std::regex re(pattern, syntax_options);
      // for (std::sregex_iterator it(line.begin(), line.end(), re), end;
      //      it != end; ++it) {
      //   matches[it->position()] = it->length();
      // }
      // is_match = regex_search(line, re);
    }

    if (invertMatch_flag) {
      is_match = !is_match;
    }

    if (is_match) {
      match_count++;
      if (!countLines_flag) {
        if (withFilename_flag && files.size() >= 1) {
          std::cout << filename << ":";
        }
        if (prefixLine_flag) {
          std::cout << line_number << ":";
        }
        // std::cout << colorMatches(line, match_positions) << std::endl;
        std::cout << COLOR::colorAll(matches, line, COLOR::RED, COLOR::BLUE)
                  << std::endl;
      }
    }
  }

  if (countLines_flag) {
    if (withFilename_flag && files.size() > 1) {
      std::cout << filename << ":";
    }
    std::cout << match_count << std::endl;
  }
}
#endif  // CMDLINE_PARSER_IMP_