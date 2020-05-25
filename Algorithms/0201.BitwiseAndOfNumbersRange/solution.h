class Solution
{
public:
    int rangeBitwiseAnd(int m, int n)
    {
        int result = m & n;
        int mask = 0;
        int shift = 0;
        while (n > 0)
        {
            if ((m & 1) ^ (n & 1) == 1)
                mask = 0;
            else
                mask |= (1 << shift);
            m >>= 1;
            n >>= 1;
            ++shift;
        }
        return result & mask;
    }
};