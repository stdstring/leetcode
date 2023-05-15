#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"


namespace
{

class Solution
{
public:
    [[nodiscard]] std::string kthLargestNumber(std::vector<std::string> const &nums, int k) const
    {
        auto comparer = [](std::string const &l, std::string const &r)
        {
            if (l.size() < r.size())
                return false;
            if (l.size() > r.size())
                return true;
            for (size_t index = 0; index < l.size(); ++index)
            {
                if (l[index] < r[index])
                    return false;
                if (l[index] > r[index])
                    return true;
            }
            return false;
        };
        std::vector<std::string> numbers(nums);
        const auto kIterator = std::next(numbers.begin(), k - 1);
        std::nth_element(numbers.begin(), kIterator, numbers.end(), comparer);
        return *kIterator;
    }
};

}

namespace FindKthLargestIntegerInArrayTask
{

TEST(FindKthLargestIntegerInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("3", solution.kthLargestNumber({"3", "6", "7", "10"}, 4));
    ASSERT_EQ("2", solution.kthLargestNumber({"2", "21", "12", "1"}, 3));
    ASSERT_EQ("0", solution.kthLargestNumber({"0", "0"}, 2));
}

}