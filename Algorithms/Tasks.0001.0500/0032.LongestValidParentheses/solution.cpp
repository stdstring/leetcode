#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

enum class ObjectType {OpenBracket, CloseBracket, ValidParentheses};

class Solution
{
public:
    [[nodiscard]] int longestValidParentheses(std::string const &s) const
    {
        std::vector<std::pair<ObjectType, size_t>> data;
        for (auto iterator = s.crbegin(); iterator != s.crend(); ++iterator)
        {
            bool hasChanges = false;
            switch (*iterator)
            {
                case ')':
                    data.emplace_back(ObjectType::CloseBracket, 0);
                    break;
                case '(':
                    if (!data.empty() && (data.back().first == ObjectType::CloseBracket))
                    {
                        data.back().first = ObjectType::ValidParentheses;
                        data.back().second = 2;
                        hasChanges = true;
                    }
                    if (!hasChanges &&
                        (data.size() > 1) &&
                        (data.back().first == ObjectType::ValidParentheses) &&
                        (data[data.size() - 2].first == ObjectType::CloseBracket))
                    {
                        const size_t innerSize = data.back().second;
                        data.pop_back();
                        data.back().first = ObjectType::ValidParentheses;
                        data.back().second = innerSize + 2;
                        hasChanges = true;
                    }
                    if ((data.size() > 1) &&
                        (data.back().first == ObjectType::ValidParentheses) &&
                        (data[data.size() - 2].first == ObjectType::ValidParentheses))
                    {
                        const size_t leftSize = data.back().second;
                        data.pop_back();
                        data.back().second += leftSize;
                    }
                    if (!hasChanges)
                        data.emplace_back(ObjectType::OpenBracket, 0);
                    break;
                default:
                    throw std::logic_error("Unexpected execution branch");
            }
        }
        size_t bestSize = 0;
        for (std::pair<ObjectType, size_t> const &entry : data)
            bestSize = std::max(bestSize, entry.second);
        return static_cast<int>(bestSize);
    }
};

}

namespace LongestValidParenthesesTask
{

TEST(LongestValidParenthesesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.longestValidParentheses("(()"));
    ASSERT_EQ(4, solution.longestValidParentheses(")()())"));
    ASSERT_EQ(0, solution.longestValidParentheses(""));
    ASSERT_EQ(0, solution.longestValidParentheses(")("));
}

}
