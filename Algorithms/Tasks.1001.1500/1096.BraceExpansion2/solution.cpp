#include <set>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> braceExpansionII(std::string const &expression) const
    {
        auto [parts, _] = processUnion(expression, 0);
        return {parts.cbegin(), parts.cend()};
    }

private:
    [[nodiscard]] std::pair<std::set<std::string>, size_t> processConcat(std::string const &expression, size_t start) const
    {
        size_t index = start;
        std::set<std::string> dest;
        while ((index < expression.size()) && (expression[index] != ',') && (expression[index] != '}'))
        {
            auto [part, partIndex] = (expression[index] == '{') ? processSet(expression, index) : processString(expression, index);
            if (dest.empty())
                std::swap(dest, part);
            else
                dest = concatSets(dest, part);
            index = partIndex;
        }
        return {dest, index};
    }

    [[nodiscard]] std::pair<std::set<std::string>, size_t> processUnion(std::string const &expression, size_t start) const
    {
        size_t index = start;
        std::set<std::string> dest;
        while ((index < expression.size()) && (expression[index] != '}'))
        {
            if (expression[index] == ',')
                ++index;
            auto [part, partIndex] = processConcat(expression, index);
            if (dest.empty())
                std::swap(dest, part);
            else
                dest = unionSets(dest, part);
            index = partIndex;
        }
        return { dest, index };
    }

    [[nodiscard]] std::pair<std::set<std::string>, size_t> processString(std::string const &expression, size_t start) const
    {
        size_t index = start;
        std::string dest;
        for (; std::islower(expression[index]) != 0; ++index)
            dest.push_back(expression[index]);
        return {std::set<std::string>({dest}), index};
    }

    [[nodiscard]] std::pair<std::set<std::string>, size_t> processSet(std::string const &expression, size_t start) const
    {
        // expression[start] == '{'
        std::set<std::string> dest;
        auto [result, resultIndex] = processUnion(expression, start + 1);
        // expression[resultIndex] == '}'
        return {result, resultIndex + 1};
    }

    [[nodiscard]] std::set<std::string> concatSets(std::set<std::string> const &left, std::set<std::string> const &right) const
    {
        std::set<std::string> result;
        for (std::string const &leftItem : left)
        {
            for (std::string const &rightItem : right)
                result.emplace(leftItem + rightItem);
        }
        return result;
    }

    [[nodiscard]] std::set<std::string> unionSets(std::set<std::string> const &left, std::set<std::string> const &right) const
    {
        std::set<std::string> result(left);
        for (std::string const &rightItem : right)
            result.emplace(rightItem);
        return result;
    }
};

}

namespace BraceExpansion2Task
{

TEST(BraceExpansion2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"ac", "ad", "ae", "bc", "bd", "be"}), solution.braceExpansionII("{a,b}{c,{d,e}}"));
    ASSERT_EQ(std::vector<std::string>({"a", "ab", "ac", "z"}), solution.braceExpansionII("{{a,z},a{b,c},{ab,z}}"));
}

TEST(BraceExpansion2TaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"abbc", "bbac"}), solution.braceExpansionII("{abb,bba}c"));
    ASSERT_EQ(std::vector<std::string>({"ac"}), solution.braceExpansionII("{a,a}c"));
    ASSERT_EQ(std::vector<std::string>({"ac", "ad", "bc", "bd"}), solution.braceExpansionII("{{a,b}{c,d}}"));
}

}
