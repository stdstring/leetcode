class Solution
{
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals)
    {
        if (intervals.empty())
            return {};
        std::sort(intervals.begin(), intervals.end(), [](std::vector<int> const &left, std::vector<int> const &right){ return left[0] < right[0]; });
        std::vector<std::vector<int>> dest;
        dest.push_back(intervals[0]);
        for (int index = 1; index < intervals.size(); ++index)
        {
            if (intervals[index][1] <= dest.back()[1])
            {
                // do nothing
            }
            else if (intervals[index][0] <= dest.back()[1])
                dest.back()[1] = intervals[index][1];
            else
                dest.push_back(intervals[index]);
        }
        return dest;
    }
};