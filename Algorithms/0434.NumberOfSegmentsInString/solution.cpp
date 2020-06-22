#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int countSegments(std::string const &s) const
    {
        if (s.empty())
            return 0;
        int count = 0;
        std::string::const_iterator iterator = skipWhitespaces(s.cbegin(), s.cend());
        while (iterator != s.cend())
        {
            ++count;
            iterator = skipWhitespaces(processSegment(iterator, s.cend()), s.cend());
        }
        return count;
    }

private:
    std::string::const_iterator skipWhitespaces(std::string::const_iterator iterator, std::string::const_iterator end) const
    {
        while (iterator != end && *iterator == ' ')
            ++iterator;
        return iterator;
    }

    std::string::const_iterator processSegment(std::string::const_iterator iterator, std::string::const_iterator end) const
    {
        while (iterator != end && *iterator != ' ')
            ++iterator;
        return iterator;
    }
};

}

namespace NumberOfSegmentsInStringTask
{

TEST(NumberOfSegmentsInStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.countSegments("Hello, my name is John"));
}

}