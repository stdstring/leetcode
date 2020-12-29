#include <cctype>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class NestedInteger
{
public:
    // Constructor initializes an empty nested list.
    NestedInteger() : _contentType(ContentType::Number), _number(0)
    {
    }

    // Constructor initializes a single integer.
    explicit NestedInteger(int value) : _contentType(ContentType::Number), _number(value)
    {
    }

    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const
    {
        return _contentType == ContentType::Number;
    }

    // Return the single integer that this NestedInteger holds, if it holds a single integer.
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const
    {
        return _number;
    }

    // Set this NestedInteger to hold a single integer.
    void setInteger(int value)
    {
        _contentType = ContentType::Number;
        _number = value;
        _list.clear();
    }

    // Set this NestedInteger to hold a nested list and adds a nested integer to it.
    void add(NestedInteger const &ni)
    {
        _contentType = ContentType::List;
        _list.push_back(ni);
        _number = 0;
    }

    // Return the nested list that this NestedInteger holds, if it holds a nested list.
    // The result is undefined if this NestedInteger holds a single integer
    std::vector<NestedInteger> const &getList() const
    {
        return _list;
    }

private:
    enum ContentType { Number, List };
    ContentType _contentType;
    int _number;
    std::vector<NestedInteger> _list;
};

class Solution
{
public:
    NestedInteger deserialize(std::string const &s) const
    {
        size_t pos = 0;
        return s[pos] == ListStart ? readList(s, pos) : readNumber(s, pos);
    }

private:
    constexpr static char Delimiter = ',';
    constexpr static char ListStart = '[';
    constexpr static char ListEnd = ']';

    NestedInteger readNumber(std::string const &source, size_t &pos) const
    {
        int sign = 1;
        if (source[pos] == '-')
        {
            sign = -1;
            ++pos;
        }
        int number = 0;
        while (pos < source.size() && std::isdigit(source[pos]))
            number = 10 * number + (source[pos++] - '0');
        return NestedInteger(sign * number);
    }

    NestedInteger readList(std::string const &source, size_t &pos) const
    {
        NestedInteger result;
        // process '['
        ++pos;
        while (source[pos] != ListEnd)
        {
            // process ','
            if (source[pos] == Delimiter)
                ++pos;
            // process inner list
            else if (source[pos] == ListStart)
                result.add(readList(source, pos));
            // process number
            else
                result.add(readNumber(source, pos));
        }
        // process ']'
        ++pos;
        return result;
    }
};

}

namespace
{

void checkNestedNumber(int expectedValue, NestedInteger const &ni)
{
    ASSERT_TRUE(ni.isInteger());
    ASSERT_EQ(expectedValue, ni.getInteger());
}

void checkNestedList(int expectedSize, NestedInteger const &ni)
{
    ASSERT_FALSE(ni.isInteger());
    ASSERT_EQ(expectedSize, ni.getList().size());
}

}

namespace MiniParserTask
{

TEST(MiniParserTaskTests, Examples)
{
    const Solution solution;
    // example 1
    checkNestedNumber(324, solution.deserialize("324"));
    // example 2
    const NestedInteger example2Result = solution.deserialize("[123,[456,[789]]]");
    checkNestedList(2, example2Result);
    checkNestedNumber(123, example2Result.getList()[0]);
    checkNestedList(2, example2Result.getList()[1]);
    checkNestedNumber(456, example2Result.getList()[1].getList()[0]);
    checkNestedList(1, example2Result.getList()[1].getList()[1]);
    checkNestedNumber(789, example2Result.getList()[1].getList()[1].getList()[0]);
}

}