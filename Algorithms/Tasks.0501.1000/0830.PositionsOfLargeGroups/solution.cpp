#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> largeGroupPositions(std::string const &s) const
    {
        constexpr size_t largeGroupMinSize = 3;
        std::vector<std::vector<int>> groups;
        char groupChar = s[0];
        size_t groupStart = 0;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (groupChar != s[index])
            {
                if ((index - groupStart) >= largeGroupMinSize)
                    groups.emplace_back(std::vector<int>({static_cast<int>(groupStart), static_cast<int>(index - 1)}));
                groupChar = s[index];
                groupStart = index;
            }
        }
        if ((s.size() - groupStart) >= largeGroupMinSize)
            groups.emplace_back(std::vector<int>({static_cast<int>(groupStart), static_cast<int>(s.size() - 1)}));
        return groups;
    }
};

}

namespace PositionsOfLargeGroupsTask
{

TEST(PositionsOfLargeGroupsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{3, 6}}), solution.largeGroupPositions("abbxxxxzzy"));
    ASSERT_EQ(std::vector<std::vector<int>>(), solution.largeGroupPositions("abc"));
    ASSERT_EQ(std::vector<std::vector<int>>({{3, 5}, {6, 9}, {12, 14}}), solution.largeGroupPositions("abcdddeeeeaabbbcd"));
    ASSERT_EQ(std::vector<std::vector<int>>(), solution.largeGroupPositions("aba"));
}

}