#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long findScore(std::vector<int> const &nums) const
    {
        typedef std::pair<int, size_t> TEntry;
        const size_t maxIndex = nums.size() - 1;
        std::vector<bool> marked(nums.size(), false);
        auto cmp = [](TEntry const &l, TEntry const &r) { return (l.first > r.first) || ((l.first == r.first) && (l.second > r.second)); };
        std::priority_queue<TEntry, std::vector<TEntry>, decltype(cmp)> queue(cmp);
        for (size_t index = 0; index < nums.size(); ++index)
            queue.emplace(nums[index], index);
        long long score = 0;
        while (!queue.empty())
        {
            auto const [number, index] = queue.top();
            queue.pop();
            if (marked[index])
                continue;
            marked[index] = true;
            score += number;
            if (index > 0)
                marked[index - 1] = true;
            if (index < maxIndex)
                marked[index + 1] = true;
        }
        return score;
    }
};

}

namespace FindScoreOfArrayAfterMarkingElementsTask
{

TEST(FindScoreOfArrayAfterMarkingElementsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.findScore({2, 1, 3, 4, 5, 2}));
    ASSERT_EQ(5, solution.findScore({2, 3, 5, 1, 3, 2}));
}

}