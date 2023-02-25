#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string entityParser(std::string const &text) const
    {
        std::string dest;
        for (size_t index = 0; index < text.size();)
        {
            if (text[index] != '&')
                dest.push_back(text[index++]);
            else
            {
                std::pair<char, size_t> entity(parseEntity(text, index));
                dest.push_back(entity.first);
                index += entity.second;
            }
        }
        return dest;
    }

private:
    [[nodiscard]] std::pair<char, size_t> parseEntity(std::string const &source, size_t index) const
    {
        if (source.compare(index, 4, "&gt;") == 0)
            return {'>', 4};
        if (source.compare(index, 4, "&lt;") == 0)
            return {'<', 4};
        if (source.compare(index, 5, "&amp;") == 0)
            return {'&', 5};
        if (source.compare(index, 6, "&quot;") == 0)
            return {'\"', 6};
        if (source.compare(index, 6, "&apos;") == 0)
            return {'\'', 6};
        if (source.compare(index, 7, "&frasl;") == 0)
            return {'/', 7};
        return {'&', 1};
    }
};

}

namespace HTMLEntityParserTask
{

TEST(HTMLEntityParserTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("& is an HTML entity but &ambassador; is not.", solution.entityParser("&amp; is an HTML entity but &ambassador; is not."));
    ASSERT_EQ("and I quote: \"...\"", solution.entityParser("and I quote: &quot;...&quot;"));
    ASSERT_EQ("Stay home! Practice on Leetcode :)", solution.entityParser("Stay home! Practice on Leetcode :)"));
    ASSERT_EQ("x > y && x < y is always false", solution.entityParser("x &gt; y &amp;&amp; x &lt; y is always false"));
    ASSERT_EQ("leetcode.com/problemset/all", solution.entityParser("leetcode.com&frasl;problemset&frasl;all"));
}

}