#include <vector>

#include "gtest/gtest.h"

namespace
{

class Bank
{
public:
    Bank(std::vector<long long> const &balance) : _accounts(balance)
    {
    }

    bool transfer(int account1, int account2, long long money)
    {
        const size_t account1Index = account1 - 1;
        const size_t account2Index = account2 - 1;
        if ((account1Index >= _accounts.size()) || (account2Index >= _accounts.size()))
            return false;
        if (_accounts[account1Index] < money)
            return false;
        _accounts[account1Index] -= money;
        _accounts[account2Index] += money;
        return true;
    }

    bool deposit(int account, long long money)
    {
        const size_t accountIndex = account - 1;
        if (accountIndex >= _accounts.size())
            return false;
        _accounts[accountIndex] += money;
        return true;
    }

    bool withdraw(int account, long long money)
    {
        const size_t accountIndex = account - 1;
        if (accountIndex >= _accounts.size())
            return false;
        if (_accounts[accountIndex] < money)
            return false;
        _accounts[accountIndex] -= money;
        return true;
    }

private:
    std::vector<long long> _accounts;
};

}

namespace SimpleBankSystemTask
{

TEST(SimpleBankSystemTaskTests, Examples)
{
    Bank bankSystem({10, 100, 20, 50, 30});
    ASSERT_EQ(true, bankSystem.withdraw(3, 10));
    ASSERT_EQ(true, bankSystem.transfer(5, 1, 20));
    ASSERT_EQ(true, bankSystem.deposit(5, 20));
    ASSERT_EQ(false, bankSystem.transfer(3, 4, 15));
    ASSERT_EQ(false, bankSystem.withdraw(10, 50));
}

}