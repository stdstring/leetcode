#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findAllPeople(int n, std::vector<std::vector<int>> const &meetings, int firstPerson) const
    {
        std::map<int, std::vector<std::vector<int>>> meetingsData;
        for (std::vector<int> const &meeting : meetings)
            meetingsData[meeting[2]].emplace_back(meeting);
        std::vector<bool> knowledge(n, false);
        knowledge[0] = knowledge[firstPerson] = true;
        for (auto const &[_, meetingsForTime] : meetingsData)
        {
            std::unordered_map<int, GroupData> groups;
            for (std::vector<int> const &meeting : meetingsForTime)
            {
                auto iterator1 = groups.find(meeting[0]);
                if (iterator1 == groups.cend())
                    groups.emplace(meeting[0], GroupData());
                auto iterator2 = groups.find(meeting[1]);
                if (iterator2 == groups.cend())
                    groups.emplace(meeting[1], GroupData());
                unionGroup(groups, meeting[0], meeting[1]);
            }
            std::unordered_map<int, std::vector<int>> uniqueMeetings;
            for (auto const &entry : groups)
            {
                const int parent = findParent(groups, entry.first);
                uniqueMeetings[parent].emplace_back(entry.first);
            }
            for (auto const &entry : uniqueMeetings)
            {
                auto accFun = [&knowledge](bool acc, int person) { return acc | knowledge[person]; };
                const bool propagateSecret = std::accumulate(entry.second.cbegin(), entry.second.cend(), false, accFun);
                if (propagateSecret)
                    std::ranges::for_each(entry.second, [&knowledge](int person) { knowledge[person] = true; });
            }
        }
        std::vector<int> result;
        result.reserve(n);
        for (int person = 0; person < n; ++person)
        {
            if (knowledge[person])
                result.emplace_back(person);
        }
        return result;
    }

private:
    struct GroupData
    {
        size_t Size = 1;
        int Parent = -1;
    };

    [[nodiscard]] int findParent(std::unordered_map<int, GroupData> const &groups, int current) const
    {
        while (groups.at(current).Parent != -1)
            current = groups.at(current).Parent;
        return current;
    }

    void unionGroup(std::unordered_map<int, GroupData> &groups, int person1, int person2) const
    {
        const int parent1 = findParent(groups, person1);
        const int parent2 = findParent(groups, person2);
        if (parent1 == parent2)
            return;
        if (groups[parent1].Size >= groups[parent2].Size)
        {
            groups[parent2].Parent = parent1;
            groups[parent1].Size += groups[parent2].Size;
        }
        else
        {
            groups[parent1].Parent = parent2;
            groups[parent2].Size += groups[parent1].Size;
        }
    }
};

}

namespace FindAllPeopleWithSecretTask
{

TEST(FindAllPeopleWithSecretTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1, 2, 3, 5}), solution.findAllPeople(6, {{1, 2, 5}, {2, 3, 8}, {1, 5, 10}}, 1));
    ASSERT_EQ(std::vector<int>({0, 1, 3}), solution.findAllPeople(4, {{3, 1, 3}, {1, 2, 2}, {0, 3, 3}}, 3));
    ASSERT_EQ(std::vector<int>({0, 1, 2, 3, 4}), solution.findAllPeople(5, {{3, 4, 2}, {1, 2, 1}, {2, 3, 1}}, 1));
}

TEST(FindAllPeopleWithSecretTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1, 2, 3}), solution.findAllPeople(6, {{0, 2, 1}, {1, 3, 1}, {4, 5, 1}}, 1));
}

}