#include <iostream>
#include <string>
#include <vector>


/*Implement a matrix class that support both floating point values and integer values. The matrix class shall support the following methods: 
1. Initialize with size and values 
2. Change value of member 
3. Support matrix and vector multiplication 
4. Be efficient in memory and operations */


using namespace std;

template <class T>
class myMatrix
{
public:
    myMatrix(vector<T>& m, const int col)
    {
        m_matrix = vector<T>(m.begin(), m.end());
        m_col = col;
        m_row = m_matrix.size() / m_col;
    }
    
    void changeValue(const int x, const int y, const T value)
    {
        int index = x * m_col + y;
        m_matrix[index] = value;
    }
    
    vector<T> mul(const vector<T>& in_v)
    {
        if(in_v.size() != m_col)
        {
            return {};
        }
        vector<T> m_out(m_row, 0);
        
        for(int i = 0; i < m_row; i++)
        {
            T temp_sum = 0;
            for(int j = 0; j < m_col; j++)
            {
                int index = i * m_row + j;
                temp_sum += m_matrix[index] * in_v[j];
            }
            m_out[i] = temp_sum;
        }
        
        return m_out;
    }
    
public:
    vector<T> m_matrix;
private:
    int m_col;
    int m_row;
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    vector<int> test_m{1,2,3,4};
    myMatrix<int> test(test_m, 2);
    vector<int> m_out = test.m_matrix;
    for(auto it:m_out) cout<<it<<endl;
    vector<int> in_v(1,1);
    vector<int> mul_out = test.mul(in_v);
    for(auto it:mul_out) cout<<it<<endl;
    
    return 0;
}

