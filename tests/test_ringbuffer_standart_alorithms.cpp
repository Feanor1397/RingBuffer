#include <buffers.hpp>
#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    RingBuffer<int> buf(5);
    for(int i = 0; i < 5; i++)
        buf.push_back(i);

    cout << "Initial fill from 0 to 4" << endl;
    for(unsigned int i = 0; i < 5; i++)
        cout << buf[i] << " ";
    cout << endl;

    std::reverse(buf.begin(), buf.end());
    cout << "After reverse() from 0 to 4" << endl;
    for(unsigned int i = 0; i < 5; i++)
        cout << buf[i] << " ";
    cout << endl;
    bool rev = buf[0] == 4 && buf[4] == 0;

    std::sort(buf.begin(), buf.end());
    cout << "After sort() from 0 to 4" << endl;
    for(unsigned int i = 0; i < 5; i++)
        cout << buf[i] << " ";
    cout << endl;

    bool srt = buf[0] == 0 && buf[4] == 4;

    return rev && srt ? 0 : -1;
}
