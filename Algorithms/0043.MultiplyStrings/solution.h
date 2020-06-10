class Solution
{
public:
    std::string multiply(std::string const &num1, std::string const &num2)
    {
        std::string const &number1 = num1.size() >= num2.size() ? num1 : num2;
        std::string const &number2 = num1.size() < num2.size() ? num1 : num2;
        if (number1 == "0" || number2 == "0")
            return "0";
        if (number1 == "1")
            return number2;
        if (number2 == "1")
            return number1;
        std::string buffer;
        int shift = 0;
        for (std::string::const_reverse_iterator iterator = number2.crbegin(); iterator != number2.crend(); ++iterator)
            processDigitMultiplication(buffer, number1, *iterator, shift++);
        return std::string(buffer.rbegin(), buffer.rend());
    }

private:
    void processDigitMultiplication(std::string &buffer, std::string const &num, char digit, int shift)
    {
        if (digit == '0')
            return;
        int bufferIndex = 0;
        for (int shiftValue = 1; shiftValue <= shift; ++shiftValue)
        {
            if (bufferIndex == buffer.size())
                buffer.push_back('0');
            ++bufferIndex;
        }
        int factor = digit - '0';
        int carry = 0;
        for (std::string::const_reverse_iterator iterator = num.crbegin(); iterator != num.crend(); ++iterator)
        {
            if (bufferIndex < buffer.size())
            {
                int result = buffer[bufferIndex] - '0' + factor * (*iterator - '0') + carry;
                buffer[bufferIndex] = '0' + result % 10;
                carry = result / 10;
            }
            else
            {
                int result = factor * (*iterator - '0') + carry;
                buffer.push_back('0' + result % 10);
                carry = result / 10;
            }
            ++bufferIndex;
        }
        while (bufferIndex < buffer.size() && carry > 0)
        {
            int result = (buffer[bufferIndex] - '0') + carry;
            buffer[bufferIndex] = '0' + result % 10;
            carry = result / 10;
            ++bufferIndex;
        }
        if (carry != 0)
            buffer.push_back('0' + carry);
    }
};