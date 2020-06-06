class Solution
{
public:
    void reverseString(std::vector<char> &s)
    {
        //std::reverse(s.begin(), s.end());
        int first = 0;
        int last = s.size() - 1;
        while (first < last)
        {
            std::swap(s[first], s[last]);
            ++first;
            --last;
        }
    }
};