#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> diStringMatch(std::string const &s) const
    {
        int left = 0;
        int right = static_cast<int>(s.size());
        std::vector<int> permutation;
        permutation.reserve(s.size() + 1);
        permutation.push_back(s.front() == 'I' ? left++ : right--);
        for (size_t index = 0; index < s.size();)
        {
            const int count = static_cast<int>(calcSameLetters(s, index));
            switch (s[index])
            {
                case 'I':
                    for (int number = right - (count - 1); number <= right; ++number)
                        permutation.push_back(number);
                    right -= count;
                    break;
                case 'D':
                    for (int number = left + (count - 1); number >= left; --number)
                        permutation.push_back(number);
                    left += count;
                    break;
                default:
                    throw std::logic_error("Bad character");
            }
            index += count;
        }
        return permutation;
    }

private:
    [[nodiscard]] size_t calcSameLetters(std::string const &s, size_t start) const
    {
        size_t count = 0;
        for (size_t index = start; (index < s.size()) && (s[index] == s[start]); ++index)
            ++count;
        return count;
    }
};

}

namespace DIStringMatchTask
{

TEST(DIStringMatchTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 4, 1, 3, 2}), solution.diStringMatch("IDID"));
    ASSERT_EQ(std::vector<int>({0, 1, 2, 3}), solution.diStringMatch("III"));
    ASSERT_EQ(std::vector<int>({3, 1, 0, 2}), solution.diStringMatch("DDI"));
}

}
