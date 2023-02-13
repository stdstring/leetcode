#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> sortJumbled(std::vector<int> const &mapping, std::vector<int> const &nums) const
    {
        std::multimap<int, int> storage;
        for (int number : nums)
            storage.emplace(convertNumber(number, mapping), number);
        std::vector<int> result;
        result.reserve(nums.size());
        for (const auto &[_, value] : storage)
            result.push_back(value);
        return result;
    }

private:
    [[nodiscard]] int convertNumber(int source, std::vector<int> const &mapping) const
    {
        if (source == 0)
            return mapping[0];
        int result = 0;
        int factor = 1;
        while (source > 0)
        {
            result += (mapping[source % 10] * factor);
            source /= 10;
            factor *= 10;
        }
        return result;
    }
};

}

namespace SortJumbledNumbersTask
{

TEST(SortJumbledNumbersTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({338, 38, 991}), solution.sortJumbled({8, 9, 4, 0, 2, 1, 3, 5, 7, 6}, {991, 338, 38}));
    ASSERT_EQ(std::vector<int>({123, 456, 789}), solution.sortJumbled({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {789, 456, 123}));
}

TEST(SortJumbledNumbersTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({9, 8, 7, 6, 5, 4, 3, 2, 1, 0}), solution.sortJumbled({9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

}