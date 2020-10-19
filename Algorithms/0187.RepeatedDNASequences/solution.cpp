#include <array>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::string> findRepeatedDnaSequences(std::string const &s) const
    {
        std::vector<unsigned int> sequenceCountData(maskSize, 0);
        unsigned int sequence = generateInitSequence(s);
        sequenceCountData[sequence] = 1;
        for (size_t index = sequenceSize; index < s.size(); ++index)
        {
            sequence = generateNextSequence(s, index, sequence);
            sequenceCountData[sequence] += 1;
        }
        std::vector<std::string> dest;
        for (size_t mask = 0; mask < maskSize; ++mask)
        {
            if (sequenceCountData[mask] > 1)
                dest.push_back(restoreSequence(mask));
        }
        return dest;
    }

private:
    constexpr static size_t sequenceSize = 10;
    constexpr static unsigned int maskSize = 1 << (2 * sequenceSize);
    constexpr static unsigned int fullMask = maskSize - 1;

    unsigned int convertNucleotideToInt(char nucleotide) const
    {
        switch (nucleotide)
        {
            case 'A':
                return 0b00;
            case 'C':
                return 0b01;
            case 'G':
                return 0b10;
            case 'T':
                return 0b11;
            default:
                return 0b00;
        }
    }

    unsigned int generateNextSequence(std::string const &s, size_t index, unsigned int prevSequence) const
    {
        return (fullMask & (prevSequence << 2)) | convertNucleotideToInt(s[index]);
    }

    unsigned int generateInitSequence(std::string const &s) const
    {
        unsigned int sequence = 0;
        for (size_t index = 0; index < sequenceSize; ++index)
            sequence = (sequence << 2) | convertNucleotideToInt(s[index]);
        return sequence;
    }

    char convertIntToNucleotide(unsigned int nucleotide) const
    {
        switch (nucleotide)
        {
            case 0b00:
                return 'A';
            case 0b01:
                return 'C';
            case 0b10:
                return 'G';
            case 0b11:
                return 'T';
            default:
                return '\0';
        }
    }

    std::string restoreSequence(unsigned int sequence) const
    {
        std::string dest(sequenceSize, '\0');
        for (size_t index = 0; index < sequenceSize; ++index)
        {
            dest[sequenceSize - index - 1] = convertIntToNucleotide(sequence & 0b11);
            sequence >>= 2;
        }
        return dest;
    }
};

}

namespace RepeatedDNASequencesTask
{

TEST(RepeatedDNASequencesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"AAAAACCCCC", "CCCCCAAAAA"}), solution.findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"));
    ASSERT_EQ(std::vector<std::string>({"AAAAAAAAAA"}), solution.findRepeatedDnaSequences("AAAAAAAAAAAAA"));
}


}