#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int compress(std::vector<char>& chars)
    {
        size_t size = 0;
        std::vector<char>::const_iterator read_iterator = chars.cbegin();
        std::vector<char>::iterator write_iterator = chars.begin();
        while (read_iterator != chars.cend())
        {
            const char ch = *read_iterator;
            ++read_iterator;
            size_t count = 1;
            for (;read_iterator != chars.cend() && *read_iterator == ch; ++read_iterator)
                ++count;
            *write_iterator = ch;
            ++write_iterator;
            ++size;
            if (count > 1)
            {
                std::string countStr = std::to_string(count);
                write_iterator = std::copy(countStr.cbegin(), countStr.cend(), write_iterator);
                size += countStr.size();
            }
        }
        return static_cast<int>(size);
    }
};

}

namespace StringCompressionTask
{

TEST(StringCompressionTaskTests, Examples)
{
    Solution solution;
    std::vector<char> chars1({'a', 'a', 'b', 'b', 'c', 'c', 'c'});
    ASSERT_EQ(6, solution.compress(chars1));
    ASSERT_EQ(std::vector<char>({'a','2','b','2','c','3'}), std::vector<char>(chars1.cbegin(), chars1.cbegin() + 6));
    std::vector<char> chars2({'a'});
    ASSERT_EQ(1, solution.compress(chars2));
    ASSERT_EQ(std::vector<char>({'a'}), chars2);
    std::vector<char> chars3({'a','b','b','b','b','b','b','b','b','b','b','b','b'});
    ASSERT_EQ(4, solution.compress(chars3));
    ASSERT_EQ(std::vector<char>({'a','b','1','2'}), std::vector<char>(chars3.cbegin(), chars3.cbegin() + 4));
}

}