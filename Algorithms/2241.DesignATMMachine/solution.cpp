#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class ATM
{
public:
    ATM() : _banknotesCount({0, 0, 0, 0, 0}), _banknotesValue({20, 50, 100, 200, 500})
    {
    }

    void deposit(std::vector<int> const &banknotesCount)
    {
        for (size_t index = 0; index < banknotesCount.size(); ++index)
            _banknotesCount[index] += banknotesCount[index];
    }

    std::vector<int> withdraw(int amount)
    {
        std::vector<int> banknotes(_banknotesValue.size(), 0);
        for (size_t rIndex = 0; rIndex < _banknotesCount.size(); ++rIndex)
        {
            const size_t index = _banknotesCount.size() - 1 - rIndex;
            const int count = static_cast<int>(std::min<uint64_t>(_banknotesCount[index], amount / _banknotesValue[index]));
            banknotes[index] = count;
            amount -= (count * _banknotesValue[index]);
            _banknotesCount[index] -= count;
        }
        if (amount > 0)
        {
            deposit(banknotes);
            return {-1};
        }
        return banknotes;
    }

private:
    std::vector<uint64_t> _banknotesCount;
    const std::vector<int> _banknotesValue;
};

}

namespace DesignATMMachineTask
{

TEST(DesignATMMachineTaskTests, Examples)
{
    ATM atm;
    ASSERT_NO_THROW(atm.deposit({0, 0, 1, 2, 1}));
    ASSERT_EQ(std::vector<int>({0, 0, 1, 0, 1}), atm.withdraw(600));
    ASSERT_NO_THROW(atm.deposit({0, 1, 0, 1, 1}));
    ASSERT_EQ(std::vector<int>({-1}), atm.withdraw(600));
    ASSERT_EQ(std::vector<int>({0, 1, 0, 0, 1}), atm.withdraw(550));
}

}