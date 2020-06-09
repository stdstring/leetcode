class Solution
{
public:
    bool isPowerOfTwo(int n)
    {
        for (int pow = 0, value = 1; pow <= 30; ++pow, value <<= 1)
        {
            if (n == value)
                return true;
            if (n < value)
                return false;
        }
        return false;
    }
};