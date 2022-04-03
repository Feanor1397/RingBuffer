# C++ STL compatible Ring buffer

C++ STL compatible Ring buffer, designed for workflow, that requires always keeping N last objects of constant flow of data.
Can be used like regular STL containers, should support all STL algorithms.

Buffer built around array of specific size, memory allocated at creation of container.
Support indexed access. Index 0 is oldest data, index max_size-1 is newest.
Data can be accessed with `front()` and `back()` methods, wich return oldest and newest elements.
Third way is to use iteratos.

Data can be added with `push_back()` and deleted with `pop_back()`.

`size()` is current number of elements in buffer.
`max_size()` is maximum elements, that buffer can hold.

To use buffer in your code include header file
and create buffer with constructor

```
#include "ring_buffer.hpp"

RingBuffer<int> buf(5);
for(int i = 0; i < 5; i++)
        buf.push_back(i);
```
