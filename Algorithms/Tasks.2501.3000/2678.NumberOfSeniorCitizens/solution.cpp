#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countSeniors(std::vector<std::string> const &details) const
    {
        // 10 - phone, 1 - gender, 2 - age, 2 - seat
        size_t seniorCount = 0;
        for (std::string const &person : details)
        {
            const int age = 10 * (person[11] - '0') + (person[12] - '0');
            if (age > 60)
                ++seniorCount;
        }
        return static_cast<int>(seniorCount);
    }
};

}

namespace NumberOfSeniorCitizensTask
{

TEST(NumberOfSeniorCitizensTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.countSeniors({"7868190130M7522", "5303914400F9211", "9273338290F4010"}));
    ASSERT_EQ(0, solution.countSeniors({"1313579440F2036", "2921522980M5644"}));
}

}