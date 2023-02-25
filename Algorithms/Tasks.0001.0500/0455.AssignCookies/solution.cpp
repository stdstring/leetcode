#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findContentChildren(std::vector<int> const &g, std::vector<int> const &s) const
    {
        std::vector<int> children(g);
        std::sort(children.begin(), children.end());
        std::vector<int> cookies(s);
        std::sort(cookies.begin(), cookies.end());
        size_t contentChildrenCount = 0;
        size_t child = 0;
        size_t cookie = 0;
        while ((child < children.size()) && (cookie < cookies.size()))
        {
            if (cookies[cookie++] >= children[child])
            {
                ++contentChildrenCount;
                ++child;
            }
        }
        return static_cast<int>(contentChildrenCount);
    }
};

}

namespace AssignCookiesTask
{

TEST(AssignCookiesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.findContentChildren({1, 2, 3}, {1, 1}));
    ASSERT_EQ(2, solution.findContentChildren({1, 2}, {1, 2, 3}));
}

}