#define MAX_POOL_SIZE 1000

template<typename T>
struct myAllocator {
private:
    bool poolInitialized = false;

    std::vector<T> memoryPool;
    std::vector<bool> busyBytes;

public:
    myAllocator() = default;
    ~myAllocator() = default;

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
        for (int i = 0; i < (busyBytes.size() - n); ++i)
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

        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << "allocate " << n << " bytes" << std::endl;
        if (!poolInitialized)
        {
            //std::cout << "allocating memo" << std::endl;
            poolInitialized = true;
            memoryPool.resize(MAX_POOL_SIZE);
            busyBytes.resize(MAX_POOL_SIZE, false);
        }

        // we first find continuous part of memory pool of size n, that is not busy
        int emptyChunkStart = findFreePiece(n);
        assert(emptyChunkStart != -1); // could not find the chunk of enough size in memory pool
        std::replace (busyBytes.begin() + emptyChunkStart, busyBytes.begin() + emptyChunkStart + n, false, true);

        return &memoryPool[emptyChunkStart];
    }

    void deallocate(T* p, std::size_t n)
    {
        if (n == 0)
        {
            return;
        }
        //std::cout << __PRETTY_FUNCTION__ << std::endl;
        int idx = p - &memoryPool[0];
        std::replace (busyBytes.begin() + idx, busyBytes.begin() + idx + n, true, false);
    }

    template<typename U, typename ...Args>
    void construct(U* p, Args &&...args)
    {
        //std::cout << __PRETTY_FUNCTION__ << std::endl;
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T* p)
    {
        //std::cout << __PRETTY_FUNCTION__ << std::endl;
        //std::cout << *p << std::endl;
        p->~T();
    }

};