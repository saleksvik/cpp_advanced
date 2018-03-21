#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <algorithm>
#include <fstream>

#include "ip_filter_li.h"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

int main(int argc, char const *argv[])
{
    try
    {
#ifndef ONLINE_JUDGE
        std::fstream ifs("./ip_filter.tsv", std::ifstream::in);
        if(!ifs.is_open())
        {
            std::cout << "File not opened" << "\n";
            return -1;
        }
#endif
        std::vector<std::vector<std::string> > ip_pool;

        //for(std::string line; std::getline(std::cin, line);)
        for(std::string line; std::getline(ifs, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
        reversed_sort(ip_pool);

        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }

        auto filter = [&ip_pool](auto first)
            {
                decltype(ip_pool) ip_filt;
                for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
                    if(std::stoi((*ip)[0]) == first)
                        ip_filt.push_back(*ip);
                return ip_filt;
            };

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        auto ip_filt = filter(1);

        for(auto ip = ip_filt.cbegin(); ip != ip_filt.cend(); ++ip) {
            for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            std::cout << "\n";
        };

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        auto filter_any = [&ip_pool](auto any)
        {
            decltype(ip_pool) ip_filt;
            for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
                 if(std::stoi((*ip)[0]) == any || std::stoi((*ip)[1]) == any || std::stoi((*ip)[2]) == any || std::stoi((*ip)[3])== any)
                    ip_filt.push_back(*ip);
            return ip_filt;
        };

        // TODO filter by any byte and output
        ip_filt = filter_any(46);

        for(auto ip = ip_filt.cbegin(); ip != ip_filt.cend(); ++ip) {
            for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            std::cout << "\n";
        };

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
