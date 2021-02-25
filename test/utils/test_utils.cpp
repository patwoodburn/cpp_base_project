#include "catch2/catch.hpp"

#include "utils.h"
#include <algorithm>
#include <array>

SCENARIO("Bubble sort does sort an unsorted array", "") {
  GIVEN("An an unsorted arry a1") {
    std::array<int, 10> a1 = {5, 10, 1, 2, 8, 3, 7, 9, 4, 6};

    WHEN("Array a1 is passed to bubble sort.") {
      BubbleSort(a1.begin(), a1.end());

      THEN("Array a1 should be sorted.") {
        REQUIRE(std::is_sorted(a1.begin(), a1.end()));
      }
    }
  }
}