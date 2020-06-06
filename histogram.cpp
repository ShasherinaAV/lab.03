#include<vector>
#include"histogram.h"
using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max)
{
    min = numbers[0];
    max = numbers[0];
    for(double numb: numbers)
    {
        if (numb < min)
        {
            min = numb;
        }
        if (numb > max)
        {
            max = numb;
        }
    }
}
