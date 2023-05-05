#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> kthSmallestPrimeFraction(std::vector<int> const &arr, int k) const
    {
        std::vector<RationalNumber> numbers;
        for (size_t numeratorIndex = 0; numeratorIndex < arr.size() - 1; ++numeratorIndex)
        {
            for (size_t denominatorIndex = numeratorIndex + 1; denominatorIndex < arr.size(); ++denominatorIndex)
                numbers.emplace_back(arr[numeratorIndex], arr[denominatorIndex]);
        }
        const auto kthIterator = std::next(numbers.begin(), k - 1);
        auto comp = [](RationalNumber const& l, RationalNumber const& r) { return l.Numerator * r.Denominator < r.Numerator * l.Denominator; };
        std::nth_element(numbers.begin(), kthIterator, numbers.end(), comp);
        return {kthIterator->Numerator, kthIterator->Denominator};
    }

private:
    struct RationalNumber
    {
        RationalNumber(int numerator, int denominator) : Numerator(numerator), Denominator(denominator)
        {
        }
        int Numerator;
        int Denominator;
    };
};

}

namespace KthSmallestPrimeFractionTask
{

TEST(KthSmallestPrimeFractionTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 5}), solution.kthSmallestPrimeFraction({1, 2, 3, 5}, 3));
    ASSERT_EQ(std::vector<int>({1, 7}), solution.kthSmallestPrimeFraction({1, 7}, 1));
}

}