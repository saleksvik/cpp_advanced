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

template<typename T>
using ip_list = std::vector<T>;

using ip_t = std::vector<int>;
using ip_s = std::vector<std::string>;

void reversed_sort(ip_list<ip_t>& ip_pool);

ip_list<ip_t> filter(const ip_list<ip_t>& ip_pool, int ip1);
ip_list<ip_t> filter(const ip_list<ip_t>& ip_pool, int ip1, int ip2);
ip_list<ip_t> filter_any(const ip_list<ip_t>& ip_pool, int ip1);

template <typename T>
std::ostream& operator<< (std::ostream& ostr, const ip_list<T>& ip_pool);

void print_ips_vector(const ip_list<ip_t>& ip_pool);

ip_s split(const std::string &str, char d);

#endif //HW03_IP_FILTER_LIB_H
