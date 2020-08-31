#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string countAndSay(int n) const
    {
        std::string current("1");
        for (int term = 2; term <= n; ++term)
            current = generateNext(current);
        return current;
    }

private:
    std::string generateNext(std::string const &current) const
    {
        std::string next;
        size_t index = 0;
        while (index < current.size())
        {
            const char digit = current[index];
            size_t count = 1;
            while ((index + count) < current.size() && current[index + count] == digit)
                ++count;
            next.append(std::to_string(count));
            next.push_back(digit);
            index += count;
        }
        return next;
    }
};

}

namespace CountAndSayTask
{

TEST(CountAndSayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("1", solution.countAndSay(1));
    ASSERT_EQ("11", solution.countAndSay(2));
    ASSERT_EQ("21", solution.countAndSay(3));
    ASSERT_EQ("1211", solution.countAndSay(4));
    ASSERT_EQ("111221", solution.countAndSay(5));
}

}