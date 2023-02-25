#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string evaluate(std::string const &s, std::vector<std::vector<std::string>> const &knowledge) const
    {
        std::unordered_map<std::string, std::string> knowledgeMap;
        for (std::vector<std::string> const &entry : knowledge)
            knowledgeMap[entry[0]] = entry[1];
        std::string dest;
        size_t index = 0;
        while (index < s.size())
        {
            if (s[index] != '(')
                dest.push_back(s[index++]);
            else
            {
                std::string key(readKey(s, index));
                dest.append(knowledgeMap.count(key) == 0 ? "?" : knowledgeMap[key]);
            }
        }
        return dest;
    }

private:
    std::string readKey(std::string const &source, size_t &index) const
    {
        // read '('
        ++index;
        const size_t start = index;
        while (source[index] != ')')
            ++index;
        const size_t finish = index;
        // read ')'
        ++index;
        return source.substr(start, finish - start);
    }
};

}

namespace EvaluateBracketPairsOfStringTask
{

TEST(EvaluateBracketPairsOfStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("bobistwoyearsold", solution.evaluate("(name)is(age)yearsold", {{"name", "bob"}, {"age", "two"}}));
    ASSERT_EQ("hi?", solution.evaluate("hi(name)", {{"a", "b"}}));
    ASSERT_EQ("yesyesyesaaa", solution.evaluate("(a)(a)(a)aaa", {{"a", "yes"}}));
    ASSERT_EQ("ba", solution.evaluate("(a)(b)", {{"a", "b"}, {"b", "a"}}));
}

}
