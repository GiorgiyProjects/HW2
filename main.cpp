#include <iostream>
#include "pretty.h"
#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>

#include "myAllocator.hpp"
#include "myContainer.hpp"

template<typename T>
void fillMap (T& m, const int size)
{
    m[0] = 1;
    for (int i = 1; i < 10; ++i)
    {
        m[i] = m[i - 1] * i;
    }
}

template<typename T>
void printMap(T m)
{
    std::for_each(m.begin(),
                  m.end(),
                  [](const auto &p) {
                      std::cout << p.first << " " << p.second << std::endl;
                  });
}

int main()
{
    static const int n = 10;

    auto m1 = std::map<int, int>{};
    fillMap(m1, n);
    printMap(m1);

    auto m2 = std::map<
            int,
            int,
            std::less<int>,
            myAllocator<
                    std::pair<int, int>
            >
    >{};
    fillMap(m2, n);
    printMap(m2);

    auto v1 = myContainer<int, std::allocator<int>>{};
    auto v2 = myContainer<int, myAllocator<int>>{};

    for (int i = 0; i < n; ++i)
    {
        v1.push_back(i);
        v2.push_back(i);
    }
    v1.print();
    v2.print();

    return 0;
}


