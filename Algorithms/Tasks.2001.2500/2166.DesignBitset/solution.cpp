#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Bitset
{
public:
    Bitset(int size) : _storage(size / sizeof(uint64_t) + (size % sizeof(uint64_t) > 0 ? 1 : 0), 0), _bitCount(size), _oneBitCount(0), _hasFlip(false)
    {
    }

    void fix(int idx)
    {
        const size_t numberIndex = idx / sizeof(uint64_t);
        const int bitMask = 1 << (idx % sizeof(uint64_t));
        const uint64_t value = _storage[numberIndex] & bitMask;
        if ((value == 0) && !_hasFlip)
        {
            _storage[numberIndex] |= bitMask;
            ++_oneBitCount;
        }
        if ((value > 0) && _hasFlip)
        {
            _storage[numberIndex] &= ~bitMask;
            --_oneBitCount;
        }
    }

    void unfix(int idx)
    {
        const size_t numberIndex = idx / sizeof(uint64_t);
        const int bitMask = 1 << (idx % sizeof(uint64_t));
        const uint64_t value = _storage[numberIndex] & bitMask;
        if ((value > 0) && !_hasFlip)
        {
            _storage[numberIndex] &= ~bitMask;
            --_oneBitCount;
        }
        if ((value == 0) && _hasFlip)
        {
            _storage[numberIndex] |= bitMask;
            ++_oneBitCount;
        }
    }

    void flip()
    {
        _hasFlip = !_hasFlip;
    }

    [[nodiscard]] bool all() const
    {
        return count() == _bitCount;
    }

    [[nodiscard]] bool one() const
    {
        return count() > 0;
    }

    [[nodiscard]] int count() const
    {
        return _hasFlip ? _bitCount - _oneBitCount : _oneBitCount;
    }

    [[nodiscard]] std::string toString() const
    {
        std::string result(_bitCount, '0');
        const size_t bitCount = _bitCount;
        for (size_t index = 0; index < bitCount; ++index)
        {
            const size_t numberIndex = index / sizeof(uint64_t);
            const int bitMask = 1 << (index % sizeof(uint64_t));
            const uint64_t value = _storage[numberIndex] & bitMask;
            if ((value > 0) && !_hasFlip)
                result[index] = '1';
            if ((value == 0) && _hasFlip)
                result[index] = '1';
        }
        return result;
    }

private:
    std::vector<uint64_t> _storage;
    int _bitCount;
    int _oneBitCount;
    bool _hasFlip;
};

}

namespace DesignBitsetTask
{

TEST(DesignBitsetTaskTests, Examples)
{
    Bitset bitset(5);
    ASSERT_NO_THROW(bitset.fix(3));
    ASSERT_NO_THROW(bitset.fix(1));
    ASSERT_NO_THROW(bitset.flip());
    ASSERT_EQ(false, bitset.all());
    ASSERT_NO_THROW(bitset.unfix(0));
    ASSERT_NO_THROW(bitset.flip());
    ASSERT_EQ(true, bitset.one());
    ASSERT_NO_THROW(bitset.unfix(0));
    ASSERT_EQ(2, bitset.count());
    ASSERT_EQ("01010", bitset.toString());
}

TEST(DesignBitsetTaskTests, FromWrongAnswers)
{
    Bitset bitset(2);
    ASSERT_NO_THROW(bitset.flip());
    ASSERT_NO_THROW(bitset.unfix(1));
    ASSERT_EQ(false, bitset.all());
    ASSERT_NO_THROW(bitset.fix(1));
    ASSERT_NO_THROW(bitset.fix(1));
    ASSERT_NO_THROW(bitset.unfix(1));
    ASSERT_EQ(false, bitset.all());
    ASSERT_EQ(1, bitset.count());
    ASSERT_EQ("10", bitset.toString());
    ASSERT_EQ("10", bitset.toString());
    ASSERT_EQ("10", bitset.toString());
    ASSERT_NO_THROW(bitset.unfix(0));
    ASSERT_NO_THROW(bitset.flip());
    ASSERT_EQ(true, bitset.all());
    ASSERT_NO_THROW(bitset.unfix(0));
    ASSERT_EQ(true, bitset.one());
    ASSERT_EQ(true, bitset.one());
    ASSERT_EQ(false, bitset.all());
    ASSERT_NO_THROW(bitset.fix(0));
    ASSERT_NO_THROW(bitset.unfix(0));
}

}