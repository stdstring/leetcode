class Solution
{
public:
    int divide(int dividend, int divisor)
    {
        long long ldividend = dividend;
        if (dividend < 0)
            ldividend = -ldividend;
        long long ldivisor = divisor;
        if (divisor < 0)
            ldivisor = -ldivisor;
        bool negativeResult = (dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0);
        if (ldividend == ldivisor)
            return negativeResult ? -1 : 1;
        if (ldividend < ldivisor)
            return 0;
        if (ldivisor == 1)
        {
            ldividend = negativeResult ? -ldividend : ldividend;
            return ldividend > std::numeric_limits<int>::max() ? std::numeric_limits<int>::max() : ldividend;
        }
        long long quotient = 0;
        long long remainder = 0;
        // from https://en.wikipedia.org/wiki/Division_algorithm
        for (int i = calcHighestSignificantBitNumber(ldividend); i >= 0; --i)
        {
            remainder <<= 1;
            if ((ldividend & (1 << i)) > 0)
                remainder |= 1;
            if (remainder >= ldivisor)
            {
                remainder -= ldivisor;
                quotient |= (1 << i);
            }
        }
        quotient = negativeResult ? -quotient : quotient;
        return quotient;
    }

private:
    int calcHighestSignificantBitNumber(long long n)
    {
        for (long long number = 31; number >= 0; --number)
        {
            if ((1 << number) <= n)
                return number;
        }
        return 0;
    }
};