#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findPaths(int m, int n, int N, int i, int j) const
    {
        if (N == 0)
            return 0;
        size_t outPathsCount = 0;
        const size_t storageSize = static_cast<size_t>(m) * n;
        std::vector<size_t> current(storageSize, 0);
        // first step
        initStorage(m, n, i, j, current, outPathsCount);
        if (N == 1)
            return static_cast<int>(outPathsCount);
        std::vector<size_t> next(storageSize, 0);
        for (size_t step = 2; step <= static_cast<size_t>(N); ++step)
        {
            std::fill(next.begin(), next.end(), 0);
            for (size_t index = 0; index < current.size(); ++index)
            {
                const size_t row = index / n;
                const size_t column = index % n;
                if (current[index] != 0)
                    processCell(m, n, row, column, current, next, outPathsCount);
            }
            std::swap(current, next);
        }
        return static_cast<int>(outPathsCount);
    }

private:
    constexpr static size_t ModValue = 1000000007;

    void initStorage(size_t m, size_t n, size_t i, size_t j, std::vector<size_t> &current, size_t &outPathsCount) const
    {
        if (i > 0)
            current[(i - 1) * n + j] = 1;
        else
            ++outPathsCount;
        if (i < (m - 1))
            current[(i + 1) * n + j] = 1;
        else
            ++outPathsCount;
        if (j > 0)
            current[i * n + (j - 1)] = 1;
        else
            ++outPathsCount;
        if (j < (n - 1))
            current[i * n + (j + 1)] = 1;
        else
            ++outPathsCount;
    }

    void processCell(size_t m, size_t n, size_t i, size_t j, std::vector<size_t> const &current, std::vector<size_t> &next, size_t&outPathsCount) const
    {
        const size_t currentPathsCount = current[i * n + j];
        if (i > 0)
            next[(i - 1) * n + j] = (next[(i - 1) * n + j] + currentPathsCount) % ModValue;
        else
            outPathsCount = (outPathsCount + currentPathsCount) % ModValue;
        if (i < (m - 1))
            next[(i + 1) * n + j] = (next[(i + 1) * n + j] + currentPathsCount) % ModValue;
        else
            outPathsCount = (outPathsCount + currentPathsCount) % ModValue;
        if (j > 0)
            next[i * n + (j - 1)] = (next[i * n + (j - 1)] + currentPathsCount) % ModValue;
        else
            outPathsCount = (outPathsCount + currentPathsCount) % ModValue;
        if (j < (n - 1))
            next[i * n + (j + 1)] = (next[i * n + (j + 1)] + currentPathsCount) % ModValue;
        else
            outPathsCount = (outPathsCount + currentPathsCount) % ModValue;
    }
};

}

namespace OutOfBoundaryPathsTask
{

TEST(OutOfBoundaryPathsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.findPaths(2, 2, 2, 0, 0));
    ASSERT_EQ(12, solution.findPaths(1, 3, 3, 0, 1));
}

}