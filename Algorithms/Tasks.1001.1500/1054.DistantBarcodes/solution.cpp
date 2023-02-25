#include <queue>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> rearrangeBarcodes(std::vector<int> const &barcodes) const
    {
        std::unordered_map<int, size_t> valuesCount;
        for (int barcode : barcodes)
            ++valuesCount[barcode];
        auto cmp = [](std::pair<int, size_t> const &l, std::pair<int, size_t> const &r){ return (l.second < r.second) || ((l.second == r.second) && (l.first < r.first)); };
        std::priority_queue<std::pair<int, size_t>, std::vector<std::pair<int, size_t>>, decltype(cmp)> queue(cmp);
        for (auto entry : valuesCount)
            queue.push(entry);
        std::vector<int> result;
        while  (queue.size() > 1)
        {
            std::pair<int, size_t> firstEntry(queue.top());
            queue.pop();
            std::pair<int, size_t> secondEntry(queue.top());
            queue.pop();
            result.push_back(firstEntry.first);
            result.push_back(secondEntry.first);
            if (firstEntry.second > 1)
                queue.emplace(firstEntry.first, firstEntry.second - 1);
            if (secondEntry.second > 1)
                queue.emplace(secondEntry.first, secondEntry.second - 1);
        }
        if (!queue.empty())
            result.push_back(queue.top().first);
        return result;
    }
};

}

namespace DistantBarcodesTask
{

TEST(DistantBarcodesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 1, 2, 1, 2, 1}), solution.rearrangeBarcodes({1, 1, 1, 2, 2, 2}));
    ASSERT_EQ(std::vector<int>({1, 3, 1, 2, 1, 3, 2, 1}), solution.rearrangeBarcodes({1, 1, 1, 1, 2, 2, 3, 3}));
}

}