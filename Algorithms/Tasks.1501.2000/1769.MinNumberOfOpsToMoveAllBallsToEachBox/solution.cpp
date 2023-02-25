#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> minOperations(std::string const &boxes) const
    {
        size_t leftOnesCount = 0;
        size_t leftOnesMoves = 0;
        size_t rightOnesCount = 0;
        size_t rightOnesMoves = 0;
        for (size_t index = 0; index < boxes.size(); ++index)
        {
            if (boxes[index] == '1')
            {
                ++rightOnesCount;
                rightOnesMoves += index;
            }
        }
        std::vector<int> answer(boxes.size(), 0);
        for (size_t index = 0; index < boxes.size(); ++index)
        {
            answer[index] = static_cast<int>(leftOnesMoves + rightOnesMoves);
            if (boxes[index] == '1')
            {
                ++leftOnesCount;
                --rightOnesCount;
            }
            leftOnesMoves += leftOnesCount;
            rightOnesMoves -= rightOnesCount;
        }
        return answer;
    }
};

}

namespace MinNumberOfOpsToMoveAllBallsToEachBoxTask
{

TEST(MinNumberOfOpsToMoveAllBallsToEachBoxTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 1, 3}), solution.minOperations("110"));
    ASSERT_EQ(std::vector<int>({11, 8, 5, 4, 3, 4}), solution.minOperations("001011"));
}

}
