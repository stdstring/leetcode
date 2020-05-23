class Solution
{
public:
    std::vector<int> getRow(int rowIndex)
    {
        if (rowIndex == 0)
            return {1};
        if (rowIndex == 1)
            return {1, 1};
        std::vector<int> result = {1, 1};
        for (int row = 2; row <= rowIndex; ++row)
        {
            int current = 1;
            for (int column = 1; column < row; ++column)
            {
                int value = current + result[column];
                current = result[column];
                result[column] = value;
            }
            result.push_back(1);
        }
        return result;
    }
};