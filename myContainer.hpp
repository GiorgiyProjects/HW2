#include <iostream>
#include "pretty.h"
#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>

//template <typename T, template<typename Alloc<typename T> >
template<typename T, typename Alloc = std::allocator<T> >
class myContainer
{
private:
    T* arr;
    Alloc myContainerAllocator;
    size_t curSize;
    size_t curAllocatedSize;

public:
    myContainer() : curSize(0), curAllocatedSize(0)
    {}

    void push_back(T value)
    {
        if (curSize == curAllocatedSize)
        {
            T* oldArr = arr;
            // we allocate new bigger memory chunk
            curAllocatedSize = (curAllocatedSize == 0) ? 1 : curAllocatedSize * 2;
            arr = myContainerAllocator.allocate(curAllocatedSize);
            // we copy values from old place in memory to new place and add new value that we are trying to push to container
            for (int i = 0; i < curSize; i++)
            {
                myContainerAllocator.construct((arr + i), oldArr[i]);
            }
            myContainerAllocator.construct((arr + curSize), value);

            // now we destroy old values
            for (int i = 0; i < curSize; i++)
            {
                myContainerAllocator.destroy((oldArr + i));
            }
            if (curSize > 0)
            {
                myContainerAllocator.deallocate(oldArr, curSize);
            }
            curSize++;
        } else
        {
            myContainerAllocator.construct((arr + curSize), value); // we need to construct new value to be pushed at the position of curSize
            curSize++;
        }
    }

    void print()
    {
        for (int i = 0; i < curSize; i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    int size()
    {
        return curSize;
    }
};