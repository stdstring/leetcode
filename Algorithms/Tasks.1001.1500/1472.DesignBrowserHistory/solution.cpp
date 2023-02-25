#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class BrowserHistory
{
public:
    BrowserHistory(std::string const &homepage) : _homepage(homepage), _index(npos), _count(0)
    {
    }

    void visit(std::string const &url)
    {
        if (_history.empty() || (_index == _history.size() - 1))
        {
            _history.push_back(url);
            _count = _history.size();
            _index = _count - 1;
        }
        else
        {
            _index = _index == npos ? 0 : _index + 1;
            _history[_index] = url;
            _count = _index + 1;
        }
    }

    std::string back(int steps)
    {
        const size_t shift = steps;
        _index = (_index == npos) || (_index < shift) ? npos : _index - shift;
        return _index == npos ? _homepage : _history[_index];
    }

    std::string forward(int steps)
    {
        const size_t shift = steps;
        if (_count == 0)
            return _homepage;
        _index = std::min(_count - 1, _index == npos ? shift - 1 : _index + shift);
        return _history[_index];
    }

private:
    constexpr static size_t npos = -1;

    std::string _homepage;
    std::vector<std::string> _history;
    size_t _index;
    size_t _count;
};

}

namespace DesignBrowserHistoryTask
{

TEST(DesignBrowserHistoryTaskTests, Examples)
{
    BrowserHistory history("leetcode.com");
    ASSERT_NO_THROW(history.visit("google.com"));
    ASSERT_NO_THROW(history.visit("facebook.com"));
    ASSERT_NO_THROW(history.visit("youtube.com"));
    ASSERT_EQ("facebook.com", history.back(1));
    ASSERT_EQ("google.com", history.back(1));
    ASSERT_EQ("facebook.com", history.forward(1));
    ASSERT_NO_THROW(history.visit("linkedin.com"));
    ASSERT_EQ("linkedin.com", history.forward(2));
    ASSERT_EQ("google.com", history.back(2));
    ASSERT_EQ("leetcode.com", history.back(7));
}

TEST(DesignBrowserHistoryTaskTests, FromWrongAnswers)
{
    BrowserHistory history("jrbilt.com");
    ASSERT_NO_THROW(history.visit("uiza.com"));
    ASSERT_EQ("uiza.com", history.forward(3));
    ASSERT_EQ("uiza.com", history.forward(3));
    ASSERT_NO_THROW(history.visit("fveyl.com"));
    ASSERT_NO_THROW(history.visit("hyhqfqf.com"));
    ASSERT_EQ("jrbilt.com", history.back(3));
    ASSERT_NO_THROW(history.visit("cccs.com"));
    ASSERT_NO_THROW(history.visit("bivz.com"));
    ASSERT_EQ("bivz.com", history.forward(6));
    ASSERT_EQ("cccs.com", history.back(1));
    ASSERT_NO_THROW(history.visit("cmbw.com"));
    ASSERT_NO_THROW(history.visit("iywwwfn.com"));
    ASSERT_NO_THROW(history.visit("sktbhdx.com"));
    ASSERT_EQ("sktbhdx.com", history.forward(8));
    ASSERT_EQ("sktbhdx.com", history.forward(10));
    ASSERT_NO_THROW(history.visit("bskj.com"));
    ASSERT_NO_THROW(history.visit("thw.com"));
    ASSERT_EQ("jrbilt.com", history.back(6));
    ASSERT_NO_THROW(history.visit("hgesj.com"));
    ASSERT_EQ("hgesj.com", history.forward(6));
    ASSERT_NO_THROW(history.visit("ctb.com"));
    ASSERT_NO_THROW(history.visit("fllnc.com"));
    ASSERT_NO_THROW(history.visit("fs.com"));
    ASSERT_EQ("jrbilt.com", history.back(7));
}

}
