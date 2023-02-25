#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string shiftingLetters(std::string const &S, std::vector<int> const &shifts) const
    {
        constexpr uint8_t alphabetSize = 26;
        std::vector<int> totalShifts(shifts);
        for (size_t index = 0; index < totalShifts.size(); ++index)
            totalShifts[totalShifts.size() - 1 - index] = (totalShifts[totalShifts.size() - 1 - index] % alphabetSize + (index > 0 ? totalShifts[totalShifts.size() - 1 - (index - 1)] : 0) % alphabetSize) % alphabetSize;
        std::string dest;
        for (size_t index = 0; index < S.size(); ++index)
            dest.push_back('a' + (S[index] - 'a' + totalShifts[index]) % alphabetSize);
        return dest;
    }
};

}

namespace ShiftingLettersTask
{

TEST(ShiftingLettersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("rpl", solution.shiftingLetters("abc", {3, 5, 9}));
}

}