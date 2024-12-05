#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canChange(std::string const &start, std::string const &target) const
    {
        char currentLetter = '\0';
        size_t currentCount = 0;
        for (size_t index = 0; index < start.size(); ++index)
        {
            // currentLetter == '\0'
            if ((currentLetter == '\0') && (start[index] == 'R') && (target[index] == '_'))
            {
                currentLetter = 'R';
                ++currentCount;
                continue;
            }
            if ((currentLetter == '\0') && (start[index] == '_') && (target[index] == 'L'))
            {
                currentLetter = 'L';
                ++currentCount;
                continue;
            }
            if ((currentLetter == '\0') && (start[index] == target[index]))
                continue;
            // currentLetter == 'L'
            if ((currentLetter == 'L') && (start[index] == '_') && (target[index] == '_'))
                continue;
            if ((currentLetter == 'L') && (start[index] == 'L') && (target[index] == '_'))
            {
                --currentCount;
                if (currentCount == 0)
                    currentLetter = '\0';
                continue;
            }
            if ((currentLetter == 'L') && (start[index] == '_') && (target[index] == 'L'))
            {
                ++currentCount;
                continue;
            }
            if ((currentLetter == 'L') && (start[index] == 'L') && (target[index] == 'L'))
                continue;
            // currentLetter == 'R'
            if ((currentLetter == 'R') && (start[index] == '_') && (target[index] == '_'))
                continue;
            if ((currentLetter == 'R') && (start[index] == '_') && (target[index] == 'R'))
            {
                --currentCount;
                if (currentCount == 0)
                    currentLetter = '\0';
                continue;
            }
            if ((currentLetter == 'R') && (start[index] == 'R') && (target[index] == '_'))
            {
                ++currentCount;
                continue;
            }
            if ((currentLetter == 'R') && (start[index] == 'R') && (target[index] == 'R'))
                continue;
            return false;
        }
        return currentLetter == '\0';
    }
};

}

namespace MovePiecesObtainStringTask
{

TEST(MovePiecesObtainStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canChange("_L__R__R_", "L______RR"));
    ASSERT_EQ(false, solution.canChange("R_L_", "__LR"));
    ASSERT_EQ(false, solution.canChange("_R", "R_"));
}

TEST(MovePiecesObtainStringTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(false, solution.canChange("L_", "_L"));
    ASSERT_EQ(true, solution.canChange("_LL", "LL_"));
}

TEST(MovePiecesObtainStringTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canChange("__LL", "LL__"));
    ASSERT_EQ(true, solution.canChange("LLRR", "LLRR"));
}

}