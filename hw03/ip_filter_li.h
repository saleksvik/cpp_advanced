//
// Created by User on 16.03.2018.
//

#ifndef HW03_IP_FILTER_LIB_H
#define HW03_IP_FILTER_LIB_H

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <type_traits>

std::vector<std::string> split(const std::string &str, char d);

void reversed_sort(std::vector<std::vector<std::string>>& ip_pool);


auto filter(std::vector<std::vector<std::string>>& ip_pool, int ip1)-> std::remove_reference<decltype(ip_pool)>::type;
auto filter(std::vector<std::vector<std::string>>& ip_pool, int ip1, int ip2)->std::remove_reference<decltype(ip_pool)>::type;
auto filter_any(std::vector<std::vector<std::string>>& ip_pool, int ip1)->std::remove_reference<decltype(ip_pool)>::type;

void print_ips_vector(const std::vector<std::vector<std::string>> &ip_pool);

#endif //HW03_IP_FILTER_LIB_H
