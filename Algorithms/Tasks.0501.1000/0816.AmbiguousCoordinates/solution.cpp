#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::string> ambiguousCoordinates(std::string const &s) const
    {
        std::vector<std::string> result;
        // s[0] = '(', s[s.size() - 1] == ')'
        for (size_t secondPartStart = 2; secondPartStart <= s.size() - 2; ++secondPartStart)
        {
            for (std::string const &firstCoord : getPossibleNumbers(s, 1, secondPartStart - 1))
            {
                for (std::string const &secondCoord : getPossibleNumbers(s, secondPartStart, s.size() - 1 - secondPartStart))
                {
                    result.push_back(std::string("(").append(firstCoord).append(", ").append(secondCoord).append(")"));
                }
            }
        }
        return result;
    }

private:
    std::vector<std::string> getPossibleNumbers(std::string const &s, size_t from, size_t size) const
    {
        if (size == 1)
            return {s.substr(from, size)};
        if (s[from] == '0')
        {
            if (s[from + size - 1] == '0')
                return {};
            return {std::string("0.").append(s.substr(from + 1, size - 1))};
        }
        if (s[from + size - 1] == '0')
            return {s.substr(from, size)};
        std::vector<std::string> possibleNumbers;
        for (size_t pointRelPos = 1; pointRelPos < size; ++pointRelPos)
            possibleNumbers.push_back(s.substr(from, pointRelPos).append(".").append(s.substr(from + pointRelPos, size - pointRelPos)));
        possibleNumbers.push_back(s.substr(from, size));
        return possibleNumbers;
    }
};

}

namespace AmbiguousCoordinatesTask
{

TEST(AmbiguousCoordinatesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"(1, 2.3)", "(1, 23)", "(1.2, 3)", "(12, 3)"}), solution.ambiguousCoordinates("(123)"));
    ASSERT_EQ(std::vector<std::string>({"(0, 1.23)", "(0, 12.3)", "(0, 123)", "(0.1, 2.3)", "(0.1, 23)", "(0.12, 3)"}), solution.ambiguousCoordinates("(0123)"));
    ASSERT_EQ(std::vector<std::string>({"(0, 0.011)", "(0.001, 1)"}), solution.ambiguousCoordinates("(00011)"));
    ASSERT_EQ(std::vector<std::string>({"(10, 0)"}), solution.ambiguousCoordinates("(100)"));
}

}
