#include <iostream>
#include "pretty.h"
#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>

template<typename T, const int MAX_POOL_SIZE = 1000>
struct myAllocator {
private:
    bool poolInitialized = false;
    int poolSize = MAX_POOL_SIZE;
    T* memoryPool;
    bool* busyBytes;

public:
    myAllocator() = default;
    ~myAllocator()
    {
        delete[] busyBytes;
        delete[] memoryPool;
    }

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = myAllocator<U>;
    };

    int findFreePiece(int n)
    {
        for (int i = 0; i < (poolSize - n); ++i)
        {
            bool chunk_works = true;
            for (int j = 0; j < n; j++)
            {
                if (busyBytes[i + j])
                {
                    chunk_works = false;
                    break;
                }
            }
            if (chunk_works) return i;
        }
        return (-1);
    }

    T* allocate(std::size_t n)
    {
        if (n == 0)
        {
            return nullptr;
        }

        if (!poolInitialized)
        {
            poolInitialized = true;
            memoryPool = new T[poolSize];
            busyBytes = new bool[poolSize];
            for (int i = 0; i < busyBytes[i]; i++)
            {
                busyBytes[i] = false;
            }
        }

        // we first find continuous part of memory pool of size n, that is not busy
        int emptyChunkStart = findFreePiece(n);
        assert(emptyChunkStart != -1); // could not find the chunk of enough size in memory pool
        for (int i = emptyChunkStart; i < emptyChunkStart + n; i++) busyBytes[i] = true;

        return &memoryPool[emptyChunkStart];
    }

    void deallocate(T* p, std::size_t n)
    {
        if (n == 0)
        {
            return;
        }
        int idx = p - &memoryPool[0];
        if (idx <= 0)
        {
            return;
        }
        for (int i = idx; i < idx + n; i++) busyBytes[i] = false;
    }

    template<typename U, typename ...Args>
    void construct(U* p, Args &&...args)
    {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T* p)
    {
        p->~T();
    }

};