#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string minimumString(std::string const &a, std::string const &b, std::string const &c) const
    {
        // a + b + c
        std::string result(processStringTriplet(a, b, c));
        // a + c + b
        result = min(result, processStringTriplet(a, c, b));
        // b + a + c
        result = min(result, processStringTriplet(b, a, c));
        // b + c + a
        result = min(result, processStringTriplet(b, c, a));
        // c + a + b
        result = min(result, processStringTriplet(c, a, b));
        // c + b + a
        result = min(result, processStringTriplet(c, b, a));
        return result;
    }

private:
    [[nodiscard]] size_t getOverlapSize(std::string const &first, std::string const &second) const
    {
        for (size_t index1 = 0; index1 < first.size(); ++index1)
        {
            if (first[index1] != second[0])
                continue;
            const size_t suffixSize = second.size() < (first.size() - index1) ? second.size() : first.size() - index1;
            size_t overlapSegmentSize = 0;
            for (size_t index2 = 0; index2 < suffixSize; ++index2)
            {
                if (first[index1 + index2] != second[index2])
                    break;
                ++overlapSegmentSize;
            }
            if (suffixSize == overlapSegmentSize)
                return suffixSize;
        }
        return 0;
    }

    [[nodiscard]] std::string processStringTriplet(std::string const &first, std::string const &second, std::string const &third) const
    {
        std::string result(first);
        const size_t overlap12 = getOverlapSize(first, second);
        if (overlap12 < second.size())
            result.append(second.substr(overlap12));
        const size_t overlap123 = getOverlapSize(result, third);
        if (overlap123 < third.size())
            result.append(third.substr(overlap123));
        return result;
    }

    [[nodiscard]] std::string min(std::string const &first, std::string const &second) const
    {
        if (first.size() < second.size())
            return first;
        if (second.size() < first.size())
            return second;
        return std::min(first, second);
    }
};

}

namespace ShortestStringThatContains3StringsTask
{

TEST(ShortestStringThatContains3StringsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("aaabca", solution.minimumString("abc", "bca", "aaa"));
    ASSERT_EQ("aba", solution.minimumString("ab", "ba", "aba"));
}

TEST(ShortestStringThatContains3StringsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ("ca", solution.minimumString("ca", "a", "a"));
}

}