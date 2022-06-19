#include <algorithm>
#include <deque>
#include <string>

#include "gtest/gtest.h"

namespace
{

class TextEditor
{
public:
    TextEditor() = default;

    void addText(std::string const &text)
    {
        for (char ch : text)
            _prefix.push_back(ch);
    }

    int deleteText(int k)
    {
        int deletedCount = 0;
        while ((deletedCount < k) && !_prefix.empty())
        {
            _prefix.pop_back();
            ++deletedCount;
        }
        return deletedCount;
    }

    std::string cursorLeft(int k)
    {
        for (size_t moveCount = 0; (moveCount < static_cast<size_t>(k)) && !_prefix.empty(); ++moveCount)
        {
            _suffix.push_front(_prefix.back());
            _prefix.pop_back();
        }
        return getLastLeftChars();
    }

    std::string cursorRight(int k)
    {
        for (size_t moveCount = 0; (moveCount < static_cast<size_t>(k)) && !_suffix.empty(); ++moveCount)
        {
            _prefix.push_back(_suffix.front());
            _suffix.pop_front();
        }
        return getLastLeftChars();
    }

private:
    static constexpr size_t MaxCharCount = 10;

    std::deque<char> _prefix;
    std::deque<char> _suffix;

    [[nodiscard]] std::string getLastLeftChars() const
    {
        auto begin = std::prev(_prefix.cend(), static_cast<int>(std::min(MaxCharCount, _prefix.size())));
        return {begin, _prefix.cend()};
    }
};

}

namespace DesignTextEditorTask
{

TEST(DesignTextEditorTaskTests, Examples)
{
    TextEditor editor;
    ASSERT_NO_THROW(editor.addText("leetcode"));
    ASSERT_EQ(4, editor.deleteText(4));
    ASSERT_NO_THROW(editor.addText("practice"));
    ASSERT_EQ("etpractice", editor.cursorRight(3));
    ASSERT_EQ("leet", editor.cursorLeft(8));
    ASSERT_EQ(4, editor.deleteText(10));
    ASSERT_EQ("", editor.cursorLeft(2));
    ASSERT_EQ("practi", editor.cursorRight(6));
}

}