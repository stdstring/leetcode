class Solution
{
public:
    std::string intToRoman(int num)
    {
        std::string result;
        int thousands = num / 1000;
        for (int counter = 1; counter <= thousands; ++counter)
            result.push_back('M');
        int hundreds = (num % 1000) / 100;
        result.append(mRomanHundreds[hundreds]);
        int tens = (num % 100) / 10;
        result.append(mRomanTens[tens]);
        int ones = num % 10;
        result.append(mRomanOnes[ones]);
        return result;
    }

private:
    std::string mRomanOnes[10] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    std::string mRomanTens[10] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    std::string mRomanHundreds[10] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
};