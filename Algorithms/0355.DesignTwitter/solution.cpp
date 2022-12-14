#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Twitter
{
public:
    Twitter() = default;

    void postTweet(int userId, int tweetId)
    {
        auto iterator = _tweets.find(userId);
        if (iterator == _tweets.end())
            iterator = _tweets.emplace(userId, std::list<Tweet>()).first;
        iterator->second.emplace_front(tweetId, _currentTime++);
        if (iterator->second.size() > RecentTweetCount)
            iterator->second.pop_back();
    }

    std::vector<int> getNewsFeed(int userId)
    {
        auto cmp = [](Tweet const &left, Tweet const &right) { return left.Time > right.Time; };
        std::priority_queue<Tweet, std::vector<Tweet>, decltype(cmp)> queue(cmp);
        auto fillFun = [this, &queue](int id)
        {
            for (Tweet const &tweet : _tweets[id])
            {
                queue.push(tweet);
                if (queue.size() > RecentTweetCount)
                    queue.pop();
            }
        };
        fillFun(userId);
        for (const int followerId : _followers[userId])
            fillFun(followerId);
        std::vector<int> newsfeed;
        while (!queue.empty())
        {
            newsfeed.emplace_back(queue.top().Id);
            queue.pop();
        }
        std::reverse(newsfeed.begin(), newsfeed.end());
        return newsfeed;
    }

    void follow(int followerId, int followeeId)
    {
        _followers[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId)
    {
        _followers[followerId].erase(followeeId);
    }

private:
    struct Tweet
    {
        Tweet(int id, int time) : Id(id), Time(time)
        {
        }

        int Id;
        int Time;
    };

    int _currentTime = 0;
    std::unordered_map<int, std::list<Tweet>> _tweets;
    std::unordered_map<int, std::unordered_set<int>> _followers;
    static constexpr int RecentTweetCount = 10;
};

}

namespace DesignTwitterTask
{

TEST(DesignTwitterTaskTests, Examples)
{
    Twitter twitter;
    ASSERT_NO_THROW(twitter.postTweet(1, 5));
    ASSERT_EQ(std::vector<int>({5}), twitter.getNewsFeed(1));
    ASSERT_NO_THROW(twitter.follow(1, 2));
    ASSERT_NO_THROW(twitter.postTweet(2, 6));
    ASSERT_EQ(std::vector<int>({6, 5}), twitter.getNewsFeed(1));
    ASSERT_NO_THROW(twitter.unfollow(1, 2));
    ASSERT_EQ(std::vector<int>({5}), twitter.getNewsFeed(1));
}

}
