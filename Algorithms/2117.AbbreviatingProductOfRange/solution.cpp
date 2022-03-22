#include <cstdint>
#include <cmath>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string abbreviateProduct(int left, int right) const
    {
        // 10 ^ 11
        constexpr uint64_t directProductBorder = 10000000000;
        // 10 ^ 5
        constexpr int lastDigitsModValue = 100000;
        uint64_t directProduct = 1;
        size_t trailingZerosCount = 0;
        size_t divider2Count = 0;
        size_t divider5Count = 0;
        uint64_t lastDigits = 1;
        long double numbersLogSum = 0;
        for (int number = left; number <= right; ++number)
        {
            numbersLogSum += std::log10(number);
            auto [numberWithout2, count2] = extractDivider(number, 2);
            auto [numberWithout25, count5] = extractDivider(numberWithout2, 5);
            lastDigits = (lastDigits * numberWithout25) % lastDigitsModValue;
            directProduct *= numberWithout25;
            if (directProduct >= directProductBorder)
                directProduct = 0;
            divider2Count += count2;
            divider5Count += count5;
            if (divider2Count < divider5Count)
            {
                trailingZerosCount += divider2Count;
                divider5Count -= divider2Count;
                divider2Count = 0;
            }
            else
            {
                trailingZerosCount += divider5Count;
                divider2Count -= divider5Count;
                divider5Count = 0;
            }
        }
        const std::string trailingZerosStr(std::to_string(trailingZerosCount));
        directProduct = tryDirectMultDivider(tryDirectMultDivider(directProduct, 2, divider2Count, directProductBorder), 5, divider5Count, directProductBorder);
        if (directProduct != 0)
            return std::to_string(directProduct).append("e").append(trailingZerosStr);
        lastDigits = multDivider(multDivider(lastDigits, 2, divider2Count, lastDigitsModValue), 5, divider5Count, lastDigitsModValue);
        const long double fractionalPart = std::fmod(numbersLogSum, 1);
        const int firstDigits = static_cast<int>(std::floor(std::pow(10.0, 4.0 + fractionalPart)));
        std::string firstDigitsStr(std::to_string(firstDigits));
        const std::string lastDigitsStr(std::to_string(lastDigits));
        return firstDigitsStr.append("...").append(5 - lastDigitsStr.size(), '0').append(lastDigitsStr).append("e").append(trailingZerosStr);
    }

private:
    [[nodiscard]] std::pair<uint64_t, size_t> extractDivider(uint64_t number, int divider) const
    {
        size_t count = 0;
        while ((number > 1) && (number % divider == 0))
        {
            number /= divider;
            ++count;
        }
        return {number, count};
    }

    [[nodiscard]] uint64_t tryDirectMultDivider(uint64_t number, int divider, size_t count, uint64_t border) const
    {
        if (number == 0)
            return 0;
        for (size_t index = 0; index < count; ++index)
        {
            number *= divider;
            if (number >= border)
            {
                number = 0;
                break;
            }
        }
        return number;
    }

    [[nodiscard]] uint64_t multDivider(uint64_t number, int divider, size_t count, int modValue) const
    {
        for (size_t index = 0; index < count; ++index)
            number = (divider * number) % modValue;
        return number;
    }
};

}

namespace AbbreviatingProductOfRangeTask
{

TEST(AbbreviatingProductOfRangeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("24e0", solution.abbreviateProduct(1, 4));
    ASSERT_EQ("399168e2", solution.abbreviateProduct(2, 11));
    ASSERT_EQ("7219856259e3", solution.abbreviateProduct(371, 375));
}

TEST(AbbreviatingProductOfRangeTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("10205...06688e2378", solution.abbreviateProduct(44, 9556));
    ASSERT_EQ("9385007814e4", solution.abbreviateProduct(621, 625));
    ASSERT_EQ("10054...62035e1", solution.abbreviateProduct(4649, 4651));
}

}