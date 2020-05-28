class Solution
{
public:
    bool isNumber(std::string const &s)
    {
        std::string::const_iterator iterator = s.cbegin();
        skipWhitespaces(iterator, s.cend());
        if (!checkMantis(iterator, s.cend()))
            return false;
        if (iterator == s.cend())
            return true;
        if (*iterator == ' ')
        {
            skipWhitespaces(iterator, s.cend());
            return iterator == s.cend();
        }
        if (!checkExponent(iterator, s.cend()))
            return false;
        skipWhitespaces(iterator, s.cend());
        return iterator == s.cend();
    }

private:
    void skipWhitespaces(std::string::const_iterator &iterator, std::string::const_iterator end)
    {
        while(iterator != end && *iterator == ' ')
            ++iterator;
    }

    bool checkMantis(std::string::const_iterator &iterator, std::string::const_iterator end)
    {
        if (*iterator == '+' || *iterator == '-')
            ++iterator;
        int integralDigitsCount = 0;
        while(iterator != end && *iterator >= '0' && *iterator <= '9')
        {
            ++iterator;
            ++integralDigitsCount;
        }
        if (iterator == end)
            return integralDigitsCount > 0;
        if (*iterator == 'e')
            return integralDigitsCount > 0;
        if (*iterator == ' ')
            return true;
        if (*iterator != '.')
            return false;
        int fractionalDigitsCount = 0;
        ++iterator;
        while(iterator != end && *iterator >= '0' && *iterator <= '9')
        {
            ++iterator;
            ++fractionalDigitsCount;
        }
        if (iterator == end)
            return (integralDigitsCount > 0) || (fractionalDigitsCount > 0);
        if (*iterator == 'e')
            return (integralDigitsCount > 0) || (fractionalDigitsCount > 0);
        if (*iterator == ' ')
            return (integralDigitsCount > 0) || (fractionalDigitsCount > 0);
        return false;
    }

    bool checkExponent(std::string::const_iterator &iterator, std::string::const_iterator end)
    {
        if (*iterator != 'e')
            return false;
        ++iterator;
        if (*iterator == '+' || *iterator == '-')
            ++iterator;
        int digitsCount = 0;
        while(iterator != end && *iterator >= '0' && *iterator <= '9')
        {
            ++iterator;
            ++digitsCount;
        }
        if (digitsCount == 0)
            return false;
        if (iterator == end)
            return true;
        return *iterator == ' ';
    }
};