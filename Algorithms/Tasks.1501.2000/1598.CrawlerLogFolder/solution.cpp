#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minOperations(std::vector<std::string> const &logs) const
    {
        int level = 0;
        for (std::string const &log : logs)
        {
            if (log == "./")
                continue;
            if (log == "../")
            {
                if (level > 0)
                    --level;
                continue;
            }
            ++level;
        }
        return level;
    }
};

}

namespace CrawlerLogFolderTask
{

TEST(CrawlerLogFolderTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minOperations({"d1/", "d2/", "../", "d21/", "./"}));
    ASSERT_EQ(3, solution.minOperations({"d1/", "d2/", "./", "d3/", "../", "d31/"}));
    ASSERT_EQ(0, solution.minOperations({"d1/", "../", "../", "../"}));
}

}