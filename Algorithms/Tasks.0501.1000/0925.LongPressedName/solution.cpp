#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isLongPressedName(std::string const &name, std::string const &typed) const
    {
        size_t nameIndex = 0;
        size_t typedIndex = 0;
        while (nameIndex < name.size() || typedIndex < typed.size())
        {
            if (nameIndex < name.size() && name[nameIndex] == typed[typedIndex])
            {
                ++nameIndex;
                ++typedIndex;
            }
            else if (nameIndex > 0 && name[nameIndex - 1] == typed[typedIndex])
                ++typedIndex;
            else
                return false;
        }
        return nameIndex == name.size() && typedIndex == typed.size();
    }
};

}

namespace LongPressedNameTask
{

TEST(LongPressedNameTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isLongPressedName("alex", "aaleex"));
    ASSERT_EQ(false, solution.isLongPressedName("saeed", "ssaaedd"));
    ASSERT_EQ(true, solution.isLongPressedName("leelee", "lleeelee"));
    ASSERT_EQ(true, solution.isLongPressedName("laiden", "laiden"));
}

TEST(LongPressedNameTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isLongPressedName("vtkgn", "vttkgnn"));
}

}
