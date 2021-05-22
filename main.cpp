#pragma once
#include <iostream>
#include "pretty.h"
#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>

#include "myAllocator.h"
#include "myContainer.h"

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


