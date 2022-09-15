#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findOriginalArray(std::vector<int> const &changed) const
    {
        std::map<int, size_t> values;
        for (int number : changed)
        {
            auto iterator = values.find(number);
            if (iterator == values.end())
                iterator = values.emplace(number, 0).first;
            ++iterator->second;
        }
        std::vector<int> original;
        for (auto iterator = values.cbegin(); iterator != values.cend(); ++iterator)
        {
            if (iterator->first == 0)
            {
                if ((iterator->second % 2) != 0)
                    return {};
                appendValue(original, 0, iterator->second / 2);
                continue;
            }
            if (iterator->second > 0)
            {
                auto doubleValueIterator = values.find(2 * iterator->first);
                if ((doubleValueIterator == values.cend()) || (doubleValueIterator->second < iterator->second))
                    return {};
                doubleValueIterator->second -= iterator->second;
                appendValue(original, iterator->first, iterator->second);
            }
        }
        return original;
    }

private:
    void appendValue(std::vector<int> &dest, int value, size_t count) const
    {
        for (size_t item = 0; item < count; ++item)
            dest.push_back(value);
    }
};

}

namespace FindOriginalArrayFromDoubledArrayTask
{

TEST(FindOriginalArrayFromDoubledArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 3, 4}), solution.findOriginalArray({1, 3, 4, 2, 6, 8}));
    ASSERT_EQ(std::vector<int>(), solution.findOriginalArray({6, 3, 0, 1}));
    ASSERT_EQ(std::vector<int>(), solution.findOriginalArray({1}));
}

TEST(FindOriginalArrayFromDoubledArrayTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 0}), solution.findOriginalArray({0, 0, 0, 0}));
}

}
