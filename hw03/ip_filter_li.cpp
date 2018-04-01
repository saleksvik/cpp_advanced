//
// Created by User on 16.03.2018.
//

#include "ip_filter_li.h"

ip_t split(const std::string &str, char d)
{
    ip_t r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

bool operator>(const std::string& lhs, const std::string& rhs)
{
    return  std::stoi(lhs) > std::stoi(rhs);
}

bool operator>(const ip_t &lvs, const ip_t &rvs)
{
    for(int i = 0; i < lvs.size(); ++i)
    {
        if(lvs[i] == rvs[i])
            continue;
        return lvs[i] > rvs[i];
    };
    return false;
}

template<typename T>
struct greater
{
    bool operator()(const T& a, const T& b) const { return a > b; }
};

void reversed_sort(ip_list<ip_t >& ip_pool)
{
    std::sort(ip_pool.begin(), ip_pool.end(), greater<ip_t>());
}

template <typename T1>
bool ippredicate(T1& ip, int index, bool op_and_or)
{
    if(op_and_or)
        return true;
    else
        return false;
}

template <typename T1, typename T2, typename... Args>
bool ippredicate(T1& ip, int index, bool op_and_or, T2 t, Args... args)
{
    auto res = (ip[index] == std::to_string(t));
    if(op_and_or)
        return !res ? false : res && ippredicate(ip, ++index, true, args...);
    else
        return res ? true : res || ippredicate(ip, ++index, false, args...);
}

auto filter(ip_list<ip_t>& ip_pool, int ip1)->ip_list<ip_t>
{
    ip_list<ip_t> ip_filt;
    std::copy_if(std::begin(ip_pool), std::end(ip_pool), std::back_inserter(ip_filt), [ip1](auto vip){return ippredicate(vip, 0, true, ip1);});
    return ip_filt;
}

auto filter(ip_list<ip_t>& ip_pool, int ip1, int ip2)->ip_list<ip_t>
{
    ip_list<ip_t> ip_filt;
    std::copy_if(std::begin(ip_pool), std::end(ip_pool), std::back_inserter(ip_filt), [ip1, ip2](auto vip){return ippredicate(vip, 0, true, ip1, ip2);});
    return ip_filt;
}

auto filter_any(ip_list<ip_t>& ip_pool, int ip1)->ip_list<ip_t>
{
    ip_list<ip_t> ip_filt;
    std::copy_if(std::begin(ip_pool), std::end(ip_pool), std::back_inserter(ip_filt), [ip1](auto vip){return ippredicate(vip, 0, false, ip1, ip1, ip1, ip1);});
    return ip_filt;
}

void print_ips_vector(const ip_list<ip_t>& ip_pool)
{
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
}
