#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class TopVotedCandidate
{
public:
    TopVotedCandidate(std::vector<int> const &persons, std::vector<int> const &times)
    {
        std::vector<size_t> votes(persons.size() + 1, 0);
        size_t bestVote = 0;
        int bestCandidate = -1;
        for (size_t index = 0; index < persons.size(); ++index)
        {
            const int person = persons[index];
            ++votes[person];
            if (votes[person] >= bestVote)
            {
                bestVote = votes[person];
                bestCandidate = person;
            }
            _topVotedMap.emplace(times[index], bestCandidate);
        }
    }

    int q(int t)
    {
        if (t >= _topVotedMap.crbegin()->first)
            return _topVotedMap.crbegin()->second;
        auto iterator = _topVotedMap.lower_bound(t);
        if (iterator->first > t)
            --iterator;
        return iterator->second;
    }

private:
    std::map<int, int> _topVotedMap;
};

}

namespace OnlineElectionTask
{

TEST(OnlineElectionTaskTests, Examples)
{
    TopVotedCandidate topVotedCandidate({0, 1, 1, 0, 0, 1, 0}, {0, 5, 10, 15, 20, 25, 30});
    ASSERT_EQ(0, topVotedCandidate.q(3));
    ASSERT_EQ(1, topVotedCandidate.q(12));
    ASSERT_EQ(1, topVotedCandidate.q(25));
    ASSERT_EQ(0, topVotedCandidate.q(15));
    ASSERT_EQ(0, topVotedCandidate.q(24));
    ASSERT_EQ(1, topVotedCandidate.q(8));
}

}
