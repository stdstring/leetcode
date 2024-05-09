#include <iterator>
#include <set>
#include <queue>
#include <variant>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class MKAverage
{
public:
    MKAverage(int m, int k) : _m(m), _k(k), _middleSum(0)
    {
    }

    void addElement(int num)
    {
        // remove oldest number
        removeOldestNumber();
        // add num
        _lastNumbers.emplace(num);
        _middleNumbers.emplace(num);
        _middleSum += num;
        if (_lastNumbers.size() < _m)
            return;
        // balance
        balanceBySize(_smallestNumbers, true);
        balanceBySize(_largestNumbers, false);
        while (*_smallestNumbers.crbegin() > *_middleNumbers.cbegin())
        {
            const int bigNumber = *_smallestNumbers.crbegin();
            const int smallNumber = *_middleNumbers.cbegin();
            _middleSum += bigNumber;
            _middleSum -= smallNumber;
            _smallestNumbers.erase(std::prev(_smallestNumbers.cend(), 1));
            _middleNumbers.erase(_middleNumbers.cbegin());
            _smallestNumbers.emplace(smallNumber);
            _middleNumbers.emplace(bigNumber);
        }
        while (*_largestNumbers.cbegin() < *_middleNumbers.crbegin())
        {
            const int smallNumber = *_largestNumbers.cbegin();
            const int bigNumber = *_middleNumbers.crbegin();
            _middleSum += smallNumber;
            _middleSum -= bigNumber;
            _largestNumbers.erase(_largestNumbers.cbegin());
            _middleNumbers.erase(std::prev(_middleNumbers.cend(), 1));
            _middleNumbers.emplace(smallNumber);
            _largestNumbers.emplace(bigNumber);
        }
    }

    int calculateMKAverage()
    {
        if (_lastNumbers.size() < _m)
            return -1;
        return _middleSum / static_cast<int>(_middleNumbers.size());
    }

private:
    size_t _m;
    size_t _k;
    std::queue<int> _lastNumbers;
    std::multiset<int> _smallestNumbers;
    std::multiset<int> _middleNumbers;
    std::multiset<int> _largestNumbers;
    long long _middleSum;

    void removeOldestNumber()
    {
        if (_lastNumbers.size() < _m)
            return;
        const int firstNumber = _lastNumbers.front();
        _lastNumbers.pop();
        if (firstNumber <= *_smallestNumbers.crbegin())
            _smallestNumbers.erase(_smallestNumbers.find(firstNumber));
        else if (firstNumber <= *_middleNumbers.crbegin())
        {
            _middleSum -= firstNumber;
            _middleNumbers.erase(_middleNumbers.find(firstNumber));
        }
        else
            _largestNumbers.erase(_largestNumbers.find(firstNumber));
    }

    void balanceBySize(std::multiset<int> &unbalancedNumbers, bool fromBegin)
    {
        while (unbalancedNumbers.size() < _k)
        {
            if (fromBegin)
            {
                _middleSum -= *_middleNumbers.cbegin();
                unbalancedNumbers.emplace(*_middleNumbers.cbegin());
                _middleNumbers.erase(_middleNumbers.cbegin());
            }
            else
            {
                _middleSum -= *_middleNumbers.crbegin();
                unbalancedNumbers.emplace(*_middleNumbers.crbegin());
                _middleNumbers.erase(std::prev(_middleNumbers.cend(), 1));
            }
        }
    }
};

}

namespace
{

struct AddElementCall
{
    AddElementCall(int element) : Element(element)
    {
    }

    int Element;
};

struct CalculateMKAverageCall
{
    CalculateMKAverageCall(int average) : Average(average)
    {
    }

    int Average;
};

void checkMKAverage(int m, int k, std::vector<std::variant<AddElementCall, CalculateMKAverageCall>> const &calls)
{
    MKAverage mkAverage(m, k);
    for (std::variant<AddElementCall, CalculateMKAverageCall> const &call : calls)
    {
        if (AddElementCall const* addElementCall = std::get_if<AddElementCall>(&call))
            ASSERT_NO_THROW(mkAverage.addElement(addElementCall->Element));
        if (CalculateMKAverageCall const* calculateMKAverageCall = std::get_if<CalculateMKAverageCall>(&call))
            ASSERT_EQ(calculateMKAverageCall->Average, mkAverage.calculateMKAverage());
    }
}

}

namespace FindingMKAverageTask
{

TEST(FindingMKAverageTaskTests, Examples)
{
    checkMKAverage(3, 1, {AddElementCall(3),
                          AddElementCall(1),
                          CalculateMKAverageCall(-1),
                          AddElementCall(10),
                          CalculateMKAverageCall(3),
                          AddElementCall(5),
                          AddElementCall(5),
                          AddElementCall(5),
                          CalculateMKAverageCall(5)});
}

TEST(FindingMKAverageTaskTests, FromWrongAnswers)
{
    checkMKAverage(3, 1, {AddElementCall(58916),
                          AddElementCall(61899),
                          CalculateMKAverageCall(-1),
                          AddElementCall(85406),
                          AddElementCall(49757),
                          CalculateMKAverageCall(61899),
                          AddElementCall(27520),
                          AddElementCall(12303),
                          CalculateMKAverageCall(27520),
                          AddElementCall(63945)});
}

}