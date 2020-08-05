#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int compareVersion(std::string const &version1, std::string const &version2) const
    {
        std::string source1(version1);
        std::string source2(version2);
        while (!source1.empty() && !source2.empty())
        {
            size_t index1 = 0;
            size_t index2 = 0;
            const int component1 = std::stoi(source1, &index1);
            const int component2 = std::stoi(source2, &index2);
            if (component1 < component2)
                return -1;
            if (component2 < component1)
                return 1;
            source1 = source1.substr(index1 + (index1 < source1.size() ? 1 : 0));
            source2 = source2.substr(index2 + (index2 < source2.size() ? 1 : 0));
        }
        if (!source1.empty())
            return checkFooter(source1) ? 0 : 1;
        if (!source2.empty())
            return checkFooter(source2) ? 0 : -1;
        return 0;
    }

private:
    bool checkFooter(std::string const &source) const
    {
        for (char ch : source)
        {
            if (ch != '.' && ch != '0')
                return false;
        }
        return true;
    }
};

}

namespace CompareVersionNumbersTask
{

TEST(CompareVersionNumbersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(-1, solution.compareVersion("0.1", "1.1"));
    ASSERT_EQ(1, solution.compareVersion("1.0.1", "1"));
    ASSERT_EQ(-1, solution.compareVersion("7.5.2.4", "7.5.3"));
    ASSERT_EQ(0, solution.compareVersion("1.01", "1.001"));
    ASSERT_EQ(0, solution.compareVersion("1.0", "1.0.0"));
}

TEST(CompareVersionNumbersTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.compareVersion("01", "1"));
    ASSERT_EQ(-1, solution.compareVersion("1.0", "1.1"));
}

}