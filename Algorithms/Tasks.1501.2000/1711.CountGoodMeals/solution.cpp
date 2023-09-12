#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countPairs(std::vector<int> const &deliciousness) const
    {
        const int maxValue = *std::ranges::max_element(deliciousness);
        std::vector<int> powers2;
        for (int power2 = 1; power2 <= 2 * maxValue; power2 <<= 1)
            powers2.emplace_back(power2);
        std::unordered_map<int, size_t> deliciousnessMap;
        for (int value : deliciousness)
            ++deliciousnessMap[value];
        constexpr size_t modValue = 1000000007;
        size_t result = 0;
        for (auto const &[value, count] : deliciousnessMap)
        {
            for (const int power2 : powers2)
            {
                if (power2 < value)
                    continue;
                int otherTerm = power2 - value;
                auto iterator = deliciousnessMap.find(otherTerm);
                if (iterator == deliciousnessMap.cend())
                    continue;
                const size_t otherCount = iterator->second - (value == otherTerm ? 1 : 0);
                result = (result + count * otherCount);
            }
        }
        return static_cast<int>((result / 2) % modValue);
    }
};

}

namespace CountGoodMealsTask
{

TEST(CountGoodMealsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.countPairs({1, 3, 5, 7, 9}));
    ASSERT_EQ(15, solution.countPairs({1, 1, 1, 3, 3, 3, 7}));
}

TEST(CountGoodMealsTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.countPairs({0, 0, 0}));
}

}