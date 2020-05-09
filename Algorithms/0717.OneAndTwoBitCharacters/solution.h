#include <vector>

class Solution {
public:
    bool isOneBitCharacter(std::vector<int> const &bits) {
        int countOfOnes = 0;
        for (std::vector<int>::const_reverse_iterator iterator = bits.crbegin() + 1; iterator != bits.crend() && (*iterator) == 1; ++iterator) {
            ++countOfOnes;
        }
        return (countOfOnes % 2) == 0;
    }
};