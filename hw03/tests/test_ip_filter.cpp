//
// Created by User on 15.03.2018.
//

#include "../ip_filter_li.h"
#include <random>
#include <chrono>
#include <fstream>

#define BOOST_TEST_MODULE test_ip_filter

#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(test_suite_ip_filter)

boost::test_tools::predicate_result validate_ip_list_size(ip_list<ip_t>& ip_pool)
{
    for (auto ipv : ip_pool)
    {
        if(ipv.size() != 4)
            return false;
    }
    return true;
}

boost::test_tools::predicate_result validate_ip_list_values(ip_list<ip_t>& ip_pool)
{
    for (auto ipv : ip_pool)
    {
        for(auto ip : ipv)
        {
            if(ip < 0)
                return false;
            if(ip > 255)
                return false;
        };
    }
    return true;
}

struct Fixture
{
    Fixture()
    {
        //reversed_sort
        test_ip_pool.push_back(ip_t{222, 42, 146, 225});
        test_ip_pool.push_back(ip_t{222, 82, 198, 61});
        test_ip_pool.push_back(ip_t{222, 130, 177, 64});
        test_ip_pool.push_back(ip_t{222, 173, 235, 246});
        //filter_1
        test_ip_pool.push_back(ip_t{1, 231, 69, 33});
        test_ip_pool.push_back(ip_t{1, 87, 203, 225});
        test_ip_pool.push_back(ip_t{1, 70, 44, 170});
        test_ip_pool.push_back(ip_t{1, 29, 168, 152});
        test_ip_pool.push_back(ip_t{1, 1, 234, 8});
        //filter_2
        test_ip_pool.push_back(ip_t{46, 70, 225, 39});
        test_ip_pool.push_back(ip_t{46, 70, 147, 26});
        test_ip_pool.push_back(ip_t{46, 70, 113, 73});
        test_ip_pool.push_back(ip_t{46, 70, 29, 76});
        //filter_any
        test_ip_pool.push_back(ip_t{185, 46, 85, 78});
        test_ip_pool.push_back(ip_t{68, 46, 218, 208});
        test_ip_pool.push_back(ip_t{46, 251, 197, 23});
        test_ip_pool.push_back(ip_t{39, 46, 86, 85});
        test_ip_pool.push_back(ip_t{5, 189, 203, 46});

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (test_ip_pool.begin(), test_ip_pool.end(), std::default_random_engine(seed));

    }

    ~Fixture()
    {

    }

    // Тестовый объект
    ip_list <ip_t> test_ip_pool;
};

BOOST_FIXTURE_TEST_CASE(test_input1, Fixture)
{

    ip_list<ip_t> ip_pool;

    std::ifstream filein("tst_ip_filter.tsv");
    for(std::string line; std::getline(filein, line);)
    //for(std::string line; std::getline(std::cin, line);)
    {
        auto v = split(line, '\t');
        auto iv_s = split(v.at(0), '.');
        ip_t  iv_t;
        std::transform(std::begin(iv_s), std::end(iv_s), std::back_inserter(iv_t), [](std::string s){return std::stoi(s);});
        ip_pool.push_back(iv_t);
    };

    BOOST_CHECK(validate_ip_list_size(ip_pool));
    BOOST_CHECK(validate_ip_list_values(ip_pool));
}

BOOST_FIXTURE_TEST_CASE(test_reversed_sort, Fixture)
{

    reversed_sort(test_ip_pool);

    BOOST_CHECK(test_ip_pool[0] == (ip_t{222, 173, 235, 246}));
    BOOST_CHECK(test_ip_pool[1] == (ip_t{222, 130, 177, 64}));
    BOOST_CHECK(test_ip_pool[2] == (ip_t{222, 82, 198, 61}));
    BOOST_CHECK(test_ip_pool[3] == (ip_t{222, 42, 146, 225}));
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

    BOOST_CHECK(ip_filt1[0] == (ip_t{1, 231, 69, 33}));
    BOOST_CHECK(ip_filt1[1] == (ip_t{1, 87, 203, 225}));
    BOOST_CHECK(ip_filt1[2] == (ip_t{1, 70, 44, 170}));
    BOOST_CHECK(ip_filt1[3] == (ip_t{1, 29, 168, 152}));
    BOOST_CHECK(ip_filt1[4] == (ip_t{1, 1, 234, 8}));
}

BOOST_FIXTURE_TEST_CASE(test_filter2, Fixture)
{
    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76

    reversed_sort(test_ip_pool);

    auto ip_filt2 = filter(test_ip_pool, 46, 70);

    BOOST_CHECK(ip_filt2[0] == (ip_t{46, 70, 225, 39}));
    BOOST_CHECK(ip_filt2[1] == (ip_t{46, 70, 147, 26}));
    BOOST_CHECK(ip_filt2[2] == (ip_t{46, 70, 113, 73}));
    BOOST_CHECK(ip_filt2[3] == (ip_t{46, 70, 29, 76}));
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

    BOOST_CHECK(ip_filt3[0] == (ip_t{185, 46, 85, 78}));
    BOOST_CHECK(ip_filt3[1] == (ip_t{68, 46, 218, 208}));
    BOOST_CHECK(ip_filt3[2] == (ip_t{46, 251, 197, 23}));
    BOOST_CHECK(ip_filt3[3] == (ip_t{46, 70, 225, 39}));
    BOOST_CHECK(ip_filt3[4] == (ip_t{46, 70, 147, 26}));
    BOOST_CHECK(ip_filt3[5] == (ip_t{46, 70, 113, 73}));
    BOOST_CHECK(ip_filt3[6] == (ip_t{46, 70, 29, 76}));
    BOOST_CHECK(ip_filt3[7] == (ip_t{39, 46, 86, 85}));
    BOOST_CHECK(ip_filt3[8] == (ip_t{5, 189, 203, 46}));
}

BOOST_AUTO_TEST_SUITE_END()
