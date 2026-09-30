#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> maxDepthAfterSplit(std::string const &seq) const
    {
        std::vector<int> result(seq.size(), 0);
        int currentSplit = 1;
        for (size_t index = 0; index < seq.size(); ++index)
        {
            if (seq[index] == '(')
            {
                currentSplit = (currentSplit == 0) ? 1 : 0;
                result[index] = currentSplit;
            }
            else
            {
                result[index] = currentSplit;
                currentSplit = (currentSplit == 0) ? 1 : 0;
            }
        }
        return result;
    }
};

}

namespace MaxNestingDepthOfTwoVPSTask
{

TEST(MaxNestingDepthOfTwoVPSTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({ 0, 1, 1, 1, 1, 0 }), solution.maxDepthAfterSplit("(()())"));
    ASSERT_EQ(std::vector<int>({0, 0, 0, 1, 1, 0, 0, 0}), solution.maxDepthAfterSplit("()(())()"));
}

}