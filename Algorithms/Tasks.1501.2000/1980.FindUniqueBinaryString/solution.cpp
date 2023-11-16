#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string findDifferentBinaryString(std::vector<std::string> const &nums) const
    {
        const int totalNumbersCount = 1 << nums.front().size();
        std::vector<bool> existingNumbers(totalNumbersCount, false);
        for (std::string const& number : nums)
            existingNumbers[convertToNumber(number)] = true;
        for (int number = 0; number < totalNumbersCount; ++number)
        {
            if (!existingNumbers[number])
                return convertToString(number, nums.front().size());
        }
        return "";
    }

private:
    [[nodiscard]] int convertToNumber(std::string const &source) const
    {
        int result = 0;
        for (size_t index = 0; index < source.size(); ++index)
            result += (source[source.size() - 1 - index] == '0' ? 0 : 1) << index;
        return result;
    }

    [[nodiscard]] std::string convertToString(int number, size_t size) const
    {
        std::string result(size, '0');
        for (size_t index = 0; index < size; ++index)
        {
            if (number == 0)
                break;
            result[size - 1 - index] = (number & 1) == 1 ? '1' : '0';
            number >>= 1;
        }
        return result;
    }
};

}

namespace FindUniqueBinaryStringTask
{

TEST(FindUniqueBinaryStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("00", solution.findDifferentBinaryString({"01", "10"}));
    ASSERT_EQ("10", solution.findDifferentBinaryString({"00", "01"}));
    ASSERT_EQ("000", solution.findDifferentBinaryString({"111", "011", "001"}));
}

}