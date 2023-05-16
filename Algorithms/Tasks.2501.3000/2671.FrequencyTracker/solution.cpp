#include <unordered_map>
#include <variant>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class FrequencyTracker
{
public:
    FrequencyTracker() = default;

    void add(int number)
    {
        auto iterator = _numberMap.find(number);
        if (iterator == _numberMap.end())
            iterator = _numberMap.emplace(number, 0).first;
        const int oldFrequency = iterator->second;
        ++iterator->second;
        updateFrequency(oldFrequency, oldFrequency + 1);
    }

    void deleteOne(int number)
    {
        const auto iterator = _numberMap.find(number);
        if (iterator == _numberMap.end())
            return;
        const int oldFrequency = iterator->second;
        --iterator->second;
        if (iterator->second == 0)
            _numberMap.erase(iterator);
        updateFrequency(oldFrequency, oldFrequency - 1);
    }

    [[nodiscard]] bool hasFrequency(int frequency) const
    {
        return _freqMap.count(frequency) > 0;
    }

private:
    void updateFrequency(int oldValue, int newValue)
    {
        if (oldValue != 0)
        {
            const auto oldValueIterator = _freqMap.find(oldValue);
            --oldValueIterator->second;
            if (oldValueIterator->second == 0)
                _freqMap.erase(oldValueIterator);
        }
        if (newValue != 0)
            ++_freqMap[newValue];
    }

    std::unordered_map<int, int> _numberMap;
    std::unordered_map<int, int> _freqMap;
};

}

namespace
{

struct AddCall
{
    AddCall(int number) : Number(number)
    {
    }

    int Number;
};

struct DeleteOneCall
{
    DeleteOneCall(int number) : Number(number)
    {
    }

    int Number;
};

struct HasFrequencyCall
{
    HasFrequencyCall(int frequency, bool result) : Frequency(frequency), Result(result)
    {
    }

    int Frequency;
    bool Result;
};

void checkFrequencyTracker(std::vector<std::variant<AddCall, DeleteOneCall, HasFrequencyCall>> const &calls)
{
    FrequencyTracker frequencyTracker;
    for (std::variant<AddCall, DeleteOneCall, HasFrequencyCall> const &call : calls)
    {
        if (const AddCall* addCall = std::get_if<AddCall>(&call))
            ASSERT_NO_THROW(frequencyTracker.add(addCall->Number));
        if (const DeleteOneCall* deleteOneCall = std::get_if<DeleteOneCall>(&call))
            ASSERT_NO_THROW(frequencyTracker.deleteOne(deleteOneCall->Number));
        if (const HasFrequencyCall* hasFrequencyCall = std::get_if<HasFrequencyCall>(&call))
            ASSERT_EQ(hasFrequencyCall->Result, frequencyTracker.hasFrequency(hasFrequencyCall->Frequency));
    }
}

}

namespace FrequencyTrackerTask
{

TEST(FrequencyTrackerTaskTests, Examples)
{
    // Example 1
    checkFrequencyTracker({AddCall(3), AddCall(3), HasFrequencyCall(2, true)});
    // Example 2
    checkFrequencyTracker({AddCall(1), DeleteOneCall(1), HasFrequencyCall(1, false)});
    // Example 3
    checkFrequencyTracker({HasFrequencyCall(2, false), AddCall(3), HasFrequencyCall(1, true)});
}

TEST(FrequencyTrackerTaskTests, FromWrongAnswers)
{
    checkFrequencyTracker({DeleteOneCall(1)});
}

}