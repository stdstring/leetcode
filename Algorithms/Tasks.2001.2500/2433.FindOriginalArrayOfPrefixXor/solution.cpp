#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findArray(std::vector<int> const &pref) const
    {
        std::vector<int> result(pref.size(), 0);
        result[0] = pref[0];
        for (size_t index = 1; index < pref.size(); ++index)
            result[index] = pref[index] ^ pref[index - 1];
        return result;
    }
};

}

namespace FindOriginalArrayOfPrefixXorTask
{

TEST(FindOriginalArrayOfPrefixXorTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({5, 7, 2, 3, 2}), solution.findArray({5, 2, 0, 3, 1}));
    ASSERT_EQ(std::vector<int>({13}), solution.findArray({13}));
}

}