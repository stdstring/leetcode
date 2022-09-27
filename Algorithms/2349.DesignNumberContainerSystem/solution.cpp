#include <set>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{
class NumberContainers
{
public:
    NumberContainers() = default;

    void change(int index, int number)
    {
        const auto iterator = _index2NumberMap.find(index);
        if (iterator == _index2NumberMap.end())
        {
            _index2NumberMap.emplace(index, number);
            auto numberIterator = _number2IndicesMap.find(number);
            if (numberIterator == _number2IndicesMap.end())
                numberIterator = _number2IndicesMap.emplace(number, std::set<int>()).first;
            numberIterator->second.emplace(index);
        }
        else
        {
            const auto oldNumberIterator = _number2IndicesMap.find(iterator->second);
            oldNumberIterator->second.erase(index);
            if (oldNumberIterator->second.empty())
                _number2IndicesMap.erase(oldNumberIterator);
            iterator->second = number;
            _number2IndicesMap[number].emplace(index);
        }
    }

    [[nodiscard]] int find(int number) const
    {
        const auto iterator = _number2IndicesMap.find(number);
        return iterator == _number2IndicesMap.cend() ? -1 : *(iterator->second.cbegin());
    }

private:
    std::unordered_map<int, int> _index2NumberMap;
    std::unordered_map<int, std::set<int>> _number2IndicesMap;
};

}

namespace DesignNumberContainerSystemTask
{

TEST(DesignNumberContainerSystemTaskTests, Examples)
{
    NumberContainers container;
    ASSERT_EQ(-1, container.find(10));
    ASSERT_NO_THROW(container.change(2, 10));
    ASSERT_NO_THROW(container.change(1, 10));
    ASSERT_NO_THROW(container.change(3, 10));
    ASSERT_NO_THROW(container.change(5, 10));
    ASSERT_EQ(1, container.find(10));
    ASSERT_NO_THROW(container.change(1, 20));
    ASSERT_EQ(2, container.find(10));
}

}