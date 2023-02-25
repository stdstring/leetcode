#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string reformat(std::string const &s) const
    {
        std::vector<char> letters;
        std::vector<char> digits;
        for (char ch : s)
            (std::isdigit(ch) ? letters : digits).push_back(ch);
        const size_t deltaSize = letters.size() > digits.size() ? letters.size() - digits.size() : digits.size() - letters.size();
        if (deltaSize > 1)
            return "";
        std::string result;
        for (size_t lettersIndex = 0, digitsIndex = 0; lettersIndex < letters.size() || digitsIndex < digits.size();)
        {
            if (result.empty())
                result.push_back(letters.size() > digits.size() ? letters[lettersIndex++] : digits[digitsIndex++]);
            else
                result.push_back(std::isdigit(result.back()) == 0 ? letters[lettersIndex++] : digits[digitsIndex++]);
        }
        return result;
    }
};

}

namespace ReformatTheStringTask
{

TEST(ReformatTheStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("a0b1c2", solution.reformat("a0b1c2"));
    ASSERT_EQ("", solution.reformat("leetcode"));
    ASSERT_EQ("", solution.reformat("1229857369"));
}

TEST(ReformatTheStringTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("c2o0v1i9d", solution.reformat("covid2019"));
}

}