class Solution
{
public:
    int rangeBitwiseAnd(int m, int n)
    {
        int result = 0;
        int shift = 0;
        while (n > 0)
        {
            int mValue = m & 1;
            if (mValue ^ (n & 1) == 1)
                result = 0;
            else
                result |= (mValue << shift);
            m >>= 1;
            n >>= 1;
            ++shift;
        }
        return result;
    }
};