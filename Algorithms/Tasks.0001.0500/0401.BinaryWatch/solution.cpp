#include <cstdint>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::string> readBinaryWatch(int num) const
    {
        if (num == 0)
            return {"0:00"};
        std::vector<std::string> result;
        const uint32_t bitsCount = static_cast<uint32_t>(num);
        const uint32_t maxNumber = (1 << (hoursBitCount + minutesBitCount)) - 1;
        for (uint32_t number = 0; number <= maxNumber; ++number)
        {
            if (calcBitCount(number) == bitsCount)
            {
                const uint32_t hours = number >> minutesBitCount;
                const uint32_t minutes = number - (hours << minutesBitCount);
                if (hours <= hoursMax && minutes <= minutesMax)
                    result.push_back(createTimeRepresentation(hours, minutes));
            }
        }
        return result;
    }

private:
    constexpr static uint32_t hoursBitCount = 4;
    constexpr static uint32_t minutesBitCount = 6;
    constexpr static uint32_t hoursMax = 11;
    constexpr static uint32_t minutesMax = 59;

    uint32_t calcBitCount(uint32_t number) const
    {
        uint32_t bitCount = 0;
        while (number > 0)
        {
            if ((number & 1) == 1)
                ++bitCount;
            number >>= 1;
        }
        return bitCount;
    }

    std::string createTimeRepresentation(uint32_t hours, uint32_t minutes) const
    {
        return std::to_string(hours) + ":" + (minutes < 10 ? "0" : "") + std::to_string(minutes);
    }
};

}

namespace BinaryWatchTask
{

TEST(BinaryWatchTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"0:00"}), solution.readBinaryWatch(0));
    ASSERT_EQ(std::vector<std::string>({"0:01", "0:02", "0:04", "0:08", "0:16", "0:32", "1:00", "2:00", "4:00", "8:00"}), solution.readBinaryWatch(1));
}

}