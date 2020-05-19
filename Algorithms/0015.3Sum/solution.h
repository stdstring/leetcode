class Solution
{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int> const &nums)
    {
        std::vector<std::vector<int>> dest;
        std::vector<int> source(nums.begin(), nums.end());
        std::sort(source.begin(), source.end());
        int firstIndex = 0;
        while ((firstIndex + 2 < source.size()) && (source[firstIndex] <= 0))
        {
            int a = source[firstIndex];
            int secondIndex = firstIndex + 1;
            int thirdIndex = source.size() - 1;
            while (secondIndex < thirdIndex)
            {
                int b = source[secondIndex];
                int c = source[thirdIndex];
                int sum = a + b + c;
                if (sum == 0)
                {
                    dest.push_back({a, b, c});
                    secondIndex = nextItemIndex(source, secondIndex);
                }
                else if (sum < 0)
                {
                    secondIndex = nextItemIndex(source, secondIndex);
                }
                else if (sum > 0)
                {
                    --thirdIndex;
                }
            }
            firstIndex = nextItemIndex(source, firstIndex);
        }
        return dest;
    }

private:
    int nextItemIndex(std::vector<int> const &source, int currentIndex)
    {
        int currentValue = source[currentIndex];
        int nextIndex = currentIndex + 1;
        while ((nextIndex < source.size()) && (currentValue == source[nextIndex]))
            ++nextIndex;
        return nextIndex;
    }
};