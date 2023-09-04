#include <set>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class TweetCounts
{
public:
    TweetCounts() = default;

    void recordTweet(std::string const &tweetName, int time)
    {
        _tweetMap[tweetName].emplace(time);
    }

    std::vector<int> getTweetCountsPerFrequency(std::string const &freq, std::string const &tweetName, int startTime, int endTime)
    {
        const int timeInterval = getTimeInterval(freq);
        const int totalTimeInterval = endTime - startTime + 1;
        const size_t intervalCount = totalTimeInterval / timeInterval + ((totalTimeInterval % timeInterval) == 0 ? 0 : 1);
        std::vector<int> result(intervalCount, 0);
        const auto tweetIterator = _tweetMap.find(tweetName);
        if (tweetIterator == _tweetMap.cend())
            return result;
        auto timeIterator = tweetIterator->second.lower_bound(startTime);
        int startIntervalTime = startTime;
        for (size_t index = 0; index < intervalCount; ++index)
        {
            const int endIntervalTime = std::min(endTime, startIntervalTime + timeInterval - 1);
            for (;(timeIterator != tweetIterator->second.cend()) && (*timeIterator <= endIntervalTime); ++timeIterator)
                ++result[index];
            if (timeIterator == tweetIterator->second.cend())
                break;
            startIntervalTime += timeInterval;
        }
        return result;
    }

private:
    std::unordered_map<std::string, std::multiset<int>> _tweetMap;

    [[nodiscard]] int getTimeInterval(std::string const &freq) const
    {
        if (freq == "minute")
            return 60;
        if (freq == "hour")
            return 3600;
        if (freq == "day")
            return 86400;
        throw std::logic_error("unsupported frequency");
    }
};

}

namespace TweetCountsPerFrequencyTask
{

TEST(TweetCountsPerFrequencyTaskTests, Examples)
{
    TweetCounts tweetCounts;
    ASSERT_NO_THROW(tweetCounts.recordTweet("tweet3", 0));
    ASSERT_NO_THROW(tweetCounts.recordTweet("tweet3", 60));
    ASSERT_NO_THROW(tweetCounts.recordTweet("tweet3", 10));
    ASSERT_EQ(std::vector<int>({2}), tweetCounts.getTweetCountsPerFrequency("minute", "tweet3", 0, 59));
    ASSERT_EQ(std::vector<int>({2, 1}), tweetCounts.getTweetCountsPerFrequency("minute", "tweet3", 0, 60));
    ASSERT_NO_THROW(tweetCounts.recordTweet("tweet3", 120));
    ASSERT_EQ(std::vector<int>({4}), tweetCounts.getTweetCountsPerFrequency("hour", "tweet3", 0, 210));
}

}