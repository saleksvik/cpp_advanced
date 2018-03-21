//
// Created by User on 15.03.2018.
//

#include "../ip_filter_li.h"

#define BOOST_TEST_MODULE test_ip_filter

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_ip_filter)

struct Fixture
{
    Fixture()
    {

    }

    ~Fixture()
    {

    }

    // Тестовый объект
    std::vector<std::vector<std::string>> test_ip_pool;
};

BOOST_FIXTURE_TEST_CASE(test_reversed_sort, Fixture)
{
    test_ip_pool.push_back(std::vector<std::string>{"222", "42", "146", "225"});
    test_ip_pool.push_back(std::vector<std::string>{"222", "82", "198", "61"});
    test_ip_pool.push_back(std::vector<std::string>{"222", "130", "177", "64"});
    test_ip_pool.push_back(std::vector<std::string>{"222", "173", "235", "246"});

    reversed_sort(test_ip_pool);

    BOOST_CHECK(test_ip_pool[0] == (std::vector<std::string>{"222", "173", "235", "246"}));
    BOOST_CHECK(test_ip_pool[1] == (std::vector<std::string>{"222", "130", "177", "64"}));
    BOOST_CHECK(test_ip_pool[2] == (std::vector<std::string>{"222", "82", "198", "61"}));
    BOOST_CHECK(test_ip_pool[3] == (std::vector<std::string>{"222", "42", "146", "225"}));

    test_ip_pool.clear();
}

BOOST_AUTO_TEST_SUITE_END()
