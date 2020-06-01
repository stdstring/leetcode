class Solution
{
public:
    bool validUtf8(std::vector<int> const &data)
    {
        int charStart = 0;
        while (charStart < data.size())
        {
            int octetCount = calcOctetCount(data[charStart]);
            if (octetCount == 0 || (charStart + octetCount) > data.size())
                return false;
            if (!checkOtherOctets(data, charStart, octetCount))
                return false;
            charStart += octetCount;
        }
        return true;
    }

private:
    int calcOctetCount(int firstOctet)
    {
        if ((firstOctet & 0b10000000) == 0)
            return 1;
        if ((firstOctet & 0b11100000) == 0b11000000)
            return 2;
        if ((firstOctet & 0b11110000) == 0b11100000)
            return 3;
        if ((firstOctet & 0b11111000) == 0b11110000)
            return 4;
        return 0;
    }

    bool checkOtherOctets(std::vector<int> const &data, int charStart, int octetCount)
    {
        for(int index = charStart + 1; index < charStart + octetCount; ++index)
        {
            if ((data[index] & 0b11000000) != 0b10000000)
                return false;
        }
        return true;
    }
};