#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Fancy
{
public:
    Fancy() = default;

    void append(int val)
    {
        values.emplace_back(val);
        operationStarts.emplace_back(operations.size());
    }

    void addAll(int inc)
    {
        if (canModifyOperation(Operation::Add))
            operations.back().second = (operations.back().second + inc) % modValue;
        else
            operations.emplace_back(Operation::Add, inc);
    }

    void multAll(int m)
    {
        if (canModifyOperation(Operation::Mult))
            operations.back().second = (operations.back().second * m) % modValue;
        else
            operations.emplace_back(Operation::Mult, m);
    }

    int getIndex(int idx)
    {
        const size_t index = idx;
        if (index >= values.size())
            return -1;
        long long value = values[index];
        for (size_t operationIndex = operationStarts[index]; operationIndex < operations.size(); ++operationIndex)
        {
            if (operations[operationIndex].first == Operation::Add)
                value = (value + operations[operationIndex].second) % modValue;
            else
                value = (value * operations[operationIndex].second) % modValue;
        }
        return static_cast<int>(value);
    }

private:
    static constexpr long long modValue = 1000000007;
    enum class Operation { Add, Mult };

    std::vector<std::pair<Operation, long long>> operations;
    std::vector<int> values;
    std::vector<size_t> operationStarts;

    bool canModifyOperation(Operation current) const
    {
        if (operations.empty() || (operations.back().first != current))
            return false;
        size_t prevOperationIndex = operations.size() - 1;
        if (values.empty() || (operationStarts.back() > prevOperationIndex))
            return false;
        return true;
    }
};

}

namespace FancySequenceTask
{

TEST(FancySequenceTaskTests, Examples)
{
    Fancy fancy;
    ASSERT_NO_THROW(fancy.append(2));
    ASSERT_NO_THROW(fancy.addAll(3));
    ASSERT_NO_THROW(fancy.append(7));
    ASSERT_NO_THROW(fancy.multAll(2));
    ASSERT_EQ(10, fancy.getIndex(0));
    ASSERT_NO_THROW(fancy.addAll(3));
    ASSERT_NO_THROW(fancy.append(10));
    ASSERT_NO_THROW(fancy.multAll(2));
    ASSERT_EQ(26, fancy.getIndex(0));
    ASSERT_EQ(34, fancy.getIndex(1));
    ASSERT_EQ(20, fancy.getIndex(2));
}

TEST(FancySequenceTaskTests, FromWrongAnswers)
{
    Fancy fancy;
    ASSERT_NO_THROW(fancy.append(5));
    ASSERT_EQ(5, fancy.getIndex(0));
    ASSERT_NO_THROW(fancy.addAll(4));
    ASSERT_NO_THROW(fancy.append(3));
    ASSERT_NO_THROW(fancy.append(4));
    ASSERT_NO_THROW(fancy.append(2));
    ASSERT_NO_THROW(fancy.addAll(7));
    ASSERT_EQ(16, fancy.getIndex(0));
    ASSERT_EQ(10, fancy.getIndex(1));
}

}