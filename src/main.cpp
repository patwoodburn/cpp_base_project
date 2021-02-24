#include <algorithm>
#include <array>
#include <cstdlib>
#include <functional>
#include <iostream>

#include "inireader.h"
#include "inputparser.h"
#include "utils.h"

int main(int argc, char *argv[]) {
  InputParser::getInstance().add_values(argc, argv);

  std::cout << "Hello, world!" << std::endl;
  if (InputParser::getInstance().cmdOptionExists("--help")) {
    std::cout << "help menue";
  }
  std::string config_file;
  if (InputParser::getInstance().cmdOptionExists("-f")) {
    config_file = InputParser::getInstance().getCmdOption("-f");
  }

  // INIReader reader(config_file);
  std::cout << "load config:" << config_file << std::endl;
  std::cout << getApplicationConfig().GetString("section_1", "user_name",
                                                "UNKNOWN")
            << std::endl;
  std::cout << "after get from reader" << std::endl;

  std::array<int, 10> s = {5, 1, 3, 4, 2, 9, 8, 6, 0, 7};
  std::array<int, 10> s2 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::copy(s.begin(), s.end(), s2.begin());
  BubbleSort(s2.begin(), s2.end());
  for (const auto &n : s) {
    std::cout << n << ' ';
  }
  std::cout << std::endl;
  for (const auto &n : s2) {
    std::cout << n << ' ';
  }
  std::cout << std::endl;
  auto result = std::find(s.begin(), s.end(), 2);
  std::cout << result - s.begin();
  std::cout << std::endl;

  std::array<int, 10> s3 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  CopySort(s.begin(), s.end(), s3.begin(), BubbleSort);
  for (const auto &n : s3) {
    std::cout << n << ' ';
  }
  std::cout << std::endl;

  return 0;
}