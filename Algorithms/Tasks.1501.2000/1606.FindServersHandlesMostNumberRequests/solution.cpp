#include <algorithm>
#include <map>
#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> busiestServers(int k, std::vector<int> const &arrival, std::vector<int> const &load) const
    {
        const size_t serversCount = k;
        std::vector<size_t> servers(serversCount, 0);
        std::set<size_t> freeServers;
        for (size_t server = 0; server < serversCount; ++server)
            freeServers.emplace(server);
        std::multimap<int, size_t> busyServers;
        size_t busiestValue = 0;
        for (size_t index = 0; index < arrival.size(); ++index)
        {
            const int task = arrival[index];
            while (!busyServers.empty() && (busyServers.cbegin()->first <= task))
            {
                freeServers.emplace(busyServers.cbegin()->second);
                busyServers.erase(busyServers.cbegin());
            }
            if (freeServers.empty())
                continue;
            auto iterator = freeServers.lower_bound(index % serversCount);
            auto selectedServer = iterator == freeServers.cend() ? freeServers.cbegin() : iterator;
            ++servers[*selectedServer];
            busiestValue = std::max(busiestValue, ++servers[*selectedServer]);
            busyServers.emplace(task + load[index], *selectedServer);
            freeServers.erase(selectedServer);
        }
        std::vector<int> result;
        for (size_t server = 0; server < serversCount; ++server)
        {
            if (servers[server] == busiestValue)
                result.emplace_back(static_cast<int>(server));
        }
        return result;
    }
};

}

namespace FindServersHandlesMostNumberRequestsTask
{

TEST(FindServersHandlesMostNumberRequestsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1}), solution.busiestServers(3, {1, 2, 3, 4, 5}, {5, 2, 3, 3, 3}));
    ASSERT_EQ(std::vector<int>({0}), solution.busiestServers(3, {1, 2, 3, 4}, {1, 2, 1, 2}));
    ASSERT_EQ(std::vector<int>({0, 1, 2}), solution.busiestServers(3, {1, 2, 3}, {10, 12, 11}));
}

TEST(FindServersHandlesMostNumberRequestsTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0}), solution.busiestServers(3, {1, 2, 3, 4, 5, 6}, {1, 1, 100, 1, 1, 1}));
}

}
