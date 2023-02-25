#include <queue>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> topKFrequent(std::vector<int> const &nums, int k) const
    {
        std::unordered_map<int, size_t> frequencyMap;
        for (int num : nums)
            ++frequencyMap[num];
        auto comparer = [](std::pair<int, size_t> const& left, std::pair<int, size_t> const& right) { return left.second < right.second; };
        std::priority_queue<std::pair<int, size_t>, std::vector<std::pair<int, size_t>>, decltype(comparer)> queue(comparer);
        std::vector<int> result;
        for (auto const &pair : frequencyMap)
            queue.push(pair);
        for (size_t index = 0; index < static_cast<size_t>(k); ++index)
        {
            result.push_back(queue.top().first);
            queue.pop();
        }
        return result;
    }
};

}

namespace TopKFrequentElementsTask
{

TEST(TopKFrequentElementsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2}), solution.topKFrequent({1, 1, 1, 2, 2, 3}, 2));
    ASSERT_EQ(std::vector<int>({1}), solution.topKFrequent({1}, 1));
}

}