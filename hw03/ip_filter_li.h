//
// Created by User on 16.03.2018.
//

#ifndef HW03_IP_FILTER_LIB_H
#define HW03_IP_FILTER_LIB_H

#include <iostream>
#include <vector>
#include <algorithm>

int version();

std::vector<std::string> split(const std::string &str, char d);

void reversed_sort(std::vector<std::vector<std::string>>& ip_pool);

#endif //HW03_IP_FILTER_LIB_H
