#include "Set.h"

#include <vector>
#include "gtest/gtest.h"

TEST(UNIT_HASHSET, TestConstructDefault) {
    Set<int> numbers{};
    EXPECT_EQ(numbers.size(), 0);
    EXPECT_TRUE(numbers.empty());
}

TEST(UNIT_HASHSET, TestInitializerList) {
    Set<int> numbers = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(numbers.size(), 5);
}

TEST(UNIT_HASHSET, TestConstructIterator) {
    std::vector<int> elems = {1, 2, 3, 4, 5, 6, 7};
    Set<int> numbers{elems.begin(), elems.end()};
    for (int n : elems){
        EXPECT_TRUE(numbers.contains(n));
    }
}