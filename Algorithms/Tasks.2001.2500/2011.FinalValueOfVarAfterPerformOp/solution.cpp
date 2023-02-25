#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int finalValueAfterOperations(std::vector<std::string> const &operations) const
    {
        int value = 0;
        for (std::string const &operation : operations)
        {
            switch (operation[1])
            {
                case '+':
                    ++value;
                    break;
                case '-':
                    --value;
                    break;
                default:
                    break;
            }
        }
        return value;
    }
};

}

namespace FinalValueOfVarAfterPerformOpTask
{

TEST(FinalValueOfVarAfterPerformOpTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.finalValueAfterOperations({"--X", "X++", "X++"}));
    ASSERT_EQ(3, solution.finalValueAfterOperations({"++X", "++X", "X++"}));
    ASSERT_EQ(0, solution.finalValueAfterOperations({"X++", "++X", "--X", "X--"}));
}

}