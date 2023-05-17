#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findThePrefixCommonArray(std::vector<int> const &a, std::vector<int> const &b) const
    {
        std::vector<bool> appearedInA(a.size() + 1, false);
        std::vector<bool> appearedInB(b.size() + 1, false);
        int commonCount = 0;
        std::vector<int> result(a.size(), 0);
        for (size_t index = 0; index < a.size(); ++index)
        {
            appearedInA[a[index]] = true;
            appearedInB[b[index]] = true;
            if (appearedInA[b[index]])
                ++commonCount;
            if ((appearedInB[a[index]]) && (a[index] != b[index]))
                ++commonCount;
            result[index] = commonCount;
        }
        return result;
    }
};

}

namespace FindPrefixCommonArrayOfTwoArraysTask
{

TEST(FindPrefixCommonArrayOfTwoArraysTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 2, 3, 4}), solution.findThePrefixCommonArray({1, 3, 2, 4}, {3, 1, 2, 4}));
    ASSERT_EQ(std::vector<int>({0, 1, 3}), solution.findThePrefixCommonArray({2, 3, 1}, {3, 1, 2}));
}

}