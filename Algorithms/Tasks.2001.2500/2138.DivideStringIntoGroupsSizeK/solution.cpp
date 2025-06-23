#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> divideString(std::string const &s, int k, char fill) const
    {
        const size_t groupSize = k;
        const size_t groupCount = (s.size() / groupSize) + ((s.size() % groupSize) == 0 ? 0 : 1);
        std::vector<std::string> result(groupCount);
        for (size_t index = 0; index < groupCount; ++index)
        {
            const size_t start = index * groupSize;
            result[index] = s.substr(start, groupSize);
            if (result[index].size() < groupSize)
                result[index] += std::string(k - result[index].size(), fill);
        }
        return result;
    }
};

}

namespace DivideStringIntoGroupsSizeKTask
{

TEST(DivideStringIntoGroupsSizeKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"abc", "def", "ghi"}), solution.divideString("abcdefghi", 3, 'x'));
    ASSERT_EQ(std::vector<std::string>({"abc", "def", "ghi", "jxx"}), solution.divideString("abcdefghij", 3, 'x'));
}

}