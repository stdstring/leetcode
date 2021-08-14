#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int calPoints(std::vector<std::string> const &ops) const
    {
        std::vector<int> records;
        for (std::string const &op : ops)
            processOperation(op, records);
        return std::accumulate(records.cbegin(), records.cend(), 0);
    }

private:
    void processOperation(std::string const &op, std::vector<int> &records) const
    {
        if (op == "+")
        {
            records.push_back(records[records.size() - 1] + records[records.size() - 2]);
            return;
        }
        if (op == "D")
        {
            records.push_back(2 * records.back());
            return;
        }
        if (op == "C")
        {
            records.pop_back();
            return;
        }
        records.push_back(std::stoi(op));
    }
};

}

namespace BaseballGameTask
{

TEST(BaseballGameTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(30, solution.calPoints({"5", "2", "C", "D", "+"}));
    ASSERT_EQ(27, solution.calPoints({"5", "-2", "4", "C", "D", "9", "+", "+"}));
    ASSERT_EQ(1, solution.calPoints({"1"}));
}

}