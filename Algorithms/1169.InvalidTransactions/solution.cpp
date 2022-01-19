#include <algorithm>
#include <deque>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct Transaction
{
    Transaction(std::string const &name, int time, int amount, std::string const &city, size_t sourceIndex) :
        Name(name), Time(time), Amount(amount), City(city), SourceIndex(sourceIndex), Valid(true)
    {
    }

    std::string Name;
    int Time;
    int Amount;
    std::string City;
    size_t SourceIndex;
    bool Valid;

    static Transaction parse(std::string const &source, size_t sourceIndex)
    {
        const size_t nameComma = source.find(',');
        const std::string name(source.substr(0, nameComma));
        const size_t timeComma = source.find(',', nameComma + 1);
        const int time = std::stoi(source.substr(nameComma + 1, timeComma - nameComma - 1));
        const size_t amountComma = source.find(',', timeComma + 1);
        const int amount = std::stoi(source.substr(timeComma + 1, amountComma - timeComma - 1));
        const std::string city(source.substr(amountComma + 1));
        return Transaction(name, time, amount, city, sourceIndex);
    }
};

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> invalidTransactions(std::vector<std::string> const &transactions) const
    {
        std::vector<Transaction> data;
        for (size_t index = 0; index < transactions.size(); ++index)
            data.push_back(Transaction::parse(transactions[index], index));
        std::sort(data.begin(), data.end(), [](Transaction const &left, Transaction const &right){ return left.Time < right.Time; });
        std::unordered_map<std::string, std::deque<Transaction*>> nameTransactionQueueMap;
        for (Transaction &transaction : data)
        {
            if (transaction.Amount > MaxAmount)
                transaction.Valid = false;
            actualizeTransactionQueue(nameTransactionQueueMap[transaction.Name], transaction.Time);
            for (Transaction *otherTransaction : nameTransactionQueueMap[transaction.Name])
            {
                if (otherTransaction->City != transaction.City)
                    otherTransaction->Valid = transaction.Valid = false;
            }
            nameTransactionQueueMap[transaction.Name].push_back(&transaction);
        }
        std::vector<std::string> result;
        for (Transaction const &transaction : data)
        {
            if (!transaction.Valid)
                result.push_back(transactions[transaction.SourceIndex]);
        }
        return result;
    }

private:
    static constexpr int MaxTimeDelta = 60;
    static constexpr int MaxAmount = 1000;

    void actualizeTransactionQueue(std::deque<Transaction*> &queue, int time) const
    {
        while (!queue.empty() && (queue.front()->Time + MaxTimeDelta < time))
            queue.pop_front();
    }
};

}

namespace InvalidTransactionsTask
{

TEST(InvalidTransactionsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"alice,20,800,mtv", "alice,50,100,beijing"}), solution.invalidTransactions({"alice,20,800,mtv", "alice,50,100,beijing"}));
    ASSERT_EQ(std::vector<std::string>({"alice,50,1200,mtv"}), solution.invalidTransactions({"alice,20,800,mtv", "alice,50,1200,mtv"}));
    ASSERT_EQ(std::vector<std::string>({"bob,50,1200,mtv"}), solution.invalidTransactions({"alice,20,800,mtv", "bob,50,1200,mtv"}));
}

}