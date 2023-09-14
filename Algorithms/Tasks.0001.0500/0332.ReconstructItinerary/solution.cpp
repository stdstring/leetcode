#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> findItinerary(std::vector<std::vector<std::string>> const &tickets) const
    {
        std::unordered_map<std::string, std::vector<std::pair<std::string, bool>>> ticketMap;
        for (std::vector<std::string> const &ticket : tickets)
            ticketMap[ticket[0]].emplace_back(ticket[1], false);
        for (auto &[_, targets] : ticketMap)
            std::ranges::sort(targets, [](std::pair<std::string, bool> const &l, std::pair<std::string, bool> const &r) { return l.first < r.first; });
        std::vector<std::string> path;
        // we use algorithm for finding Euler path: https://en.wikipedia.org/wiki/Eulerian_path
        findEulerPath(ticketMap, "JFK", path);
        std::ranges::reverse(path);
        return path;
    }

private:
    void findEulerPath(std::unordered_map<std::string, std::vector<std::pair<std::string, bool>>> &ticketMap,
                       std::string const &current,
                       std::vector<std::string> &path) const
    {
        for (std::pair<std::string, bool> &target : ticketMap[current])
        {
            if (target.second)
                continue;
            target.second = true;
            findEulerPath(ticketMap, target.first, path);
        }
        path.emplace_back(current);
    }
};

}

namespace ReconstructItineraryTask
{

TEST(ReconstructItineraryTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"JFK", "MUC", "LHR", "SFO", "SJC"}),
              solution.findItinerary({{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}}));
    ASSERT_EQ(std::vector<std::string>({"JFK", "ATL", "JFK", "SFO", "ATL", "SFO"}),
              solution.findItinerary({{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}}));
}

TEST(ReconstructItineraryTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"JFK", "NRT", "JFK", "KUL"}),
              solution.findItinerary({{"JFK", "KUL"}, {"JFK", "NRT"}, {"NRT", "JFK"}}));
}

}