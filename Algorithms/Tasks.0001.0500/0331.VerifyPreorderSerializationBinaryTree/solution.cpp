#include <stack>
#include <string>

#include "gtest/gtest.h"

namespace
{

enum class Direction {Left, Right};

class Solution
{
public:
    bool isValidSerialization(std::string const &preorder) const
    {
        std::stack<Direction> directionStack;
        size_t index = 0;
        while (index < preorder.size())
        {
            if (index > 0 && directionStack.empty())
                break;
            if (preorder[index] == Delimiter)
                ++index;
            if (preorder[index] == NullValue)
            {
                ++index;
                if (directionStack.empty())
                    continue;
                if (directionStack.top() == Direction::Left)
                    directionStack.top() = Direction::Right;
                else
                {
                    while (!directionStack.empty() && directionStack.top() == Direction::Right)
                        directionStack.pop();
                    if (!directionStack.empty())
                        directionStack.top() = Direction::Right;
                }
            }
            else
            {
                readNode(preorder, index);
                directionStack.push(Direction::Left);
            }
        }
        return (index == preorder.size()) && directionStack.empty();
    }

private:
    constexpr static char Delimiter = ',';
    constexpr static char NullValue = '#';

    void readNode(std::string const &source, size_t &index) const
    {
        size_t nextDelimiterIndex = source.find(Delimiter, index);
        index = nextDelimiterIndex == std::string::npos ? source.size() : nextDelimiterIndex;
    }
};

}

namespace VerifyPreorderSerializationBinaryTreeTask
{

TEST(VerifyPreorderSerializationBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#"));
    ASSERT_EQ(false, solution.isValidSerialization("1,#"));
    ASSERT_EQ(false, solution.isValidSerialization("9,#,#,1"));
}

TEST(VerifyPreorderSerializationBinaryTreeTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isValidSerialization("#"));
}

}