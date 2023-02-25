#include <stack>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class FreqStack
{
public:
    FreqStack() = default;

    void push(int value)
    {
        const size_t level = (++_valuesMap[value]);
        if (_levels.size() < level)
            _levels.emplace_back();
        _levels[level - 1].push(value);
    }

    int pop()
    {
        const int value = _levels.back().top();
        const size_t level = (--_valuesMap[value]);
        if (level == 0)
            _valuesMap.erase(value);
        _levels.back().pop();
        if (_levels.back().empty())
            _levels.pop_back();
        return value;
    }

private:
    std::unordered_map<int, size_t> _valuesMap;
    std::vector<std::stack<int>> _levels;
};

}

namespace MaxFrequencyStackTask
{

TEST(MaxFrequencyStackTaskTests, Examples)
{
    FreqStack freqStack;
    ASSERT_NO_THROW(freqStack.push(5));
    ASSERT_NO_THROW(freqStack.push(7));
    ASSERT_NO_THROW(freqStack.push(5));
    ASSERT_NO_THROW(freqStack.push(7));
    ASSERT_NO_THROW(freqStack.push(4));
    ASSERT_NO_THROW(freqStack.push(5));
    ASSERT_EQ(5, freqStack.pop());
    ASSERT_EQ(7, freqStack.pop());
    ASSERT_EQ(5, freqStack.pop());
    ASSERT_EQ(4, freqStack.pop());
}

}