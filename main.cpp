#include <iostream>
#include "pretty.h"
#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>
#include <string>

#include "myAllocator.hpp"
#include "myContainer.hpp"
#include "mapHelper.hpp"

int main()
{
    static const int n = 10;
    mapHelper manager;

    auto m1 = std::map<int, int>{};
    manager.fillMap(m1, n);
    std::cout << manager.printMap(m1);

    auto m2 = std::map<
            int,
            int,
            std::less<int>,
            myAllocator<
                    std::pair<int, int>
            >
    >{};
    manager.fillMap(m2, n);
    std::cout << manager.printMap(m2);

    auto v1 = myContainer<int, std::allocator<int>>{};
    auto v2 = myContainer<int, myAllocator<int>>{};

    for (int i = 0; i < n; ++i)
    {
        v1.push_back(i);
        v2.push_back(i);
    }
    std::cout << v1.print();
    std::cout << v2.print();

    return 0;
}


