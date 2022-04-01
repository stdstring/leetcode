#include <stdexcept>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfWays(std::string const &corridor) const
    {
        constexpr uint64_t modValue = 1000000007;
        constexpr char seat = 'S';
        size_t currentGroupSize = 0;
        size_t currentGroupEnd = std::string::npos;
        uint64_t combinationsCount = 1;
        for (size_t index = 0; index < corridor.size(); ++index)
        {
            if (corridor[index] == seat)
            {
                switch (currentGroupSize)
                {
                    case 0:
                    case 1:
                        ++currentGroupSize;
                        break;
                    case 2:
                        currentGroupSize = 1;
                        combinationsCount = (combinationsCount * (index - currentGroupEnd)) % modValue;
                        break;
                    default:
                        throw std::logic_error("Unexpected execution branch");
                }
                currentGroupEnd = index;
            }
        }
        return currentGroupSize < 2 ? 0 : static_cast<int>(combinationsCount);
    }
};

}

namespace NumberOfWaysToDivideLongCorridorTask
{

TEST(NumberOfWaysToDivideLongCorridorTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.numberOfWays("SSPPSPS"));
    ASSERT_EQ(1, solution.numberOfWays("PPSPSP"));
    ASSERT_EQ(0, solution.numberOfWays("S"));
}

}