#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string maximumNumber(std::string const &num, std::vector<int> const &change) const
    {
        constexpr size_t alphabetStart = '0';
        std::string result(num.size(), '0');
        State state = State::None;
        for (size_t index = 0; index < num.size();)
        {
            const size_t digitIndex = num[index] - alphabetStart;
            const char currentDigit = num[index];
            const char changeDigit = static_cast<char>(change[digitIndex] + '0');
            switch (state)
            {
            case State::None:
                if (currentDigit < changeDigit)
                    state = State::SubstrEnter;
                else
                    result[index++] = currentDigit;
                break;
            case State::SubstrEnter:
                if (changeDigit < num[index])
                    state = State::SubstrExit;
                else
                    result[index++] = changeDigit;
                break;
            case State::SubstrExit:
                result[index++] = currentDigit;
                break;
            }
        }
        return result;
    }

private:
    enum class State {None, SubstrEnter, SubstrExit};
};

}

namespace LargestNumberAfterMutatingSubstrTask
{

TEST(LargestNumberAfterMutatingSubstrTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("832", solution.maximumNumber("132", {9, 8, 5, 0, 3, 6, 4, 2, 6, 8}));
    ASSERT_EQ("934", solution.maximumNumber("021", {9, 4, 3, 5, 7, 2, 1, 9, 0, 6}));
    ASSERT_EQ("5", solution.maximumNumber("5", {1, 4, 7, 5, 3, 2, 5, 6, 9, 4}));
}

TEST(LargestNumberAfterMutatingSubstrTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ("974676", solution.maximumNumber("214010", {6, 7, 9, 7, 4, 0, 3, 4, 4, 7}));
    ASSERT_EQ("334999", solution.maximumNumber("334111", {0, 9, 2, 3, 3, 2, 5, 5, 5, 5}));
}

}