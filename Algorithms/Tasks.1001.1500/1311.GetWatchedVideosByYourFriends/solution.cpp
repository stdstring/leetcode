#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> watchedVideosByFriends(std::vector<std::vector<std::string>> const &watchedVideos,
                                                                  std::vector<std::vector<int>> const &friends,
                                                                  int id,
                                                                  int level) const
    {
        const size_t peopleCount = watchedVideos.size();
        // find friends on specified level
        std::vector<bool> visited(peopleCount, false);
        std::queue<int> levelQueue;
        visited[id] = true;
        levelQueue.push(id);
        for (int currentLevel = 0; (currentLevel < level) && !levelQueue.empty(); ++currentLevel)
        {
            const size_t levelSize = levelQueue.size();
            for (size_t index = 0; index < levelSize; ++index)
            {
                const int currentPerson = levelQueue.front();
                levelQueue.pop();
                for (const int personFriend : friends[currentPerson])
                {
                    if (!visited[personFriend])
                    {
                        visited[personFriend] = true;
                        levelQueue.push(personFriend);
                    }
                }
            }
        }
        if (levelQueue.empty())
            return {};
        // count video freq
        std::vector<std::string> levelVideos;
        std::unordered_map<std::string, int> levelVideosFreq;
        while (!levelQueue.empty())
        {
            const int currentPerson = levelQueue.front();
            levelQueue.pop();
            for (std::string const &video : watchedVideos[currentPerson])
            {
                auto iterator = levelVideosFreq.find(video);
                if (iterator == levelVideosFreq.end())
                {
                    levelVideos.emplace_back(video);
                    iterator = levelVideosFreq.emplace(video, 0).first;
                }
                ++iterator->second;
            }
        }
        // sort result
        auto comparer = [&levelVideosFreq](std::string const& l, std::string const& r)
        {
            return (levelVideosFreq[l] < levelVideosFreq[r]) || ((levelVideosFreq[l] == levelVideosFreq[r]) && (l < r));
        };
        std::sort(levelVideos.begin(), levelVideos.end(), comparer);
        return levelVideos;
    }
};

}

namespace GetWatchedVideosByYourFriendsTask
{

TEST(GetWatchedVideosByYourFriendsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"B", "C"}),
              solution.watchedVideosByFriends({{"A", "B"}, {"C"}, {"B", "C"}, {"D"}}, {{1, 2}, {0, 3}, {0, 3}, {1, 2}}, 0, 1));
    ASSERT_EQ(std::vector<std::string>({"D"}),
              solution.watchedVideosByFriends({{"A", "B"}, {"C"}, {"B", "C"}, {"D"}}, {{1, 2}, {0, 3}, {0, 3}, {1, 2}}, 0, 2));
}

}