//
// Created by User on 15.03.2018.
//

#include "../ip_filter_li.h"
#include <random>
#include <chrono>
#include <fstream>

#define BOOST_TEST_MODULE test_ip_filter

#include <boost/test/unit_test.hpp>

std::ostream& operator<< (std::ostream& ostr, ip_t const& ip_part)
{
    for(auto it = std::begin(ip_part); it != std::end(ip_part); ++it)
    {
        if (it != std::begin(ip_part))
        {
            ostr << ".";
        }
        ostr << *it;
    }
    ostr << std::endl;
    return ostr;
}

namespace boost {
    namespace test_tools {
        //namespace tt_detail{
            template<>
            struct print_log_value<ip_t> {
                void operator()( std::ostream& os, ip_t const& ts)
                {
                    ::operator<<(os,ts);
                }
             };
        //}
    }
}

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(test_suite_ip_filter)

tt::predicate_result validate_ip_list_size(ip_list<ip_t>& ip_pool)
{
    for (auto ipv : ip_pool)
    {
        if(ipv.size() != 4)
            return false;
    }
    return true;
}

tt::predicate_result validate_ip_list_values(ip_list<ip_t>& ip_pool)
{
    for (auto ipv : ip_pool)
    {
        for(auto ip_octet : ipv)
        {
            if(ip_octet < 0)
                return false;
            if(ip_octet > 255)
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
    ip_list <ip_t> test_input_ip_pool;
};

BOOST_FIXTURE_TEST_CASE(test_input1, Fixture)
{
    std::ifstream filein("tst_ip_filter.tsv");
    for(std::string line; std::getline(filein, line);){
        auto v = split(line, '\t');
        auto iv_s = split(v.at(0), '.');
        ip_t  iv_t;
        std::transform(std::begin(iv_s), std::end(iv_s), std::back_inserter(iv_t), [](std::string s){return std::stoi(s);});
        test_input_ip_pool.push_back(iv_t);
    };

    BOOST_CHECK(validate_ip_list_size(test_ip_pool));
    BOOST_CHECK(validate_ip_list_values(test_ip_pool));
}

BOOST_FIXTURE_TEST_CASE(test_reversed_sort, Fixture)
{

    reversed_sort(test_ip_pool);

    ip_list<ip_t>  ip_test1 = {{222, 173, 235, 246},
                               {222, 130, 177, 64},
                               {222, 82, 198, 61},
                               {222, 42, 146, 225}};
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(test_ip_pool), std::begin(test_ip_pool)+4, std::begin(ip_test1), std::end(ip_test1));
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

    ip_list<ip_t>  ip_test2 = {{1, 231, 69, 33},
                                {1, 87, 203, 225},
                                {1, 70, 44, 170},
                                {1, 29, 168, 152},
                                {1, 1, 234, 8}};
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(ip_filt1), std::begin(ip_filt1)+5, std::begin(ip_test2), std::end(ip_test2));
}

BOOST_FIXTURE_TEST_CASE(test_filter2, Fixture)
{
    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76

    reversed_sort(test_ip_pool);

    auto ip_filt2 = filter(test_ip_pool, 46, 70);

    ip_list<ip_t>  ip_test3 = {{46, 70, 225, 39},
                               {46, 70, 147, 26},
                               {46, 70, 113, 73},
                               {46, 70, 29, 76}};
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(ip_filt2), std::begin(ip_filt2)+4, std::begin(ip_test3), std::end(ip_test3));
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

    ip_list<ip_t>  ip_test4 = {{185, 46, 85, 78},
                               {68, 46, 218, 208},
                               {46, 251, 197, 23},
                               {46, 70, 225, 39},
                               {46, 70, 147, 26},
                               {46, 70, 113, 73},
                               {46, 70, 29, 76},
                               {39, 46, 86, 85},
                               {5, 189, 203, 46}};
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(ip_filt3), std::begin(ip_filt3)+9, std::begin(ip_test4), std::end(ip_test4));
}

BOOST_AUTO_TEST_SUITE_END()
