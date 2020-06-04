class Solution
{
public:
    std::vector<std::string> letterCombinations(std::string const &digits)
    {
        if (digits.empty())
            return {};
        std::vector<std::string> result;
        createLetterCombinations(digits, result, "");
        return result;
    }

private:
    void createLetterCombinations(std::string const &source, std::vector<std::string> &dest, std::string const &prefix)
    {
        int currentIndex = prefix.size();
        int currentDigit = source[currentIndex] - '0';
        if (mDigitLetters[currentDigit].empty())
            return;
        for (char letter : mDigitLetters[currentDigit])
        {
            std::string current(prefix);
            current.push_back(letter);
            if (currentIndex == (source.size() - 1))
                dest.push_back(current);
            else
                createLetterCombinations(source, dest, current);
        }
    }

    std::string mDigitLetters[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
};