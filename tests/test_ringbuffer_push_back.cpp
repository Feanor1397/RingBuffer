#include <ring_buffer.hpp>
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    RingBuffer<int> buf(5);
    // fill buffer first time
    for(int i = 0; i < 5; i++)
        buf.push_back(i);

    cout << "Initial fill from 0 to 4" << endl;
    for(unsigned int i = 0; i < 5; i++)
        cout << buf[i] << " ";
    cout << endl;

    bool first = buf[0] == 0;
    bool last = buf[4] == 4;

    bool before = first && last;

    for(int i = 0; i < 5; i++)
        buf.push_back(i + 5);

    cout << "After refill from 0 to 4" << endl;
    for(unsigned int i = 0; i < 5; i++)
        cout << buf[i] << " ";
    cout << endl;

    first = buf[0] == 5;
    last = buf[4] == 9;

    bool after = first && last;

    return before && after ? 0 : -1;
}
