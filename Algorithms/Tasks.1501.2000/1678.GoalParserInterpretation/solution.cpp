#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string interpret(std::string const &command) const
    {
        std::string result;
        for (size_t index = 0; index < command.size();)
        {
            // G
            if (command[index] == 'G')
            {
                result.push_back('G');
                ++index;
            }
            // ()
            else if (command[index] == '(' && command[index + 1] == ')')
            {
                result.push_back('o');
                index += 2;
            }
            // (al)
            else
            {
                result.append("al");
                index += 4;
            }
        }
        return result;
    }
};

}

namespace GoalParserInterpretationTask
{

TEST(GoalParserInterpretationTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("Goal", solution.interpret("G()(al)"));
    ASSERT_EQ("Gooooal", solution.interpret("G()()()()(al)"));
    ASSERT_EQ("alGalooG", solution.interpret("(al)G(al)()()G"));
}

}