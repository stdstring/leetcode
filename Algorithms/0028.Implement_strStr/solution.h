class Solution
{
public:
    int strStr(std::string const &haystack, std::string const &needle)
    {
        if (needle.size() == 0)
            return 0;
        if (haystack.size() < needle.size())
            return -1;
        for (int i = 0; i <= (haystack.size() - needle.size()); ++i)
        {
            bool isMatch = true;
            for (int j = 0; j < needle.size(); ++j)
            {
                if (haystack[i + j] != needle[j])
                {
                    isMatch = false;
                    break;
                }
            }
            if (isMatch)
                return i;
        }
        return -1;
    }
};