#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumTeachings(int n, std::vector<std::vector<int>> const &languages, std::vector<std::vector<int>> const &friendships) const
    {
        std::vector<std::unordered_set<int>> languagesData(prepareLanguagesData(languages));
        std::vector<bool> friendshipsStatus(friendships.size());
        for (size_t index = 0; index < friendships.size(); ++index)
            friendshipsStatus[index] = needFriendshipTeaching(friendships[index], languages);
        int bestTeaching = INT_MAX;
        for (int language = 1; language <= n; ++language)
        {
            int currentTeaching = 0;
            std::vector<std::unordered_set<int>> currentLanguagesData(languages.size());
            for (size_t index = 0; index < friendships.size(); ++index)
            {
                if (friendshipsStatus[index])
                    continue;
                currentTeaching += processFriendship(language, friendships[index], languagesData, currentLanguagesData);
            }
            bestTeaching = std::min(bestTeaching, currentTeaching);
        }
        return bestTeaching;
    }

private:
    [[nodiscard]] std::vector<std::unordered_set<int>> prepareLanguagesData(std::vector<std::vector<int>> const &languages) const
    {
        std::vector<std::unordered_set<int>> result(languages.size());
        for (size_t index = 0; index < languages.size(); ++index)
            result[index] = std::unordered_set<int>(languages[index].cbegin(), languages[index].cend());
        return result;
    }

    [[nodiscard]] bool needFriendshipTeaching(std::vector<int> const &friendship, std::vector<std::vector<int>> const &languages) const
    {
        std::unordered_map<int, size_t> usedLanguages;
        for (int person : friendship)
        {
            for (int language : languages[person - 1])
                ++usedLanguages[language];
        }
        for (auto const &[_, count] : usedLanguages)
        {
            if (count == friendship.size())
                return true;
        }
        return false;
    }

    [[nodiscard]] int processFriendship(int language,
                                        std::vector<int> const &friendship,
                                        std::vector<std::unordered_set<int>> &mainData,
                                        std::vector<std::unordered_set<int>> &currentData) const
    {
        int result = 0;
        for (int person : friendship)
        {
            if (mainData[person - 1].contains(language) || currentData[person - 1].contains(language))
                continue;
            ++result;
            currentData[person - 1].insert(language);
        }
        return result;
    }
};

}

namespace MinNumberOfPeopleToTeachTask
{

TEST(MinNumberOfPeopleToTeachTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minimumTeachings(2, {{1}, {2}, {1, 2}}, {{1, 2}, {1, 3}, {2, 3}}));
    ASSERT_EQ(2, solution.minimumTeachings(3, {{2}, {1, 3}, {1, 2}, {3}}, {{1, 4}, {1, 2}, {3, 4}, {2, 3}}));
}

}