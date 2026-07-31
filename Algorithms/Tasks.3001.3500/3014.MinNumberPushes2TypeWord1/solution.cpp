#include <algorithm>
#include <ranges>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumPushes(std::string const &word) const
    {
        std::unordered_map<char, size_t> frequencies;
        for (const char ch : word)
            ++frequencies[ch];
        std::vector<size_t> data;
        for (const auto &count : frequencies | std::views::values)
            data.emplace_back(count);
        std::ranges::sort(data, std::greater<size_t>());
        size_t result = 0;
        constexpr size_t keyCount = 8;
        for (size_t index = 0; index < data.size(); ++index)
            result += data[index] * (1 + index / 8);
        return static_cast<int>(result);
    }
};

}

namespace MinNumberPushes2TypeWord1Task
{

TEST(MinNumberPushes2TypeWord1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.minimumPushes("abcde"));
    ASSERT_EQ(12, solution.minimumPushes("xycdefghij"));
}

}