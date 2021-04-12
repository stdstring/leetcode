#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> decode(std::vector<int> const &encoded, int first) const
    {
        std::vector<int> source(encoded.size() + 1, 0);
        source[0] = first;
        for (size_t index = 0; index < encoded.size(); ++index)
            source[index + 1] = source[index] ^ encoded[index];
        return source;
    }
};

}

namespace DecodeXORedArrayTask
{

TEST(DecodeXORedArrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 0, 2, 1}), solution.decode({1, 2, 3}, 1));
    ASSERT_EQ(std::vector<int>({4, 2, 0, 7, 4}), solution.decode({6, 2, 7, 3}, 4));
}

}