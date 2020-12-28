#include <cctype>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isValid(std::string const &code) const
    {
        size_t pos = 0;
        return isValid(code, pos) && pos == code.size();
    }

private:
    constexpr static char TagStart = '<';
    constexpr static char TagEnd = '>';
    static const std::string CloseTagStart;
    static const std::string CDataStart;
    static const std::string CDataEnd;

    bool isValid(std::string const &code, size_t &pos) const
    {
        // process '<'
        if (!isOpenTagStart(code, pos))
            return false;
        ++pos;
        // process open tag name
        std::string openTagName;
        if (!getValidTagName(code, pos, openTagName))
            return false;
        // process '>'
        if (!isTagEnd(code, pos))
            return false;
        ++pos;
        // process TAG_CONTENT
        if (!processTagContent(code, pos))
            return false;
        // process '</'
        if (!isCloseTagStart(code, pos))
            return false;
        pos += CloseTagStart.size();
        // process close tag name
        std::string closeTagName;
        if (!getValidTagName(code, pos, closeTagName))
            return false;
        if (openTagName != closeTagName)
            return false;
        // process '>'
        if (!isTagEnd(code, pos))
            return false;
        ++pos;
        return true;
    }

    bool processTagContent(std::string const &code, size_t &pos) const
    {
        while (pos < code.size())
        {
            if (code[pos] != TagStart)
            {
                ++pos;
                continue;
            }
            if (isCDataStart(code, pos))
            {
                if (!checkCData(code, pos))
                    return false;
                continue;
            }
            if (isCloseTagStart(code, pos))
                break;
            // process inner closed tag
            if (!isValid(code, pos))
                return false;
        }
        return true;
    }

    bool isOpenTagStart(std::string const &code, size_t const &pos) const
    {
        return pos < code.size() && code[pos] == TagStart;
    }

    bool isTagEnd(std::string const &code, size_t const &pos) const
    {
        return pos < code.size() && code[pos] == TagEnd;
    }

    bool isCloseTagStart(std::string const &code, size_t const &pos) const
    {
        return code.compare(pos, CloseTagStart.size(), CloseTagStart) == 0;
    }

    bool isCDataStart(std::string const &code, size_t const &pos) const
    {
        return code.compare(pos, CDataStart.size(), CDataStart) == 0;
    }

    bool getValidTagName(std::string const &code, size_t &pos, std::string &tagName) const
    {
        constexpr size_t minTagNameLength = 1;
        constexpr size_t maxTagNameLength = 9;
        while (pos < code.size() && code[pos] != TagEnd)
        {
            if (!std::isupper(code[pos]))
                return false;
            if (tagName.size() == maxTagNameLength)
                return false;
            tagName.push_back(code[pos++]);
        }
        return tagName.size() >= minTagNameLength;
    }

    bool checkCData(std::string const &code, size_t &pos) const
    {
        const size_t cDataEndPos = code.find(CDataEnd, pos);
        if (cDataEndPos == std::string::npos)
            return false;
        pos = cDataEndPos + CDataEnd.size();
        return true;
    }
};

const std::string Solution::CloseTagStart = "</";
const std::string Solution::CDataStart = "<![CDATA[";
const std::string Solution::CDataEnd = "]]>";

}

namespace TagValidatorTask
{

TEST(TagValidatorTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isValid("<DIV>This is the first line <![CDATA[<div>]]></DIV>"));
    ASSERT_EQ(true, solution.isValid("<DIV>>>  ![cdata[]] <![CDATA[<div>]>]]>]]>>]</DIV>"));
    ASSERT_EQ(false, solution.isValid("<A>  <B> </A>   </B>"));
    ASSERT_EQ(false, solution.isValid("<DIV>  div tag is not closed  <DIV>"));
    ASSERT_EQ(false, solution.isValid("<DIV>  unmatched <  </DIV>"));
    ASSERT_EQ(false, solution.isValid("<DIV> closed tags with invalid tag name  <b>123</b> </DIV>"));
    ASSERT_EQ(false, solution.isValid("<DIV> unmatched tags with invalid tag name  </1234567890> and <CDATA[[]]>  </DIV>"));
    ASSERT_EQ(false, solution.isValid("<DIV>  unmatched start tag <B>  and unmatched end tag </C>  </DIV>"));
}

TEST(TagValidatorTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.isValid("<A></A><B></B>"));
}

}