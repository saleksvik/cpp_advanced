//
// Created by User on 16.03.2018.
//

#include "ip_filter_li.h"

void reversed_sort(ip_list<ip_t >& ip_pool)
{
    std::sort(std::begin(ip_pool), std::end(ip_pool), std::greater<ip_t>());
}

bool ippredicate(ip_t& ip, bool op_and_or, int t0 = -1, int t1 = -1, int t2 = -1, int t3 = -1)
{
    if(op_and_or)
        return (ip[0] == t0 || t0 == -1) && (ip[1] == t1 || t1 == -1)
                && (ip[2] == t2 || t2 == -1) && (ip[3] == t3 || t3 == -1);
    else
        return (ip[0] == t0 || t0 == -1) || (ip[1] == t1 || t1 == -1)
               || (ip[2] == t2 || t2 == -1) || (ip[3] == t3 || t3 == -1);
}

ip_list<ip_t> filter(const ip_list<ip_t>& ip_pool, int ip1)
{
    ip_list<ip_t> ip_filt;
    std::copy_if(std::begin(ip_pool), std::end(ip_pool), std::back_inserter(ip_filt), [ip1](auto vip){return ippredicate(vip, true, ip1);});
    return ip_filt;
}

ip_list<ip_t> filter(const ip_list<ip_t>& ip_pool, int ip1, int ip2)
{
    ip_list<ip_t> ip_filt;
    std::copy_if(std::begin(ip_pool), std::end(ip_pool), std::back_inserter(ip_filt), [ip1, ip2](auto vip){return ippredicate(vip, true, ip1, ip2);});
    return ip_filt;
}

ip_list<ip_t> filter_any(const ip_list<ip_t>& ip_pool, int ip1)
{
    ip_list<ip_t> ip_filt;
    std::copy_if(std::begin(ip_pool), std::end(ip_pool), std::back_inserter(ip_filt), [ip1](auto vip){return ippredicate(vip, false, ip1, ip1, ip1, ip1);});
    return ip_filt;
}

template <typename T>
std::ostream& operator<< (std::ostream& ostr, ip_list<T> const& ip_pool)
{
    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                ostr << ".";
            }
            ostr << *ip_part;
        }
        ostr << std::endl;
    }
    return ostr;
}

void print_ips_vector(const ip_list<ip_t>& ip_pool)
{
    std::cout << ip_pool;
}

ip_s split(const std::string &str, char d)
{
    ip_s r;
    r.reserve(4);
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
