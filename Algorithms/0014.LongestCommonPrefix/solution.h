class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        if (strs.size() == 0)
            return "";
        std::string dest;
        int index = 0;
        while (checkIndex(strs, index))
        {
            dest.push_back(strs[0][index]);
            ++index;
        }
        return dest;
    }
    
private:
    bool checkIndex(std::vector<std::string> const& strs, int index)
    {
        if (strs[0].size() <= index)
            return false;
        char expectedChar = strs[0][index];
        for(int strIndex = 1; strIndex < strs.size(); ++strIndex)
        {
            if (strs[strIndex].size() <= index)
                return false;
            if (expectedChar != strs[strIndex][index])
                return false;
        }
        return expectedChar != 0;
    }
};