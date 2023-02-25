#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minDeletionSize(std::vector<std::string> const &strs) const
    {
        std::vector<size_t> columns;
        columns.reserve(strs.front().size());
        for (size_t column = 0; column < strs.front().size(); ++column)
        {
            columns.push_back(column);
            if (!isOrdered(strs, columns))
                columns.pop_back();
        }
        return static_cast<int>(strs.front().size() - columns.size());
    }

private:
    [[nodiscard]] bool isOrdered(std::string const &left, std::string const &right, std::vector<size_t> const &columns) const
    {
        for (const size_t column : columns)
        {
            if (left[column] > right[column])
                return false;
            if (left[column] < right[column])
                return true;
        }
        return true;
    }

    [[nodiscard]] bool isOrdered(std::vector<std::string> const &strs, std::vector<size_t> const &columns) const
    {
        for (size_t index = 1; index < strs.size(); ++index)
        {
            if (!isOrdered(strs[index - 1], strs[index], columns))
                return false;
        }
        return true;
    }
};

}

namespace DeleteColumnsToMakeSortedIITask
{

TEST(DeleteColumnsToMakeSortedIITaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minDeletionSize({"ca", "bb", "ac"}));
    ASSERT_EQ(0, solution.minDeletionSize({"xc", "yb", "za"}));
    ASSERT_EQ(3, solution.minDeletionSize({"zyx", "wvu", "tsr"}));
}

}