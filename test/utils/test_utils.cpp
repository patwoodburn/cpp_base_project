#include "catch2/catch.hpp"

#include "utils.h"
#include <algorithm>
#include <array>

SCENARIO("An array of values needs to be sorted", "") {
  GIVEN("An an unsorted arry a1") {
    std::array<int, 10> a1 = {5, 10, 1, 2, 8, 3, 7, 9, 4, 6};

    WHEN("Array a1 is passed to bubble sort.") {
      BubbleSort(a1.begin(), a1.end());

      THEN("Array a1 should be sorted.") {
        REQUIRE(std::is_sorted(a1.begin(), a1.end()));
        REQUIRE(a1.size() == 10);
        REQUIRE(a1[0] == 1);
        REQUIRE(a1[1] == 2);
        REQUIRE(a1[2] == 3);
        REQUIRE(a1[3] == 4);
        REQUIRE(a1[4] == 5);
        REQUIRE(a1[5] == 6);
        REQUIRE(a1[6] == 7);
        REQUIRE(a1[7] == 8);
        REQUIRE(a1[8] == 9);
        REQUIRE(a1[9] == 10);
      }
    }
  }
}

SCENARIO("An array of values need to be sorted with out changing the order of "
         "the orriganal array",
         "") {
  GIVEN("An unsorted array a1 and an empty target array a2") {
    std::array<int, 10> a1 = {10, 1, 5, 6, 8, 7, 0, 2, 3, 9};
    std::array<int, 10> a2;

    WHEN("Array a1 and a2 and a sort function are passed to copy sort") {
      CopySort(a1.begin(), a1.end(), a2.begin(), BubbleSort);

      THEN("a2 should be sorted copy of a1 and a1 should be unchanged") {
        REQUIRE(!std::is_sorted(a1.begin(), a1.end()));
        REQUIRE(std::is_sorted(a2.begin(), a2.end()));
        REQUIRE(a1.size() == 10);
        REQUIRE(a2.size() == 10);

        for (int i : a1) {
          REQUIRE(a2.end() != std::find(a2.begin(), a2.end(), i));
        }
      }
    }
  }
}