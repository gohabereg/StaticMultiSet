#include <iostream>
#include "StatisticMultiset.h"
int main()
{
    std::cout << "Lab 02" << std::endl;
    StatisticMultiset<int> ms1;
    ms1.add( 89 );
    ms1.add( 54 );
    ms1.add( 54 );
    ms1.add( 24 );
    StatisticMultiset<int> ms2;
    std::vector<int> somedata = { 10, 40, 6, 87 };
    ms2.add( somedata );
    StatisticMultiset<int> ms3;
    ms3.add( ms1 );
    ms3.add( ms2 );
    std::cout << "Min: " << ms3.min()
              << " Avg: " << ms3.avg()
              << " Max: " << ms3.max()
              << std::endl;
    return 0;
}