#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countTexts(std::string const &pressedKeys) const
    {
        std::unordered_map<char, size_t> combinationsCount({{'2', 3}, {'3', 3}, {'4', 3}, {'5', 3}, {'6', 3}, {'7', 4}, {'8', 3}, {'9', 4}});
        size_t result = 1;
        for (size_t start = 0; start < pressedKeys.size();)
        {
            size_t substrSize = 1;
            for (size_t shift = 1; ((start + shift) < pressedKeys.size()) && (pressedKeys[start] == pressedKeys[start + shift]); ++shift)
                ++substrSize;
            if (substrSize > 1)
                result = (result * calcCombinationsForSameDigitSubstr(substrSize, combinationsCount[pressedKeys[start]])) % ModValue;
            start += substrSize;
        }
        return static_cast<int>(result);
    }

private:
    static constexpr size_t ModValue = 1000000007;

    [[nodiscard]] size_t calcCombinationsForSameDigitSubstr(size_t substrSize, size_t combinationsCount) const
    {
        const size_t ringSize = combinationsCount + 1;
        std::vector<size_t> combinations(ringSize, 0);
        combinations[0] = 1;
        for (size_t pos = 0; pos < substrSize; ++pos)
        {
            for (size_t shift = 1; shift <= combinationsCount; ++shift)
            {
                combinations[(pos + shift) % ringSize] = (combinations[(pos + shift) % ringSize] + combinations[pos % ringSize]) % ModValue;
            }
            combinations[pos % ringSize] = 0;
        }
        return combinations[substrSize % ringSize];
    }
};

}

namespace CountNumberOfTextsTask
{

TEST(CountNumberOfTextsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.countTexts("22233"));
    ASSERT_EQ(82876089, solution.countTexts("222222222222222222222222222222222222"));
}

}