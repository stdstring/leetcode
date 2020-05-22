class Solution
{
public:
    double myPow(double x, int n)
    {
        if (n == 0)
            return 1;
        if (n == 1)
            return x;
        if (n == 2)
            return x * x;
        if (n == -1)
            return 1 / x;
        if (n == -2)
            return 1 / (x * x);
        if (n > 0)
        {
            double halfPowerValue = myPow(x, n / 2);
            double result = halfPowerValue * halfPowerValue;
            return n % 2 == 0 ? result : x * result;
        }
        else
        {
            double halfPowerValue = myPow(x, n / 2);
            double result = halfPowerValue * halfPowerValue;
            return n % 2 == 0 ? result : result / x;
        }
    }
};