/*
Подсчитать кол-во единичных бит в входном числе , стоящих на четных позициях.
Позиции битов нумеруются с 0.

Необходимо использование битовых операций.
Использование арифметических операций запрещено.
*/

#include <iostream>

using namespace std;
    
void inc(unsigned& n) {
    unsigned mask;
    for (mask = 1; (n & mask) != 0; mask <<= 1)
        n &= ~mask;
     
    n |= mask;
}

int main()
{
    unsigned n, count = 0; 
    cin >> n;
    
    while(n) {
        if (n & 1)
            inc(count);
        n >>= 2;
    } 
    
    cout << count;
    return 0;
}
