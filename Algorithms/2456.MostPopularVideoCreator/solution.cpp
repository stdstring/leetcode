#include <map>
#include <string>

#include "gtest/gtest.h"

namespace
{

struct Creator
{
    Creator(std::string const &name) : Name(name), Popularity(0), BestVideoViews(-1)
    {
    }

    std::string Name;
    long long Popularity;
    std::string BestVideoId;
    int BestVideoViews;
};

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<std::string>> mostPopularCreator(std::vector<std::string> const &creators, std::vector<std::string> const &ids, std::vector<int> const &views) const
    {
        std::map<std::string, Creator> creatorDataMap;
        long long bestPopularity = 0;
        for (size_t index = 0; index < creators.size(); ++index)
        {
            auto iterator = creatorDataMap.find(creators[index]);
            if (iterator == creatorDataMap.end())
                iterator = creatorDataMap.emplace(creators[index], Creator(creators[index])).first;
            iterator->second.Popularity += views[index];
            bestPopularity = std::max(bestPopularity, iterator->second.Popularity);
            if ((views[index] > iterator->second.BestVideoViews) || ((views[index] == iterator->second.BestVideoViews) && (ids[index] < iterator->second.BestVideoId)))
            {
                iterator->second.BestVideoViews = views[index];
                iterator->second.BestVideoId = ids[index];
            }
        }
        std::vector<std::vector<std::string>> result;
        for (auto const &entry : creatorDataMap)
        {
            if (entry.second.Popularity == bestPopularity)
                result.push_back(std::vector<std::string>({entry.second.Name, entry.second.BestVideoId}));
        }
        return result;
    }
};

}

namespace MostPopularVideoCreatorTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<std::string>>({{"alice", "one"}, {"bob", "two"}}),
              solution.mostPopularCreator({"alice", "bob", "alice", "chris"}, {"one", "two", "three", "four"}, {5, 10, 5, 4}));
    ASSERT_EQ(std::vector<std::vector<std::string>>({{"alice", "b"}}),
              solution.mostPopularCreator({"alice", "alice", "alice"}, {"a", "b", "c"}, {1, 2, 2}));
}

}