class Solution
{
public:
    int missingNumber(std::vector<int> const &nums)
    {
        int maxN = nums.size() + 1;
        int actualSum = std::accumulate(nums.cbegin(), nums.cend(), 0);
        int expectedSum = (0 + maxN - 1) * maxN / 2;
        return expectedSum - actualSum;
    }
};