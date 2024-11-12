#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> maximumBeauty(std::vector<std::vector<int>> const& items, std::vector<int> const& queries) const
    {
        std::vector<size_t> itemsIndices(items.size(), 0);
        std::iota(itemsIndices.begin(), itemsIndices.end(), 0);
        std::ranges::sort(itemsIndices, [&items](size_t left, size_t right) { return items[left][0] < items[right][0]; });
        std::vector<size_t> queriesIndices(queries.size(), 0);
        std::iota(queriesIndices.begin(), queriesIndices.end(), 0);
        std::ranges::sort(queriesIndices, [&queries](size_t left, size_t right) { return queries[left] < queries[right]; });
        std::vector<int> answer(queries.size(), 0);
        int maxBeauty = 0;
        size_t itemIndex = 0;
        for (size_t queryIndex : queriesIndices)
        {
            while ((itemIndex < itemsIndices.size()) && (items[itemsIndices[itemIndex]][0] <= queries[queryIndex]))
            {
                maxBeauty = std::max(maxBeauty, items[itemsIndices[itemIndex]][1]);
                ++itemIndex;
            }
            answer[queryIndex] = maxBeauty;
        }
        return answer;
    }
};

}

namespace MostBeautifulItemForEachQueryTask
{

TEST(MostBeautifulItemForEachQueryTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 4, 5, 5, 6, 6}), solution.maximumBeauty({{1, 2}, {3, 2}, {2, 4}, {5, 6}, {3, 5}}, {1, 2, 3, 4, 5, 6}));
    ASSERT_EQ(std::vector<int>({4}), solution.maximumBeauty({{1, 2}, {1, 2}, {1, 3}, {1, 4}}, {1}));
    ASSERT_EQ(std::vector<int>({0}), solution.maximumBeauty({{10, 1000}}, {5}));
}

TEST(MostBeautifulItemForEachQueryTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({962, 962, 962, 962, 746, 962, 962, 962, 946, 962, 962, 919, 746, 746, 962, 962, 962, 919, 962}),
              solution.maximumBeauty({{193, 732}, {781, 962}, {864, 954}, {749, 627}, {136, 746}, {478, 548}, {640, 908}, {210, 799}, {567, 715}, {914, 388},
                                      {487, 853}, {533, 554}, {247, 919}, {958, 150}, {193, 523}, {176, 656}, {395, 469}, {763, 821}, {542, 946}, {701, 676}},
                                     {885, 1445, 1580, 1309, 205, 1788, 1214, 1404, 572, 1170, 989, 265, 153, 151, 1479, 1180, 875, 276, 1584}));
}

}