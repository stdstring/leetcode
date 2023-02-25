#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> sumEvenAfterQueries(std::vector<int> const &nums, std::vector<std::vector<int>> const &queries) const
    {
        std::vector<int> numbers(nums);
        int evenNumbersSum = std::accumulate(numbers.cbegin(), numbers.cend(), 0, [](int result, int number){ return result + (number % 2 == 0 ? number : 0); });
        std::vector<int> answers(queries.size(), 0);
        for (size_t index = 0; index < queries.size(); ++index)
        {
            const int oldValue = numbers[queries[index][1]];
            const int newValue = oldValue + queries[index][0];
            if (oldValue % 2 == 0)
                evenNumbersSum -= oldValue;
            if (newValue % 2 == 0)
                evenNumbersSum += newValue;
            numbers[queries[index][1]] = newValue;
            answers[index] = evenNumbersSum;
        }
        return answers;
    }
};

}

namespace SumOfEvenNumbersAfterQueriesTask
{

TEST(SumOfEvenNumbersAfterQueriesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({8, 6, 2, 4}), solution.sumEvenAfterQueries({1, 2, 3, 4}, {{1, 0}, {-3, 1}, {-4, 0}, {2, 3}}));
    ASSERT_EQ(std::vector<int>({0}), solution.sumEvenAfterQueries({1}, {{4, 0}}));
}

}
