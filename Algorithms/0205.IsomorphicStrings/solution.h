class Solution
{
public:
    bool isIsomorphic(std::string const &s, std::string const &t)
    {
        std::array<char, UCHAR_MAX + 1> firstSecondMap;
        firstSecondMap.fill(0);
        std::array<char, UCHAR_MAX + 1> secondFirstMap;
        secondFirstMap.fill(0);
        for(int index = 0; index < s.size(); ++index)
        {
            if (firstSecondMap[s[index]] == 0 && secondFirstMap[t[index]] == 0)
            {
                firstSecondMap[s[index]] = t[index];
                secondFirstMap[t[index]] = s[index];
            }
            else if (firstSecondMap[s[index]] != t[index] || secondFirstMap[t[index]] != s[index])
                return false;
        }
        return true;
    }
};