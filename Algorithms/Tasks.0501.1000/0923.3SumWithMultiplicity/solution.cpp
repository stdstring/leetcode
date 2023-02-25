#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int threeSumMulti(std::vector<int> const &arr, int target) const
    {
        constexpr size_t modValue = 1000000007;
        constexpr int minValue = 0;
        constexpr int maxValue = 100;
        std::vector<size_t> numbers(0LL + maxValue - minValue + 1, 0);
        for (const int number : arr)
            ++numbers[0LL + number - minValue];
        uint64_t count = 0;
        for (int first = 0; first <= maxValue; ++first)
        {
            if (numbers[first] == 0)
                continue;
            if (3 * first > target)
                break;
            if (3 * first == target)
                count = (count + calcCombinationsNumber3(numbers[first])) % modValue;
            const int targetRest = target - first;
            if ((targetRest - first > first) && (targetRest - first <= maxValue))
                    count = (count + calcCombinationsNumber2(numbers[first]) * numbers[0LL + targetRest - first]) % modValue;
            for (int second = first + 1; second <= maxValue; ++second)
            {
                if (numbers[second] == 0)
                    continue;
                if (2 * second > targetRest)
                    break;
                if (2 * second == targetRest)
                    count = (count + numbers[first] * calcCombinationsNumber2(numbers[second])) % modValue;
                for (int third = second + 1; third <= maxValue; ++third)
                {
                    if (numbers[third] == 0)
                        continue;
                    if (second + third > targetRest)
                        break;
                    if (second + third == targetRest)
                        count = (count + numbers[first] * numbers[second] * numbers[third]) % modValue;
                }
            }
        }
        return static_cast<int>(count);
    }

private:
    [[nodiscard]] uint64_t calcCombinationsNumber2(uint64_t n) const
    {
        return n * (n - 1) / 2;
    }

    [[nodiscard]] uint64_t calcCombinationsNumber3(uint64_t n) const
    {
        return n * (n - 1) * (n - 2) / 6;
    }
};

}

namespace ThreeSumWithMultiplicity
{

TEST(ThreeSumWithMultiplicityTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(20, solution.threeSumMulti({1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, 8));
    ASSERT_EQ(12, solution.threeSumMulti({1, 1, 2, 2, 2, 2}, 5));
}

TEST(ThreeSumWithMultiplicityTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(5166, solution.threeSumMulti({92, 4, 59, 23, 100, 16, 7, 15, 3, 78, 98, 17, 77, 33, 83, 15, 87, 35, 54, 72,
                                            58, 14, 87, 47, 58, 31, 72, 58, 87, 22, 25, 54, 27, 53, 13, 54, 61, 12, 96, 24,
                                            35, 43, 94, 1, 88, 76, 89, 89, 41, 56, 61, 65, 60, 91, 89, 79, 86, 52, 27, 2,
                                            97, 46, 50, 46, 87, 93, 71, 87, 95, 78, 65, 10, 35, 51, 34, 66, 61, 7, 49, 38,
                                            10, 1, 88, 37, 50, 84, 35, 20, 7, 83, 51, 85, 11, 12, 89, 93, 54, 23, 36, 95,
                                            100, 19, 82, 67, 96, 77, 53, 56, 51, 16, 54, 7, 30, 68, 78, 13, 38, 52, 91, 44,
                                            54, 17, 21, 44, 4, 10, 85, 19, 11, 88, 73, 36, 47, 53, 3, 21, 41, 24, 60, 53,
                                            88, 35, 48, 89, 35, 3, 43, 85, 45, 67, 56, 78, 44, 49, 29, 35, 68, 96, 29, 21,
                                            51, 17, 52, 99, 3, 48, 65, 51, 22, 38, 77, 81, 30, 64, 99, 35, 88, 72, 73, 29, 29, 2}, 105));
}

}