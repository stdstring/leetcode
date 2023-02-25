#include <queue>
#include <stdexcept>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string predictPartyVictory(std::string const &senate) const
    {
        std::queue<char> queue;
        size_t banRCount = 0;
        size_t restRCount = 0;
        size_t banDCount = 0;
        size_t restDCount = 0;
        for (const char ch : senate)
            processRight(ch, queue, banRCount, restRCount, banDCount, restDCount);
        while ((restRCount != 0) && (restDCount != 0))
        {
            size_t roundRestRCount = 0;
            size_t roundRestDCount = 0;
            const size_t roundSize = queue.size();
            for (size_t index = 0; index < roundSize; ++index)
            {
                processRight(queue.front(), queue, banRCount, roundRestRCount, banDCount, roundRestDCount);
                queue.pop();
            }
            restRCount = roundRestRCount;
            restDCount = roundRestDCount;
        }
        return restRCount > 0 ? "Radiant" : "Dire";
    }

private:
    void processRight(char current, std::queue<char> &queue, size_t &banRCount, size_t &restRCount, size_t &banDCount, size_t &restDCount) const
    {
        switch (current)
        {
            case 'R':
                if (banRCount > 0)
                    --banRCount;
                else
                {
                    queue.push('R');
                    ++restRCount;
                    ++banDCount;
                }
                break;
            case 'D':
                if (banDCount > 0)
                    --banDCount;
                else
                {
                    queue.push('D');
                    ++restDCount;
                    ++banRCount;
                }
                break;
            default:
                throw std::logic_error("Bad senator");
        }
    }
};

}

namespace Dota2SenateTask
{

TEST(Dota2SenateTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("Radiant", solution.predictPartyVictory("RD"));
    ASSERT_EQ("Dire", solution.predictPartyVictory("RDD"));
}

TEST(Dota2SenateTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ("Radiant", solution.predictPartyVictory("RRDDD"));
    ASSERT_EQ("Radiant", solution.predictPartyVictory("DRRDRDRDRDDRDRDR"));
}

}