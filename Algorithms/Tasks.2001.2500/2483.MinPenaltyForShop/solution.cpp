#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int bestClosingTime(std::string const &customers) const
    {
        const size_t customerCount = std::count(customers.cbegin(), customers.cend(), 'Y');
        size_t leftCustomerCount = 0;
        size_t closingTime = 0;
        size_t penalty = customerCount;
        for (size_t index = 0; index < customers.size(); ++index)
        {
            if (customers[index] == 'Y')
                ++leftCustomerCount;
            const size_t currentPenalty = (index + 1 - leftCustomerCount) + (customerCount - leftCustomerCount);
            if (currentPenalty < penalty)
            {
                penalty = currentPenalty;
                closingTime = index + 1;
            }
        }
        return static_cast<int>(closingTime);
    }
};

}

namespace MinPenaltyForShopTask
{

TEST(MinPenaltyForShopTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.bestClosingTime("YYNY"));
    ASSERT_EQ(0, solution.bestClosingTime("NNNNN"));
    ASSERT_EQ(4, solution.bestClosingTime("YYYY"));
}

}