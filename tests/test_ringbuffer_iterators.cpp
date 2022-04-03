#include <ring_buffer.hpp>

int main()
{
    RingBuffer<int> buf(5);
    for(int i = 0; i < 5; i++)
        buf.push_back(i);

    int sum = 0;
    // sum should be 0 + 1 + 2 + 3 + 4 = 10
    for(int& i : buf)
        sum += i;

    return sum == 10 ? 0 : -1;
}
