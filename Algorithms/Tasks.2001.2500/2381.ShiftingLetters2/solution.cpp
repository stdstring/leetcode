#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string shiftingLetters(std::string const &s, std::vector<std::vector<int>> const &shifts) const
    {
        constexpr int alphabetSize = 26;
        constexpr char alphabetStart = 'a';
        std::vector<int> deltas(s.size() + 1, 0);
        for (std::vector<int> const &shift : shifts)
        {
            const int deltaEnter = shift[2] == 1 ? 1 : -1;
            const int deltaExit = -deltaEnter;
            deltas[shift[0]] += deltaEnter;
            deltas[shift[1] + 1] += deltaExit;
        }
        std::string result(s.size(), ' ');
        int delta = 0;
        for (size_t index = 0; index < s.size(); ++index)
        {
            delta = (delta + deltas[index]) % alphabetSize;
            if (delta < 0)
                delta = (delta + alphabetSize) % alphabetSize;
            result[index] = static_cast<char>(alphabetStart + (s[index] - alphabetStart + delta) % alphabetSize);
        }
        return result;
    }
};

}

namespace ShiftingLetters2Task
{

TEST(ShiftingLetters2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("ace", solution.shiftingLetters("abc", {{0, 1, 0}, {1, 2, 1}, {0, 2, 1}}));
    ASSERT_EQ("catz", solution.shiftingLetters("dztz", {{0, 0, 0}, {1, 1, 1}}));
}

}