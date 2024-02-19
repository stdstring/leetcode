#include <algorithm>
#include <iterator>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int chalkReplacer(std::vector<int> const &chalk, int k) const
    {
        std::vector<long long> prefixSums(chalk.size(), 0);
        for (size_t index = 0; index < chalk.size(); ++index)
            prefixSums[index] = (index > 0 ? prefixSums[index - 1] : 0) + chalk[index];
        const long long totalChalkRest = k % prefixSums.back();
        const auto iterator = std::ranges::lower_bound(prefixSums, totalChalkRest);
        return static_cast<int>(std::distance(prefixSums.begin(), iterator)) + (totalChalkRest == *iterator ? 1 : 0);
    }
};

}

namespace FindStudentThatWillReplaceChalkTask
{

TEST(FindStudentThatWillReplaceChalkTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.chalkReplacer({5, 1, 5}, 22));
    ASSERT_EQ(1, solution.chalkReplacer({3, 4, 1, 2}, 25));
}

}