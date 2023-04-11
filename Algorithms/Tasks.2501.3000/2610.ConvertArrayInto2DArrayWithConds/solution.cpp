#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> findMatrix(std::vector<int> const &nums) const
    {
        std::vector<std::unordered_set<int>> rows;
        std::vector<std::vector<int>> result;
        for (const int number : nums)
            appendToNearestRow(rows, result, number);
        return result;
    }

private:
    void appendToNearestRow(std::vector<std::unordered_set<int>> &rows, std::vector<std::vector<int>> &result, int number) const
    {
        for (size_t index = 0; index < rows.size(); ++index)
        {
            if (rows[index].count(number) == 0)
            {
                rows[index].insert(number);
                result[index].emplace_back(number);
                return;
            }
        }
        rows.emplace_back();
        result.emplace_back();
        rows.back().insert(number);
        result.back().emplace_back(number);
    }
};

}

namespace ConvertArrayInto2DArrayWithCondsTask
{

TEST(ConvertArrayInto2DArrayWithCondsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 3, 4, 2}, {1, 3}, {1}}), solution.findMatrix({1, 3, 4, 1, 2, 3, 1}));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2, 3, 4}}), solution.findMatrix({1, 2, 3, 4}));
}

}