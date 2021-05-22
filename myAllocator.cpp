#include <iostream>
#include "pretty.h"

#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>

#define MAX_POOL_SIZE 1000

/*
template <class T, class U>
constexpr bool operator== (const my_allocator<T>&, const my_allocator<U>&) noexcept {
	return false;
}

template <class T, class U>
constexpr bool operator!= (const my_allocator<T>&, const my_allocator<U>&) noexcept {
	return false;
}
*/


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
    myContainer()
    {
        curSize = 0;
        curAllocatedSize = 0;
    }

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
    void iterate()
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


int main()
{

    //auto v = std::vector<int, myAllocator<int>>{};
    auto v = myContainer<int, myAllocator<int>>{};
    //auto v = myContainer<int, std::allocator<int>>{};

    for (int i = 0; i < 7; ++i) {
        std::cout << "vector size = " << v.size() << std::endl;
        v.push_back(i + 1);
        v.iterate();

        // output vector now
        /*
        std::cout << "vector output" << std::endl;
        for (int i = 0; i < v.size(); ++i) {
            std::cout << v[i] << std::endl;
        }
        std::cout << "vector output end" << std::endl;
        */
    }

/*

    auto m = std::map<
        int,
        int,
        std::less<int>,
        myAllocator<
            std::pair<int, int>
        >
    >{};
    m[0] = 1;
    for (int i = 1; i < 10; ++i)
    {
        m[i] = m[i - 1] * i;
        std::cout << m[i] << std::endl;
    }


    /*
    auto m = std::map<int, int>{};
    m[0] = 1;
    for (int i = 1; i < 10; ++i)
    {
        m[i] = m[i - 1] * i;
        std::cout << m[i] << std::endl;
    }
    */
    return 0;
}
