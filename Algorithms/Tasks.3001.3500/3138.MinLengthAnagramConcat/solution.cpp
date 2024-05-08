#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minAnagramLength(std::string const &s) const
    {
        if (std::ranges::count(s, s.front()) == static_cast<long long>(s.size()))
            return 1;
        for (size_t size = 2; 2 * size <= s.size(); ++size)
        {
            if (((s.size() % size) == 0) && checkPortion(s, size))
                return static_cast<int>(size);
        }
        return static_cast<int>(s.size());
    }

private:
    [[nodiscard]] bool checkPortion(std::string const &s, size_t portionSize) const
    {
        constexpr size_t alphabetStart = 'a';
        constexpr size_t alphabetSize = 26;
        // first portion
        std::vector<size_t> sampleLetterData(alphabetSize, 0);
        for (size_t index = 0; index < portionSize; ++index)
            ++sampleLetterData[s[index] - alphabetStart];
        // other portions
        for (size_t index = portionSize; index < s.size();)
        {
            std::vector<size_t> portionLetterData(alphabetSize, 0);
            for (size_t portionIndex = 0; portionIndex < portionSize; ++portionIndex)
            {
                const size_t currentLetter = s[index + portionIndex] - alphabetStart;
                ++portionLetterData[currentLetter];
                if (portionLetterData[currentLetter] > sampleLetterData[currentLetter])
                    return false;
            }
            index += portionSize;
        }
        return true;
    }
};

}

namespace MinLengthAnagramConcatTask
{

TEST(MinLengthAnagramConcatTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minAnagramLength("abba"));
    ASSERT_EQ(4, solution.minAnagramLength("cdef"));
}

}