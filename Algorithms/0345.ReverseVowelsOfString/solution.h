class Solution
{
public:
    std::string reverseVowels(std::string const &s)
    {
        std::string result(s);
        int forward = findVowelForward(result, 0);
        int backward = findVowelBackward(result, result.size() - 1);
        while (forward < backward)
        {
            std::swap(result[forward], result[backward]);
            forward = findVowelForward(result, forward + 1);
            backward = findVowelBackward(result, backward - 1);
        }
        return result;
    }

private:
    bool IsVowel(char ch)
    {
        return (ch == 'a') ||
               (ch == 'A') ||
               (ch == 'e') ||
               (ch == 'E') ||
               (ch == 'i') ||
               (ch == 'I') ||
               (ch == 'o') ||
               (ch == 'O') ||
               (ch == 'u') ||
               (ch == 'U');
    }

    int findVowelForward(std::string const &source, int index)
    {
        while (index < source.size() && !IsVowel(source[index]))
            ++index;
        return index;
    }

    int findVowelBackward(std::string const &source, int index)
    {
        while (index >= 0 && !IsVowel(source[index]))
            --index;
        return index;
    }
};