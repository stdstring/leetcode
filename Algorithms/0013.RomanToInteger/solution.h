class Solution
{
public:
    int romanToInt(std::string const &s)
    {
        int result = 0;
        for (int index = 0; index < s.size(); ++index)
        {
            result += (isSubtraction(s, index) ? -mRomanSymbols[s[index]] : mRomanSymbols[s[index]]);
        }
        return result;
    }

private:
    bool isSubtraction(std::string const &s, int index)
    {
        return index < (s.size() - 1) && mRomanSymbols[s[index]] < mRomanSymbols[s[index + 1]];
    }

    std::unordered_map<char, int> mRomanSymbols =
    {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };
};