#include <numeric>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class CombinationIterator
{
public:
    CombinationIterator(std::string const &characters, int combinationLength) : _characters(characters), _combinationLength(combinationLength)
    {
    }

    std::string next()
    {
        if (!_currentCombination.empty() && (_currentCombination[0] == (_characters.size() - _combinationLength)))
            throw std::logic_error("Last combination reached");
        if (_currentCombination.empty())
        {
            _currentCombination.resize(_combinationLength);
            std::iota(_currentCombination.begin(), _currentCombination.end(), 0);
        }
        else
        {
            size_t shift = 1;
            for (;_currentCombination[_currentCombination.size() - shift] == (_characters.size() - shift); ++shift) {}
            ++_currentCombination[_currentCombination.size() - shift];
            --shift;
            for (;shift > 0; --shift)
                _currentCombination[_currentCombination.size() - shift] = _currentCombination[_currentCombination.size() - shift - 1] + 1;
        }
        std::string combination;
        for (const size_t index : _currentCombination)
            combination.push_back(_characters[index]);
        return combination;
    }

    bool hasNext()
    {
        return _currentCombination.empty() || (_currentCombination[0] < (_characters.size() - _combinationLength));
    }

private:
    const std::string _characters;
    const int _combinationLength;
    std::vector<size_t> _currentCombination;
};

}

namespace IteratorForCombinationTask
{

TEST(IteratorForCombinationTaskTests, Examples)
{
    CombinationIterator iterator("abc", 2);
    ASSERT_EQ("ab", iterator.next());
    ASSERT_EQ(true, iterator.hasNext());
    ASSERT_EQ("ac", iterator.next());
    ASSERT_EQ(true, iterator.hasNext());
    ASSERT_EQ("bc", iterator.next());
    ASSERT_EQ(false, iterator.hasNext());
}

}