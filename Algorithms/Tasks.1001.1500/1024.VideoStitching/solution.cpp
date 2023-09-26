#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int videoStitching(std::vector<std::vector<int>> const &clips, int time) const
    {
        std::vector<std::vector<int>> sortedClips(clips);
        auto comp = [](std::vector<int> const& l, std::vector<int> const& r) { return (l[0] < r[0]) || ((l[0] == r[0]) && (l[1] < r[1])); };
        std::ranges::sort(sortedClips, comp);
        std::vector<int> dp(time + 1, -1);
        dp[0] = 0;
        for (std::vector<int> const &clip : sortedClips)
        {
            if (clip[0] >= time)
                break;
            if (dp[clip[0]] == -1)
                return -1;
            int minClipCount = dp[clip[0]] + 1;
            for (int clipTime = clip[0] + 1; clipTime <= std::min(time, clip[1]); ++clipTime)
            {
                if (dp[clipTime] == -1)
                    dp[clipTime] = minClipCount;
                else
                    minClipCount = std::min(minClipCount, dp[clipTime] + 1);
            }
        }
        return dp.back();
    }
};

}

namespace VideoStitchingTask
{

TEST(VideoStitchingTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.videoStitching({{0, 2}, {4, 6}, {8, 10}, {1, 9}, {1, 5}, {5, 9}}, 10));
    ASSERT_EQ(-1, solution.videoStitching({{0, 1}, {1, 2}}, 5));
    ASSERT_EQ(3, solution.videoStitching({{0, 1}, {6, 8}, {0, 2}, {5, 6}, {0, 4}, {0, 3}, {6, 7}, {1, 3}, {4, 7}, {1, 4}, {2, 5}, {2, 6}, {3, 4}, {4, 5}, {5, 7}, {6, 9}}, 9));
}

TEST(VideoStitchingTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.videoStitching({{0, 4}, {2, 8}}, 5));
    ASSERT_EQ(1, solution.videoStitching({{5, 7}, {1, 8}, {0, 0}, {2, 3}, {4, 5}, {0, 6}, {5, 10}, {7, 10}}, 5));
}

}