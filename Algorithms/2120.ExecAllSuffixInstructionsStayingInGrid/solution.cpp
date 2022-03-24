#include <stdexcept>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> executeInstructions(int n, std::vector<int> const &startPos, std::string const &s) const
    {
        std::vector<int> result;
        result.reserve(s.size());
        for (size_t start = 0; start < s.size(); ++start)
            result.push_back(executeInstructionsImpl(n, startPos[0], startPos[1], s, start));
        return result;
    }

private:
    [[nodiscard]] int executeInstructionsImpl(int n, int row, int column, std::string const &s, size_t start) const
    {
        int numberOfInstructions = 0;
        for (size_t index = start; index < s.size(); ++index)
        {
            switch (s[index])
            {
                case 'L':
                    --column;
                    break;
                case 'R':
                    ++column;
                    break;
                case 'U':
                    --row;
                    break;
                case 'D':
                    ++row;
                    break;
                default:
                    throw std::logic_error("Unknown command");
            }
            if ((row < 0) || (row == n) || (column < 0) || (column == n))
                break;
            ++numberOfInstructions;
        }
        return numberOfInstructions;
    }
};

}

namespace ExecAllSuffixInstructionsStayingInGridTask
{

TEST(ExecAllSuffixInstructionsStayingInGridTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 5, 4, 3, 1, 0}), solution.executeInstructions(3, {0, 1}, "RRDDLU"));
    ASSERT_EQ(std::vector<int>({4, 1, 0, 0}), solution.executeInstructions(2, {1, 1}, "LURD"));
    ASSERT_EQ(std::vector<int>({0, 0, 0, 0}), solution.executeInstructions(1, {0, 0}, "LRUD"));
}

}