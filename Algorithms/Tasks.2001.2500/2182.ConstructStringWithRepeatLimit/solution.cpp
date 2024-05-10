#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string repeatLimitedString(std::string const &s, int repeatLimit) const
    {
        constexpr size_t alphabetStart = 'a';
        constexpr size_t alphabetSize = 26;
        std::vector<int> letterData(alphabetSize, 0);
        for (const char ch : s)
            ++letterData[alphabetSize - 1 - (ch - alphabetStart)];
        std::string result;
        result.reserve(s.size());
        for (size_t index = 0; index < alphabetSize;)
        {
            if (letterData[index] == 0)
            {
                ++index;
                continue;
            }
            const int portionCount = std::min(repeatLimit, letterData[index]);
            result.append(portionCount, static_cast<char>(alphabetStart + alphabetSize - 1 - index));
            letterData[index] -= portionCount;
            if (letterData[index] == 0)
                continue;
            bool canContinue = false;
            for (size_t nextIndex = index + 1; nextIndex < alphabetSize; ++nextIndex)
            {
                if (letterData[nextIndex] > 0)
                {
                    --letterData[nextIndex];
                    result.append(1, static_cast<char>(alphabetStart + alphabetSize - 1 - nextIndex));
                    canContinue = true;
                    break;
                }
            }
            if (!canContinue)
                break;
        }
        return result;
    }
};

}

namespace ConstructStringWithRepeatLimitTask
{

TEST(ConstructStringWithRepeatLimitTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("zzcccac", solution.repeatLimitedString("cczazcc", 3));
    ASSERT_EQ("bbabaa", solution.repeatLimitedString("aababab", 2));
}

TEST(ConstructStringWithRepeatLimitTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ("yxxvvuvusrrqqppopponliihgfeeddcbba",
              solution.repeatLimitedString("robnsdvpuxbapuqgopqvxdrchivlifeepy", 2));
}

}