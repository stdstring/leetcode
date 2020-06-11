class Solution
{
public:
    std::string countAndSay(int n)
    {
        std::string current("1");
        for (int term = 2; term <= n; ++term)
            current = generateNext(current);
        return current;
    }

private:
    std::string generateNext(std::string const & current)
    {
        std::string next;
        int index = 0;
        while (index < current.size())
        {
            char digit = current[index];
            int count = 1;
            while ((index + count) < current.size() && current[index + count] == digit)
                ++count;
            next.append(std::to_string(count));
            next.push_back(digit);
            index += count;
        }
        return next;
    }
};