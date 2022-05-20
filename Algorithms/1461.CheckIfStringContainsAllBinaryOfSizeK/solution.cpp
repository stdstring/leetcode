#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool hasAllCodes(std::string const &s, int k) const
    {
        if (s.size() <= static_cast<size_t>(k))
            return false;
        const int numbersCount = 1 << k;
        int maxNumber = numbersCount - 1;
        std::vector<bool> knownNumbers(numbersCount, false);
        int number = 0;
        for (size_t index = 0; index < k; ++index)
            number = (number << 1) | (s[index] == '1' ? 1 : 0);
        knownNumbers[number] = true;
        int knownNumbersCount = 1;
        for (size_t index = k; index < s.size(); ++index)
        {
            number = (maxNumber & (number << 1)) | (s[index] == '1' ? 1 : 0);
            if (!knownNumbers[number])
            {
                knownNumbers[number] = true;
                ++knownNumbersCount;
            }
            if (knownNumbersCount == numbersCount)
                return true;
        }
        return false;
    }
};

}

namespace CheckIfStringContainsAllBinaryOfSizeKTask
{

TEST(CheckIfStringContainsAllBinaryOfSizeKTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.hasAllCodes("00110110", 2));
    ASSERT_EQ(true, solution.hasAllCodes("0110", 1));
    ASSERT_EQ(false, solution.hasAllCodes("0110", 2));
}

}
