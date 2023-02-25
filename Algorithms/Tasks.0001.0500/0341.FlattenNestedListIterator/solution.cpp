#include <algorithm>
#include <iterator>
#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class NestedInteger
{
public:
    explicit NestedInteger(int value) : _isInteger(true), _value(value)
    {
    }

    explicit NestedInteger(std::vector<NestedInteger> nestedValues) : _isInteger(false), _value(0), _nestedValues(std::move(nestedValues))
    {
    }

    explicit NestedInteger(std::vector<int> const &nestedValues) : _isInteger(false), _value(0)
    {
        std::transform(nestedValues.cbegin(), nestedValues.cend(), std::back_inserter(_nestedValues), [](int value) { return NestedInteger(value); });
    }

    NestedInteger(NestedInteger const&) = default;
    NestedInteger(NestedInteger&&) = default;
    NestedInteger& operator=(NestedInteger const&) = delete;
    NestedInteger& operator=(NestedInteger&&) = delete;
    ~NestedInteger() = default;

    bool isInteger() const
    {
        return _isInteger;
    }

    int getInteger() const
    {
        return _value;
    }

    std::vector<NestedInteger> const& getList() const
    {
        return _nestedValues;
    }

private:
    bool _isInteger;
    int _value;
    std::vector<NestedInteger> _nestedValues;
};

class NestedIteratorWithPreprocessing
{
public:
    NestedIteratorWithPreprocessing(std::vector<NestedInteger> const &nestedList) : _index(0)
    {
        flatten(nestedList, _data);
    }

    int next()
    {
        return _data[_index++];
    }

    bool hasNext() const
    {
        return _index < _data.size();
    }

private:
    std::vector<int> _data;
    size_t _index;

    void flatten(std::vector<NestedInteger> const &source, std::vector<int> &dest)
    {
        for (NestedInteger const &entry : source)
        {
            if (entry.isInteger())
                dest.push_back(entry.getInteger());
            else
                flatten(entry.getList(), dest);
        }
    }
};

struct Iterator
{
    Iterator(std::vector<NestedInteger>::const_iterator const &current, std::vector<NestedInteger>::const_iterator const &end) : current(current), end(end)
    {
    }

    bool hasNext() const
    {
        return current != end;
    }

    std::vector<NestedInteger>::const_iterator current;
    std::vector<NestedInteger>::const_iterator end;
};

class NestedIterator
{
public:
    NestedIterator(std::vector<NestedInteger> const &nestedList) : _nestedList(nestedList)
    {
        _iteratorStack.push(Iterator(nestedList.cbegin(), nestedList.cend()));
    }

    int next()
    {
        prepare();
        const int value = _iteratorStack.top().current->getInteger();
        ++_iteratorStack.top().current;
        return value;
    }

    bool hasNext() const
    {
        prepare();
        return !_iteratorStack.empty();
    }

private:
    std::vector<NestedInteger> _nestedList;
    mutable std::stack<Iterator> _iteratorStack;

    void prepare() const
    {
        while (!_iteratorStack.empty())
        {
            if (!_iteratorStack.top().hasNext())
                _iteratorStack.pop();
            else if (!_iteratorStack.top().current->isInteger())
            {
                Iterator iterator(_iteratorStack.top().current->getList().cbegin(), _iteratorStack.top().current->getList().cend());
                ++_iteratorStack.top().current;
                _iteratorStack.push(iterator);
            }
            else
                break;
        }
    }
};

}

namespace
{

template <typename TNestedIterator> void checkNestedIterator(std::vector<NestedInteger> const &nestedList, std::vector<int> const &expectedNumbers)
{
    TNestedIterator iterator(nestedList);
    for (int expectedNumber : expectedNumbers)
    {
        ASSERT_EQ(true, iterator.hasNext());
        ASSERT_EQ(expectedNumber, iterator.next());
    }
    ASSERT_EQ(false, iterator.hasNext());
}

}

namespace FlattenNestedListIteratorTask
{

TEST(FlattenNestedListIteratorTaskTests, Examples)
{
    // [[1,1],2,[1,1]]
    checkNestedIterator<NestedIteratorWithPreprocessing>({NestedInteger({1, 1}), NestedInteger(2), NestedInteger({1, 1})}, {1, 1, 2, 1, 1});
    checkNestedIterator<NestedIterator>({NestedInteger({1, 1}), NestedInteger(2), NestedInteger({1, 1})}, {1, 1, 2, 1, 1});
    // [1,[4,[6]]]
    checkNestedIterator<NestedIteratorWithPreprocessing>({NestedInteger(1), NestedInteger({NestedInteger(4), NestedInteger(std::vector<int>({6}))})}, {1, 4, 6});
    checkNestedIterator<NestedIterator>({NestedInteger(1), NestedInteger({NestedInteger(4), NestedInteger(std::vector<int>({6}))})}, {1, 4, 6});
}

TEST(FlattenNestedListIteratorTaskTests, FromWrongAnswers)
{
    // [[]]
    checkNestedIterator<NestedIteratorWithPreprocessing>({NestedInteger(std::vector<int>())}, {});
    checkNestedIterator<NestedIterator>({NestedInteger(std::vector<int>())}, {});
}

}