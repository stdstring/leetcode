#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minDeletionSize(std::vector<std::string> const &strs) const
    {
        size_t columnsForDelete = 0;
        for (size_t column = 0; column < strs.front().size(); ++column)
        {
            if (!isOrdered(strs, column))
               ++columnsForDelete;
        }
        return static_cast<int>(columnsForDelete);
    }

private:
    [[nodiscard]] bool isOrdered(std::vector<std::string> const &strs, size_t column) const
    {
        for (size_t index = 1; index < strs.size(); ++index)
        {
            if (strs[index - 1][column] > strs[index][column])
                return false;
        }
        return true;
    }
};

}

namespace DeleteColumnsToMakeSortedTask
{

TEST(DeleteColumnsToMakeSortedTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minDeletionSize({"cba", "daf", "ghi"}));
    ASSERT_EQ(0, solution.minDeletionSize({"a", "b"}));
    ASSERT_EQ(3, solution.minDeletionSize({"zyx", "wvu", "tsr"}));
}

}