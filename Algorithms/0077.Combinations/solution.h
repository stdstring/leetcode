class Solution {
public:
    std::vector<std::vector<int>> combine(int n, int k) {
        std::vector<std::vector<int>> combinations;
        std::vector<int> buffer;
        buffer.reserve(k);
        combineImpl(n, k, combinations, buffer);
        return combinations;
    }

private:
    void combineImpl(int n, int k, std::vector<std::vector<int>> &combinations, std::vector<int> &buffer)
    {
        if (buffer.size() == k)
        {
            combinations.push_back(std::vector<int>(buffer));
        }
        else
        {
            int size = buffer.size();
            for (int number = size == 0 ? 1 : buffer.back() + 1; number <= (n - k + size + 1); ++number)
            {
                buffer.push_back(number);
                combineImpl(n, k, combinations, buffer);
                buffer.pop_back();
            }
        }
    }
};