#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<std::string>> accountsMerge(std::vector<std::vector<std::string>> const &accounts) const
    {
        std::vector<Node> nodes(accounts.size(), Node());
        std::unordered_map<std::string, size_t> emailAccountMap;
        for (size_t index = 0; index < accounts.size(); ++index)
        {
            for (size_t emailIndex = 1; emailIndex < accounts[index].size(); ++emailIndex)
            {
                auto iterator = emailAccountMap.find(accounts[index][emailIndex]);
                if (iterator == emailAccountMap.end())
                    emailAccountMap.emplace(accounts[index][emailIndex], index);
                else
                {
                    const size_t currentParent = getParent(nodes, index);
                    const size_t emailParent = getParent(nodes, iterator->second);
                    if (currentParent == emailParent)
                        continue;
                    if (nodes[currentParent].Size >= nodes[emailParent].Size)
                    {
                        nodes[emailParent].Parent = static_cast<int>(currentParent);
                        nodes[currentParent].Size += nodes[emailParent].Size;
                        nodes[currentParent].Children.emplace_back(emailParent);
                    }
                    else
                    {
                        nodes[currentParent].Parent = static_cast<int>(emailParent);
                        nodes[emailParent].Size += nodes[currentParent].Size;
                        nodes[emailParent].Children.emplace_back(currentParent);
                    }
                }
            }
        }
        std::vector<std::vector<std::string>> result;
        for (size_t index = 0; index < accounts.size(); ++index)
        {
            if (nodes[index].Parent != -1)
                continue;
            std::vector<std::string> account;
            // placeholder for account name
            account.emplace_back("");
            collectEmails(index, accounts, nodes, account);
            std::ranges::sort(account);
            const auto last = std::ranges::unique(account).begin();
            account.erase(last, account.end());
            account[0] = accounts[index][0];
            result.emplace_back(account);
        }
        return result;
    }

private:
    struct Node
    {
        Node() = default;

        int Parent = -1;
        int Size = 1;
        std::vector<size_t> Children;
    };

    [[nodiscard]] size_t getParent(std::vector<Node> const &nodes, size_t current) const
    {
        while (nodes[current].Parent != -1)
            current = nodes[current].Parent;
        return current;
    }

    void collectEmails(size_t current, std::vector<std::vector<std::string>> const &accounts, std::vector<Node> const &nodes, std::vector<std::string> &dest) const
    {
        for (size_t emailIndex = 1; emailIndex < accounts[current].size(); ++emailIndex)
            dest.emplace_back(accounts[current][emailIndex]);
        for (const size_t child : nodes[current].Children)
            collectEmails(child, accounts, nodes, dest);
    }
};

}

namespace
{

void check(std::vector<std::vector<std::string>> const &accounts, std::vector<std::vector<std::string>> const &expected)
{
    constexpr Solution solution;
    const std::vector<std::vector<std::string>> actual(solution.accountsMerge(accounts));
    ASSERT_EQ(expected.size(), actual.size());
    for (size_t index = 0; index < expected.size(); ++index)
        ASSERT_EQ(expected[index], actual[index]);
}

}

namespace AccountsMergeTask
{

TEST(AccountsMergeTaskTests, Examples)
{
    check({{"John", "john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com"},
           {"Mary", "mary@mail.com"},
           {"John", "johnnybravo@mail.com"}},
          {{"John", "john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com"},
           {"Mary", "mary@mail.com"},
           {"John", "johnnybravo@mail.com"}});
    check({{"Gabe", "Gabe0@m.co", "Gabe3@m.co", "Gabe1@m.co"},
           {"Kevin", "Kevin3@m.co", "Kevin5@m.co", "Kevin0@m.co"},
           {"Ethan", "Ethan5@m.co", "Ethan4@m.co", "Ethan0@m.co"},
           {"Hanzo", "Hanzo3@m.co", "Hanzo1@m.co", "Hanzo0@m.co"},
           {"Fern", "Fern5@m.co", "Fern1@m.co", "Fern0@m.co"}},
          {{"Gabe", "Gabe0@m.co", "Gabe1@m.co", "Gabe3@m.co"},
           {"Kevin", "Kevin0@m.co", "Kevin3@m.co", "Kevin5@m.co"},
           {"Ethan", "Ethan0@m.co", "Ethan4@m.co", "Ethan5@m.co"},
           {"Hanzo", "Hanzo0@m.co", "Hanzo1@m.co", "Hanzo3@m.co"},
           {"Fern", "Fern0@m.co", "Fern1@m.co", "Fern5@m.co"}});
}

TEST(AccountsMergeTaskTests, FromWrongAnswers)
{
    check({{"Alex", "Alex5@m.co", "Alex4@m.co", "Alex0@m.co"},
           {"Ethan", "Ethan3@m.co", "Ethan3@m.co", "Ethan0@m.co"},
           {"Kevin", "Kevin4@m.co", "Kevin2@m.co", "Kevin2@m.co"},
           {"Gabe", "Gabe0@m.co", "Gabe3@m.co", "Gabe2@m.co"},
           {"Gabe", "Gabe3@m.co", "Gabe4@m.co", "Gabe2@m.co"}},
          {{"Alex", "Alex0@m.co", "Alex4@m.co", "Alex5@m.co"},
           {"Ethan", "Ethan0@m.co", "Ethan3@m.co"},
           {"Kevin", "Kevin2@m.co", "Kevin4@m.co"},
           {"Gabe", "Gabe0@m.co", "Gabe2@m.co", "Gabe3@m.co", "Gabe4@m.co"}});
}

}