#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> substringXorQueries(std::string const &s, std::vector<std::vector<int>> const &queries) const
    {
        constexpr size_t maxSize = 30;
        std::unordered_map<int, std::vector<int>> existingNumbers;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (s[index] == '0')
            {
                existingNumbers.emplace(0, std::vector<int>({static_cast<int>(index), static_cast<int>(index)}));
                continue;
            }
            int value = 1;
            existingNumbers.emplace(1, std::vector<int>({static_cast<int>(index), static_cast<int>(index)}));
            for (size_t shift = 1; shift < maxSize; ++shift)
            {
                if ((index + shift) == s.size())
                    break;
                value = (value << 1) + (s[index + shift] == '1' ? 1 : 0);
                existingNumbers.emplace(value, std::vector<int>({static_cast<int>(index), static_cast<int>(index + shift)}));
            }
        }
        std::vector<std::vector<int>> result;
        for (std::vector<int> const &query : queries)
        {
            const int first = query[0];
            const int second = query[1];
            auto iterator = existingNumbers.find(first ^ second);
            result.emplace_back(iterator == existingNumbers.cend() ? std::vector<int>({-1, -1}) : iterator->second);
        }
        return result;
    }
};

}

namespace SubstringXORQueriesTask
{

TEST(SubstringXORQueriesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 2}, {2, 3}}), solution.substringXorQueries("101101", {{0, 5}, {1, 2}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{-1, -1}}), solution.substringXorQueries("0101", {{12, 8}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 0}}), solution.substringXorQueries("1", {{4, 5}}));
}

}