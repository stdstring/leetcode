#include <stack>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> exclusiveTime(int n, std::vector<std::string> const &logs) const
    {
        constexpr char delimiter = ':';
        std::vector<int> functionsExecTime(n, 0);
        std::stack<int> functionStack;
        int currentTime = 0;
        for (std::string const &logEntry : logs)
        {
            const size_t delimiterPos1 = logEntry.find(delimiter, 0);
            const size_t delimiterPos2 = logEntry.find(delimiter, delimiterPos1 + 1);
            int id = std::stoi(logEntry.substr(0, delimiterPos1));
            std::string operation(logEntry.substr(delimiterPos1 + 1, delimiterPos2 - delimiterPos1 - 1));
            const int time = std::stoi(logEntry.substr(delimiterPos2 + 1));
            if (functionStack.empty())
            {
                currentTime = time;
                // assert(operation == "start")
                functionStack.push(id);
            }
            else
            {
                if (operation == "start")
                {
                    functionsExecTime[functionStack.top()] += (time - currentTime);
                    functionStack.push(id);
                    currentTime = time;
                }
                else
                {
                    functionsExecTime[functionStack.top()] += (time - currentTime + 1);
                    functionStack.pop();
                    currentTime = time + 1;
                }
            }
        }
        return functionsExecTime;
    }
};

}

namespace ExclusiveTimeOfFunctionsTask
{

TEST(ExclusiveTimeOfFunctionsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({3, 4}), solution.exclusiveTime(2, {"0:start:0", "1:start:2", "1:end:5", "0:end:6"}));
    ASSERT_EQ(std::vector<int>({8}), solution.exclusiveTime(1, {"0:start:0", "0:start:2", "0:end:5", "0:start:6", "0:end:6", "0:end:7"}));
    ASSERT_EQ(std::vector<int>({7, 1}), solution.exclusiveTime(2, {"0:start:0", "0:start:2", "0:end:5", "1:start:6", "1:end:6", "0:end:7"}));
    ASSERT_EQ(std::vector<int>({8, 1}), solution.exclusiveTime(2, {"0:start:0", "0:start:2", "0:end:5", "1:start:7", "1:end:7", "0:end:8"}));
    ASSERT_EQ(std::vector<int>({1}), solution.exclusiveTime(1, {"0:start:0", "0:end:0"}));
}

}