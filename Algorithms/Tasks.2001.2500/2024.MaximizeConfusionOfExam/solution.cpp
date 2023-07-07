#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxConsecutiveAnswers(std::string const &answerKey, int k) const
    {
        size_t bestSize = 0;
        const size_t maxChangeCount = k;
        size_t start = 0;
        char mainAnswer = answerKey.front();
        size_t mainCount = 0;
        size_t changeCount = 0;
        for (size_t index = 0; index < answerKey.size(); ++index)
        {
            const char currentAnswer = answerKey[index];
            ++(currentAnswer == mainAnswer ? mainCount : changeCount);
            if (changeCount > maxChangeCount)
            {
                while (start < index)
                {
                    // current
                    if (changeCount <= maxChangeCount)
                        break;
                    // reverse
                    if (mainCount <= maxChangeCount)
                    {
                        std::swap(mainCount, changeCount);
                        mainAnswer = mainAnswer == 'T' ? 'F' : 'T';
                        break;
                    }
                    --(answerKey[start] == mainAnswer ? mainCount : changeCount);
                    ++start;
                }
            }
            bestSize = std::max(bestSize, index - start + 1);
        }
        return static_cast<int>(bestSize);
    }
};

}

namespace MaximizeConfusionOfExamTask
{

TEST(MaximizeConfusionOfExamTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maxConsecutiveAnswers("TTFF", 2));
    ASSERT_EQ(3, solution.maxConsecutiveAnswers("TFFT", 1));
    ASSERT_EQ(5, solution.maxConsecutiveAnswers("TTFTTFTT", 1));
}

TEST(MaximizeConfusionOfExamTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.maxConsecutiveAnswers("FFFTTFTTFT", 3));
    ASSERT_EQ(10, solution.maxConsecutiveAnswers("FTFFTFTTTT", 4));
    ASSERT_EQ(3, solution.maxConsecutiveAnswers("TFF", 1));
}

}