class Solution {
public:
    int reverse(int x) {
        if (x == 0)
            return 0;
        bool sign = x < 0;
        std::vector<int> digits;
        long long sourceValue = x;
        if (sign)
            sourceValue = - sourceValue;
        // digits in reverse order
        while (sourceValue > 0)
        {
            digits.push_back(sourceValue % 10);
            sourceValue /= 10;
        }
        // reversed number
        long long destValue = 0;
        for (std::vector<int>::const_iterator it = digits.cbegin(); it != digits.cend(); ++it)
        {
            destValue = 10 * destValue + (*it);
        }
        if (sign)
            destValue = - destValue;
        return (destValue > std::numeric_limits<int>::max()) || (destValue < std::numeric_limits<int>::min()) ? 0 : destValue;
    }
};