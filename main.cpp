#include <iostream>

#define CMDLINE_PARSER_IMP_
#include "CmdLineParser.hpp"

int main(int argc, char** argv) {
  if (argc == 1) {
    CommandLineParser::printUsage(argv[0]);
    return 1;
  }

  CommandLineParser parser;
  parser.parse(argc, argv);

  parser.processFiles();

  return 0;
}