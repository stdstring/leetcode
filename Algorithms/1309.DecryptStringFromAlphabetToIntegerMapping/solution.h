class Solution
{
public:
    std::string freqAlphabets(std::string const &s)
    {
        std::string result;
        for (int index = 0; index < s.size(); ++index)
        {
            if ((index + 2) < s.size() && s[index + 2] == '#')
            {
                result.push_back(decryptChar(s, index, 2));
                index += 2;
            }
            else
                result.push_back(decryptChar(s, index, 1));
        }
        return result;
    }

private:
    char decryptChar(std::string const &source, int pos, int len)
    {
        int code = 0;
        for (int shift = 0; shift < len; ++shift)
            code = 10 * code + (source[pos + shift] - '0');
        return 'a' + (code - 1);
    }
};