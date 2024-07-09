#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> validStrings(int n) const
    {
        std::vector<std::string> storage;
        std::string current;
        current.reserve(n);
        generate(n, storage, current);
        return storage;
    }

private:
    void generate(size_t n, std::vector<std::string> &storage, std::string &current) const
    {
        if (current.size() == n)
        {
            storage.emplace_back(current);
            return;
        }
        if (current.empty() || current.back() == '1')
        {
            current.push_back('0');
            generate(n, storage, current);
            current.pop_back();
        }
        current.push_back('1');
        generate(n, storage, current);
        current.pop_back();
    }
};

}

namespace GenerateBinStrWithoutAdjacentZerosTask
{

TEST(GenerateBinStrWithoutAdjacentZerosTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"010", "011", "101", "110", "111"}), solution.validStrings(3));
    ASSERT_EQ(std::vector<std::string>({"0", "1"}), solution.validStrings(1));
}

}