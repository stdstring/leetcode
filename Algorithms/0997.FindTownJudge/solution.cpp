#include <vector>

#include "gtest/gtest.h"

namespace
{

struct TrustData
{
    TrustData() : TrustFrom(0), TrustTo(0)
    {
    }

    size_t TrustFrom;
    size_t TrustTo;
};

class Solution
{
public:
    [[nodiscard]] int findJudge(int n, std::vector<std::vector<int>> const &trust) const
    {
        const size_t personCount = n;
        std::vector<TrustData> trustData(personCount);
        for (std::vector<int> const &entry : trust)
        {
            ++trustData[static_cast<size_t>(entry[0]) - 1].TrustTo;
            ++trustData[static_cast<size_t>(entry[1]) - 1].TrustFrom;
        }
        int judge = -1;
        for (int person = 1; person <= n; ++person)
        {
            const size_t personIndex = static_cast<size_t>(person) - 1;
            if ((trustData[personIndex].TrustFrom == (personCount - 1)) && (trustData[personIndex].TrustTo == 0))
            {
                if (judge != -1)
                    return -1;
                judge = person;
            }
        }
        return judge;
    }
};

}

namespace FindTownJudgeTask
{

TEST(FindTownJudgeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.findJudge(2, {{1, 2}}));
    ASSERT_EQ(3, solution.findJudge(3, {{1, 3}, {2, 3}}));
    ASSERT_EQ(-1, solution.findJudge(3, {{1, 3}, {2, 3}, {3, 1}}));
}

}
