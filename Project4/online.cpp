#include <algorithm>
#include <iostream>
#include <iterator>
 
// Radix sort comparator for 32-bit two's complement integers
class radix_test
{
    const int bit; // bit position [0..31] to examine
public:
    radix_test(int offset) : bit(offset) {} // constructor
 
    bool operator()(int value) const // function call operator
    {
        if (bit == 31) // sign bit
            return value < 0; // negative int to left partition
        else
            return !(value & (1 << bit)); // 0 bit to left partition
    }
};
 
// Most significant digit radix sort (recursive)
void msd_radix_sort(int *first, int *last, int msb = 31)
{
    if (first != last && msb >= 0)
    {
        int *mid = std::partition(first, last, radix_test(msb));
        msb--; // decrement most-significant-bit
        msd_radix_sort(first, mid, msb); // sort left partition
        msd_radix_sort(mid, last, msb); // sort right partition
    }
}
// test radix_sort
int main()
{
    int data[] = { 170, 45, 75, -90, -802, 24, 2, 66, 1, 2, 4, 1234, 64, 325, 100};
    msd_radix_sort(data, data + 8);
    std::copy(data, data + 8, std::ostream_iterator<int>(std::cout, " "));
    return 0;
}