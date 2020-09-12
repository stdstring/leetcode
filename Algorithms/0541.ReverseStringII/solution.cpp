#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string reverseStr(std::string const &s, int k) const
    {
        const size_t partSize = static_cast<size_t>(k);
        std::string dest;
        dest.reserve(s.size());
        size_t index = 0;
        while (index < s.size())
        {
            size_t currentPartSize = std::min(partSize, s.size() - index);
            for (size_t partShift = 0; partShift < currentPartSize; ++partShift)
                dest.push_back(s[index + currentPartSize - partShift - 1]);
            index += currentPartSize;
            currentPartSize = std::min(partSize, s.size() - index);
            for (size_t partShift = 0; partShift < currentPartSize; ++partShift)
                dest.push_back(s[index + partShift]);
            index += currentPartSize;
        }
        return dest;
    }
};

}

namespace ReverseStringIITask
{

TEST(ReverseStringIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("bacdfeg", solution.reverseStr("abcdefg", 2));
}

}
