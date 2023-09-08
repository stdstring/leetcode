#include <set>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> avoidFlood(std::vector<int> const &rains) const
    {
        std::unordered_map<int, size_t> rainMap;
        std::set<size_t> drySet;
        std::vector<int> result(rains.size(), 1);
        for (size_t index = 0; index < rains.size(); ++index)
        {
            if (rains[index] == 0)
                drySet.emplace(index);
            else
            {
                result[index] = -1;
                auto rainIterator = rainMap.find(rains[index]);
                if (rainIterator == rainMap.cend())
                    rainMap.emplace(rains[index], index);
                else
                {
                    auto dryIterator = drySet.upper_bound(rainIterator->second);
                    if (dryIterator == drySet.cend())
                        return {};
                    result[*dryIterator] = rainIterator->first;
                    drySet.erase(dryIterator);
                    rainIterator->second = index;
                }
            }
        }
        return result;
    }
};

}

namespace AvoidFloodInCityTask
{

TEST(AvoidFloodInCityTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({-1, -1, -1, -1}), solution.avoidFlood({1, 2, 3, 4}));
    ASSERT_EQ(std::vector<int>({-1, -1, 2, 1, -1, -1}), solution.avoidFlood({1, 2, 0, 0, 2, 1}));
    ASSERT_EQ(std::vector<int>(), solution.avoidFlood({1, 2, 0, 1, 2}));
}

}