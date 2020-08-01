#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string getHint(std::string const &secret, std::string const &guess) const
    {
        size_t bulls = 0;
        size_t cows = 0;
        std::array<int, 10> digits{};
        digits.fill(0);
        std::string guessData(guess);
        for (size_t index = 0; index < secret.size(); ++index)
        {
            if (secret[index] == guess[index])
            {
                guessData[index] = 'B';
                ++bulls;
            }
            else
                ++digits[secret[index] - '0'];
        }
        for (char ch : guessData)
        {
            if (ch == 'B')
                continue;
            if (digits[ch - '0'] > 0)
            {
                --digits[ch - '0'];
                ++cows;
            }
        }
        return std::to_string(bulls) + "A" + std::to_string(cows) + "B";
    }
};

}

namespace BullsAndCowsTask
{

TEST(BullsAndCowsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("1A3B", solution.getHint("1807", "7810"));
    ASSERT_EQ("1A1B", solution.getHint("1123", "0111"));
}

TEST(BullsAndCowsTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("1A0B", solution.getHint("11", "10"));
}

}