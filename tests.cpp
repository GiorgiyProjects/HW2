#define BOOST_TEST_MODULE tests
//#include <boost/test/unit_test.hpp>
#include "myAllocator.hpp"
#include "myContainer.hpp"
#include "mapHelper.hpp"

#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(testAllocator1)
{
    auto m = std::map<int, int>{};
    mapHelper manager;
    manager.fillMap(m, 10);
    BOOST_CHECK_EQUAL(manager.printMap(m), "0 1;1 1;2 2;3 6;4 24;5 120;6 720;7 5040;8 40320;9 362880;\n");
}

BOOST_AUTO_TEST_CASE(testAllocator2)
{
    auto m = std::map<
            int,
            int,
            std::less<int>,
            myAllocator<
                    std::pair<int, int>
            >
    >{};
    mapHelper manager;
    manager.fillMap(m, 10);
    BOOST_CHECK_EQUAL(manager.printMap(m), "0 1;1 1;2 2;3 6;4 24;5 120;6 720;7 5040;8 40320;9 362880;\n");
}

BOOST_AUTO_TEST_CASE(testContainer1)
{
    auto v = myContainer<int, std::allocator<int>>{};
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i);
    }
    BOOST_CHECK_EQUAL(v.print(), "0 1 2 3 4 5 6 7 8 9 \n");
}

BOOST_AUTO_TEST_CASE(testContainer2)
{
    auto v = myContainer<int, myAllocator<int>>{};
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i);
    }
    BOOST_CHECK_EQUAL(v.print(), "0 1 2 3 4 5 6 7 8 9 \n");
}