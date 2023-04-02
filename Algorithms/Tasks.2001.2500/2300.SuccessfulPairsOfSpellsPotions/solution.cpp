#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> successfulPairs(std::vector<int> const &spells, std::vector<int> const &potions, long long success) const
    {
        std::vector<int> sortedPotions(potions);
        std::sort(sortedPotions.begin(), sortedPotions.end());
        std::vector<int> result(spells.size(), 0);
        for (size_t index = 0; index < result.size(); ++index)
            result[index] = static_cast<int>(calcSuccessfulPotionsCount(spells[index], sortedPotions, success));
        return result;
    }

private:
    [[nodiscard]] size_t calcSuccessfulPotionsCount(long long spell, std::vector<int> const &sortedPotions, long long success) const
    {
        if (spell * sortedPotions.front() >= success)
            return sortedPotions.size();
        if (spell * sortedPotions.back() < success)
            return 0;
        size_t left = 0;
        size_t right = sortedPotions.size();
        while (left < right)
        {
            const size_t middle = (left + right) / 2;
            const long long middleValue = spell * sortedPotions[middle];
            if (middleValue < success)
                left = middle + 1;
            else
                right = middle;
        }
        return sortedPotions.size() - left;
    }
};

}

namespace SuccessfulPairsOfSpellsPotionsTask
{

TEST(SuccessfulPairsOfSpellsPotionsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({4, 0, 3}), solution.successfulPairs({5, 1, 3}, {1, 2, 3, 4, 5}, 7));
    ASSERT_EQ(std::vector<int>({2, 0, 2}), solution.successfulPairs({3, 1, 2}, {8, 5, 8}, 16));
}

}