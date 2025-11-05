#include <iterator>
#include <set>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<long long> findXSum(std::vector<int> const &nums, int k, int x) const
    {
        const size_t subarraySize = k;
        const size_t topCount = x;
        std::vector<long long> result(nums.size() - subarraySize + 1, 0);
        std::set<FrequencyData, FrequencyDataComp> topData;
        std::set<FrequencyData, FrequencyDataComp> bottomData;
        std::unordered_map<int, int> slidingWindow;
        long long topSum = 0;
        // sliding window init
        for (size_t index = 0; index < subarraySize; ++index)
            ++slidingWindow[nums[index]];
        for (auto const& [number, frequency] : slidingWindow)
            bottomData.emplace(frequency, number);
        while ((topData.size() < topCount) && !bottomData.empty())
        {
            FrequencyData const& current(*bottomData.cbegin());
            topSum += 1LL * current.Number * current.Frequency;
            topData.insert(current);
            bottomData.erase(bottomData.cbegin());
        }
        result[0] = topSum;
        // sliding window move
        for (size_t index = 1; index + subarraySize <= nums.size(); ++index)
        {
            topSum = removeNumber(nums[index - 1], topData, bottomData, slidingWindow, topSum, topCount);
            topSum = addNumber(nums[index + subarraySize - 1], topData, bottomData, slidingWindow, topSum, topCount);
            topSum = balanceData(topData, bottomData, topSum, topCount);
            result[index] = topSum;
        }
        return result;
    }

private:
    struct FrequencyData
    {
        FrequencyData(int frequency, int number) : Frequency(frequency), Number(number)
        {
        }
        int Frequency;
        int Number;
    };

    struct FrequencyDataComp
    {
        bool operator()(FrequencyData const &l, FrequencyData const &r) const
        {
            return (l.Frequency > r.Frequency) || ((l.Frequency == r.Frequency) && (l.Number > r.Number));
        }
    };

    [[nodiscard]] long long removeNumber(int number,
                                         std::set<FrequencyData, FrequencyDataComp> &topData,
                                         std::set<FrequencyData, FrequencyDataComp> &bottomData,
                                         std::unordered_map<int, int> &slidingWindow,
                                         long long topSum,
                                         size_t topCount) const
    {
        auto slidingWindowIterator = slidingWindow.find(number);
        FrequencyData data(slidingWindowIterator->second, number);
        --slidingWindowIterator->second;
        if (slidingWindowIterator->second == 0)
            slidingWindow.erase(slidingWindowIterator);
        auto bottomIterator = bottomData.find(data);
        if (bottomIterator != bottomData.cend())
            bottomData.erase(bottomIterator);
        auto topIterator = topData.find(data);
        if (topIterator != topData.cend())
        {
            topSum -= 1LL * topIterator->Number * topIterator->Frequency;
            topData.erase(topIterator);
        }
        --data.Frequency;
        if (data.Frequency > 0)
            bottomData.insert(data);
        return topSum;
    }

    [[nodiscard]] long long addNumber(int number,
                                      std::set<FrequencyData, FrequencyDataComp> &topData,
                                      std::set<FrequencyData, FrequencyDataComp> &bottomData,
                                      std::unordered_map<int, int> &slidingWindow,
                                      long long topSum,
                                      size_t topCount) const
    {
        auto slidingWindowIterator = slidingWindow.find(number);
        if (slidingWindowIterator == slidingWindow.cend())
            slidingWindowIterator = slidingWindow.emplace(number, 0).first;
        FrequencyData data(slidingWindowIterator->second, number);
        ++slidingWindowIterator->second;
        auto bottomIterator = bottomData.find(data);
        if (bottomIterator != bottomData.cend())
            bottomData.erase(bottomIterator);
        auto topIterator = topData.find(data);
        if (topIterator != topData.cend())
        {
            topSum -= 1LL * topIterator->Number * topIterator->Frequency;
            topData.erase(topIterator);
        }
        ++data.Frequency;
        bottomData.insert(data);
        return topSum;
    }

    [[nodiscard]] long long balanceData(std::set<FrequencyData, FrequencyDataComp> &topData,
                                        std::set<FrequencyData, FrequencyDataComp> &bottomData,
                                        long long topSum,
                                        size_t topCount) const
    {
        while (!bottomData.empty() && (topData.size() < topCount))
        {
            FrequencyData const &data(*bottomData.cbegin());
            topSum += 1LL * data.Number * data.Frequency;
            topData.insert(data);
            bottomData.erase(bottomData.cbegin());
        }
        FrequencyDataComp comparer;
        while (!bottomData.empty() && comparer(*bottomData.cbegin(), *topData.crbegin()))
        {
            FrequencyData lastTopData(*topData.crbegin());
            FrequencyData firstBottomData(*bottomData.cbegin());
            topData.erase(std::prev(topData.cend()));
            bottomData.erase(bottomData.cbegin());
            topData.insert(firstBottomData);
            bottomData.insert(lastTopData);
            topSum -= 1LL * lastTopData.Number * lastTopData.Frequency;
            topSum += 1LL * firstBottomData.Number * firstBottomData.Frequency;
        }
        return topSum;
    }
};

}

namespace FindXSumOfAllKLongSubarrays2Task
{

TEST(FindXSumOfAllKLongSubarrays2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<long long>({6, 10, 12}), solution.findXSum({1, 1, 2, 2, 3, 4, 2, 3}, 6, 2));
    ASSERT_EQ(std::vector<long long>({11, 15, 15, 15, 12}), solution.findXSum({3, 8, 7, 8, 7, 5}, 2, 2));
}

}