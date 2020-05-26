class Solution
{
public:
    int myAtoi(std::string const &str)
    {
        std::string::const_iterator iterator = str.cbegin();
        // skip leading whitespaces
        while (iterator != str.cend() && *iterator == ' ')
            ++iterator;
        if (iterator == str.cend())
            return 0;
        bool positive = true;
        // process optional sign
        if (*iterator == '+' || *iterator == '-')
        {
            positive = *iterator == '+';
            ++iterator;
        }
        long long result = 0;
        // process digits
        while (iterator != str.cend() && *iterator >= '0' && *iterator <= '9')
        {
            result = 10 * result + (*iterator - '0');
            if (positive && result > std::numeric_limits<int>::max())
                return std::numeric_limits<int>::max();
            if (!positive && (-result) < std::numeric_limits<int>::min())
                return std::numeric_limits<int>::min();
            ++iterator;
        }
        return positive ? result : -result;
    }
};