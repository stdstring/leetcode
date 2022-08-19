#include <queue>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isPossible(std::vector<int> const &nums) const
    {
        auto cmp = [](std::pair<int, size_t> const &l, std::pair<int, size_t> const &r){ return (l.first > r.first) || ((l.first == r.first) && (l.second > r.second));};
        std::priority_queue<std::pair<int, size_t>, std::vector<std::pair<int, size_t>>, decltype(cmp)> queue(cmp);
        for (int number : nums)
        {
            const int previousNumber = number - 1;
            while (!queue.empty() && (queue.top().first < previousNumber))
            {
                if (queue.top().second < 3)
                    return false;
                queue.pop();
            }
            if (queue.empty() || (queue.top().first > previousNumber))
                queue.emplace(number, 1);
            else
            {
                queue.emplace(number, queue.top().second + 1);
                queue.pop();
            }
        }
        while (!queue.empty())
        {
            if (queue.top().second < 3)
                return false;
            queue.pop();
        }
        return true;
    }
};

}

namespace SplitArrayIntoConsecutiveSubseqsTask
{

TEST(SplitArrayIntoConsecutiveSubseqsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isPossible({1, 2, 3, 3, 4, 5}));
    ASSERT_EQ(true, solution.isPossible({1, 2, 3, 3, 4, 4, 5, 5}));
    ASSERT_EQ(false, solution.isPossible({1, 2, 3, 4, 4, 5}));
}

}