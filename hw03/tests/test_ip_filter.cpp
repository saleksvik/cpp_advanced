//
// Created by User on 15.03.2018.
//

#include "../ip_filter_li.h"
#include <random>
#include <chrono>

#define BOOST_TEST_MODULE test_ip_filter

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_ip_filter)

struct Fixture
{
    Fixture()
    {
        //reversed_sort
        test_ip_pool.push_back(std::vector<std::string>{"222", "42", "146", "225"});
        test_ip_pool.push_back(std::vector<std::string>{"222", "82", "198", "61"});
        test_ip_pool.push_back(std::vector<std::string>{"222", "130", "177", "64"});
        test_ip_pool.push_back(std::vector<std::string>{"222", "173", "235", "246"});
        //filter_1
        test_ip_pool.push_back(std::vector<std::string>{"1", "231", "69", "33"});
        test_ip_pool.push_back(std::vector<std::string>{"1", "87", "203", "225"});
        test_ip_pool.push_back(std::vector<std::string>{"1", "70", "44", "170"});
        test_ip_pool.push_back(std::vector<std::string>{"1", "29", "168", "152"});
        test_ip_pool.push_back(std::vector<std::string>{"1", "1", "234", "8"});
        //filter_2
        test_ip_pool.push_back(std::vector<std::string>{"46", "70", "225", "39"});
        test_ip_pool.push_back(std::vector<std::string>{"46", "70", "147", "26"});
        test_ip_pool.push_back(std::vector<std::string>{"46", "70", "113", "73"});
        test_ip_pool.push_back(std::vector<std::string>{"46", "70", "29", "76"});
        //filter_any
        test_ip_pool.push_back(std::vector<std::string>{"185", "46", "85", "78"});
        test_ip_pool.push_back(std::vector<std::string>{"68", "46", "218", "208"});
        test_ip_pool.push_back(std::vector<std::string>{"46", "251", "197", "23"});
        test_ip_pool.push_back(std::vector<std::string>{"39", "46", "86", "85"});
        test_ip_pool.push_back(std::vector<std::string>{"5", "189", "203", "46"});

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (test_ip_pool.begin(), test_ip_pool.end(), std::default_random_engine(seed));
    }

    ~Fixture()
    {

    }

    // Тестовый объект
    std::vector<std::vector<std::string>> test_ip_pool;
};

BOOST_FIXTURE_TEST_CASE(test_reversed_sort, Fixture)
{

    reversed_sort(test_ip_pool);

    BOOST_CHECK(test_ip_pool[0] == (std::vector<std::string>{"222", "173", "235", "246"}));
    BOOST_CHECK(test_ip_pool[1] == (std::vector<std::string>{"222", "130", "177", "64"}));
    BOOST_CHECK(test_ip_pool[2] == (std::vector<std::string>{"222", "82", "198", "61"}));
    BOOST_CHECK(test_ip_pool[3] == (std::vector<std::string>{"222", "42", "146", "225"}));
}

BOOST_FIXTURE_TEST_CASE(test_filter1, Fixture)
{
    // 1.231.69.33
    // 1.87.203.225
    // 1.70.44.170
    // 1.29.168.152
    // 1.1.234.8

    reversed_sort(test_ip_pool);

    auto ip_filt1 = filter(test_ip_pool, 1);

    BOOST_CHECK(ip_filt1[0] == (std::vector<std::string>{"1", "231", "69", "33"}));
    BOOST_CHECK(ip_filt1[1] == (std::vector<std::string>{"1", "87", "203", "225"}));
    BOOST_CHECK(ip_filt1[2] == (std::vector<std::string>{"1", "70", "44", "170"}));
    BOOST_CHECK(ip_filt1[3] == (std::vector<std::string>{"1", "29", "168", "152"}));
    BOOST_CHECK(ip_filt1[4] == (std::vector<std::string>{"1", "1", "234", "8"}));
}

BOOST_FIXTURE_TEST_CASE(test_filter2, Fixture)
{
    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76

    reversed_sort(test_ip_pool);

    auto ip_filt2 = filter(test_ip_pool, 46, 70);

    BOOST_CHECK(ip_filt2[0] == (std::vector<std::string>{"46", "70", "225", "39"}));
    BOOST_CHECK(ip_filt2[1] == (std::vector<std::string>{"46", "70", "147", "26"}));
    BOOST_CHECK(ip_filt2[2] == (std::vector<std::string>{"46", "70", "113", "73"}));
    BOOST_CHECK(ip_filt2[3] == (std::vector<std::string>{"46", "70", "29", "76"}));
}

BOOST_FIXTURE_TEST_CASE(test_filter_any, Fixture)
{
    // 185.46.85.78
    // 68.46.218.208
    // 46.251.197.23
    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76
    // 39.46.86.85
    // 5.189.203.46

    reversed_sort(test_ip_pool);

    auto ip_filt3 = filter_any(test_ip_pool, 46);

    BOOST_CHECK(ip_filt3[0] == (std::vector<std::string>{"185", "46", "85", "78"}));
    BOOST_CHECK(ip_filt3[1] == (std::vector<std::string>{"68", "46", "218", "208"}));
    BOOST_CHECK(ip_filt3[2] == (std::vector<std::string>{"46", "251", "197", "23"}));
    BOOST_CHECK(ip_filt3[3] == (std::vector<std::string>{"46", "70", "225", "39"}));
    BOOST_CHECK(ip_filt3[4] == (std::vector<std::string>{"46", "70", "147", "26"}));
    BOOST_CHECK(ip_filt3[5] == (std::vector<std::string>{"46", "70", "113", "73"}));
    BOOST_CHECK(ip_filt3[6] == (std::vector<std::string>{"46", "70", "29", "76"}));
    BOOST_CHECK(ip_filt3[7] == (std::vector<std::string>{"39", "46", "86", "85"}));
    BOOST_CHECK(ip_filt3[8] == (std::vector<std::string>{"5", "189", "203", "46"}));

}

BOOST_AUTO_TEST_SUITE_END()
