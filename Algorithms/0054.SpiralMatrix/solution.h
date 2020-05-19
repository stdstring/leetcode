class Solution
{
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>> const &matrix)
    {
        if (matrix.size() == 0)
            return {};
        int m = matrix.size();
        int n = matrix[0].size();
        std::vector<int> dest;
        dest.reserve(m * n);
        int rowMin = 0;
        int rowMax = m - 1;
        int columnMin = 0;
        int columnMax = n - 1;
        while ((rowMin <= rowMax) && (columnMin <= columnMax))
        {
            processLayer(matrix, dest, rowMin, rowMax, columnMin, columnMax);
            ++rowMin;
            --rowMax;
            ++columnMin;
            --columnMax;
        }
        return dest;
    }

private:
    void processLayer(std::vector<std::vector<int>> const &matrix, std::vector<int> &dest, int rowMin, int rowMax, int columnMin, int columnMax)
    {
        if (rowMin == rowMax)
        {
            for(int column = columnMin; column <= columnMax; ++column)
            {
                dest.push_back(matrix[rowMin][column]);
            }
            return;
        }
        if (columnMin == columnMax)
        {
            for(int row = rowMin; row <= rowMax; ++row)
            {
                dest.push_back(matrix[row][columnMin]);
            }
            return;
        }
        for(int column = columnMin; column <= columnMax; ++column)
        {
            dest.push_back(matrix[rowMin][column]);
        }
        for(int row = rowMin + 1; row <= rowMax; ++row)
        {
            dest.push_back(matrix[row][columnMax]);
        }
        for(int column = columnMax - 1; column >= columnMin; --column)
        {
            dest.push_back(matrix[rowMax][column]);
        }
        for(int row = rowMax - 1; row > rowMin; --row)
        {
            dest.push_back(matrix[row][columnMin]);
        }
    }
};