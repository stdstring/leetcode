#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<bool> camelMatch(std::vector<std::string> const &queries, std::string const &pattern) const
    {
        std::vector<bool> result;
        auto transformFun = [&pattern](std::string const &query)
        {
            size_t patternIndex = 0;
            for (const char ch : query)
            {
                if (std::isupper(ch) && (patternIndex == pattern.size() || ch != pattern[patternIndex]))
                    return false;
                if (ch == pattern[patternIndex])
                    ++patternIndex;
            }
            return patternIndex == pattern.size();
        };
        std::transform(queries.cbegin(), queries.cend(), std::back_inserter(result), transformFun);
        return result;
    }
};

}

namespace CamelcaseMatchingTask
{

TEST(CamelcaseMatchingTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector({true, false, true, true, false}), solution.camelMatch({"FooBar", "FooBarTest", "FootBall", "FrameBuffer", "ForceFeedBack"}, "FB"));
    ASSERT_EQ(std::vector({true, false, true, false, false}), solution.camelMatch({"FooBar", "FooBarTest", "FootBall", "FrameBuffer", "ForceFeedBack"}, "FoBa"));
    ASSERT_EQ(std::vector({false, true, false, false, false}), solution.camelMatch({"FooBar", "FooBarTest", "FootBall", "FrameBuffer", "ForceFeedBack"}, "FoBaT"));
}

}