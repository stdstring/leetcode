#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int getKth(int lo, int hi, int k) const
    {
        std::unordered_map<int, int> knownPowers;
        std::vector<std::pair<int, int>> data;
        for (int number = lo; number <= hi; ++number)
            data.emplace_back(number, calcPower(number, knownPowers));
        auto comp = [](std::pair<int, int> const &l, std::pair<int, int> const &r)
        {
            return (l.second < r.second) || ((l.second == r.second) && (l.first < r.first));
        };
        const auto iterator = std::next(data.begin(), k - 1);
        std::ranges::nth_element(data, iterator, comp);
        return iterator->first;
    }

private:
    [[nodiscard]] int calcPower(int n, std::unordered_map<int, int> &knownPowers) const
    {
        std::vector<int> chain({n});
        int currentPower = 0;
        while (n > 1)
        {
            const auto iterator = knownPowers.find(n);
            if (iterator != knownPowers.cend())
            {
                currentPower = iterator->second;
                break;
            }
            n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
            chain.emplace_back(n);
        }
        for (size_t rIndex = 0; rIndex < chain.size(); ++rIndex)
        {
            const size_t index = chain.size() - 1 - rIndex;
            if (chain[index] == 1)
                continue;
            const int delta = static_cast<int>(rIndex);
            knownPowers.emplace(chain[index], currentPower + delta);
        }
        return currentPower + static_cast<int>(chain.size() - 1);
    }
};

}

namespace SortIntegersByPowerValueTask
{

TEST(SortIntegersByPowerValueTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(13, solution.getKth(12, 15, 2));
    ASSERT_EQ(7, solution.getKth(7, 11, 4));
}

}