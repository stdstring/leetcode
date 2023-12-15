#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string destCity(std::vector<std::vector<std::string>> const &paths) const
    {
        std::unordered_map<std::string, bool> cityMap;
        for (std::vector<std::string> const &path : paths)
        {
            auto fromIterator = cityMap.find(path[0]);
            if (fromIterator == cityMap.end())
                cityMap.emplace(path[0], false);
            else
                fromIterator->second = false;
            auto toIterator = cityMap.find(path[1]);
            if (toIterator == cityMap.end())
                cityMap.emplace(path[1], true);
        }
        for (auto const &[city, isDestination] : cityMap)
        {
            if (isDestination)
                return city;
        }
        return "";
    }
};

}

namespace DestinationCityTask
{

TEST(DestinationCityTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("Sao Paulo", solution.destCity({{"London", "New York"}, {"New York", "Lima"}, {"Lima", "Sao Paulo"}}));
    ASSERT_EQ("A", solution.destCity({{"B", "C"}, {"D", "B"}, {"C", "A"}}));
    ASSERT_EQ("Z", solution.destCity({{"A", "Z"}}));
}

}