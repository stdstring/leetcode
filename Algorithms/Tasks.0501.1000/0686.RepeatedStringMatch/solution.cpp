#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int repeatedStringMatch(std::string const &a, std::string const &b) const
    {
        if (a.size() >= b.size())
        {
            if (a.find(b) != std::string::npos)
                return 1;
            return (a + a).find(b) == std::string::npos ? -1 : 2;
        }
        for (size_t index = 0; index < a.size(); ++index)
        {
            if (a[index] == b[0])
            {
                const int repeatCount = tryMatch(a, b, index);
                if (repeatCount != -1)
                    return repeatCount;
            }
        }
        return -1;
    }

private:
    [[nodiscard]] bool checkPrefix(std::string const &a, std::string const &b, size_t start) const
    {
        for (size_t index = 0; index < a.size() - start; ++index)
        {
            if (a[start + index] != b[index])
                return false;
        }
        return true;
    }

    [[nodiscard]] bool checkPart(std::string const &a, std::string const &b, size_t start) const
    {
        const size_t restSize = b.size() - start;
        for (size_t index = 0; index < std::min(a.size(), restSize); ++index)
        {
            if (a[index] != b[start + index])
                return false;
        }
        return true;
    }

    [[nodiscard]] int tryMatch(std::string const &a, std::string const &b, size_t start) const
    {
        if (!checkPrefix(a, b, start))
            return -1;
        size_t repeatCount = 1;
        for (size_t totalSize = a.size() - start; totalSize < b.size(); totalSize += a.size(), ++repeatCount)
        {
            if (!checkPart(a, b, totalSize))
                return -1;
        }
        return static_cast<int>(repeatCount);
    }
};

}

namespace RepeatedStringMatchTask
{

TEST(RepeatedStringMatchTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.repeatedStringMatch("abcd", "cdabcdab"));
    ASSERT_EQ(2, solution.repeatedStringMatch("a", "aa"));
}

TEST(RepeatedStringMatchTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.repeatedStringMatch("aa", "a"));
    ASSERT_EQ(2, solution.repeatedStringMatch("aaaaaaaaaaaaaaaaaaaaaab", "ba"));
}

}