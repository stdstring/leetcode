#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfBeams(std::vector<std::string> const &bank) const
    {
        size_t beamsCount = 0;
        size_t prevDeviceCount = 0;
        for (std::string const &bankFloor : bank)
        {
            const size_t deviceCount = std::count(bankFloor.cbegin(), bankFloor.cend(), '1');
            if (deviceCount > 0)
            {
                beamsCount += (deviceCount * prevDeviceCount);
                prevDeviceCount = deviceCount;
            }
        }
        return static_cast<int>(beamsCount);
    }
};

}

namespace NumberOfLaserBeamsInBankTask
{

TEST(NumberOfLaserBeamsInBankTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(8, solution.numberOfBeams({"011001", "000000", "010100", "001000"}));
    ASSERT_EQ(0, solution.numberOfBeams({"000", "111", "000"}));
}

}