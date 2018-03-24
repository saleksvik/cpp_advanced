//
// Created by User on 16.03.2018.
//

#include "ip_filter_li.h"

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

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
    return  lhs.length() == rhs.length() ? !(lhs <= rhs) : lhs.length() > rhs.length();
}

bool operator>(const std::vector<std::string> &lvs, const std::vector<std::string> &rvs)
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

void reversed_sort(std::vector<std::vector<std::string>>& ip_pool)
{
    std::sort(ip_pool.begin(), ip_pool.end(), greater<std::vector<std::string>>());
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
    if(op_and_or)
        return ip[index] == std::to_string(t) && ippredicate(ip, ++index, true, args...);
    else
        return ip[index] == std::to_string(t) || ippredicate(ip, ++index, false, args...);
}

//template <typename T, typename ...Args>
//auto filter(T& ip_pool, Args...args)-> typename std::remove_reference<decltype(ip_pool)>::type
//{
//    typename std::remove_reference<decltype(ip_pool)>::type ip_filt;
//    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_filt), [args...](auto vip){return ippredicate(vip, 0, args...);});
//    return ip_filt;
//}

auto filter(std::vector<std::vector<std::string>>& ip_pool, int ip1)-> std::remove_reference<decltype(ip_pool)>::type
{
    std::remove_reference<decltype(ip_pool)>::type ip_filt;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_filt), [ip1](auto vip){return ippredicate(vip, 0, true, ip1);});
    return ip_filt;
}

auto filter(std::vector<std::vector<std::string>>& ip_pool, int ip1, int ip2)-> std::remove_reference<decltype(ip_pool)>::type
{
    std::remove_reference<decltype(ip_pool)>::type ip_filt;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_filt), [ip1, ip2](auto vip){return ippredicate(vip, 0, true, ip1, ip2);});
    return ip_filt;
}

auto filter_any(std::vector<std::vector<std::string>>& ip_pool, int ip1)-> std::remove_reference<decltype(ip_pool)>::type
{
    std::remove_reference<decltype(ip_pool)>::type ip_filt;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_filt), [ip1](auto vip){return ippredicate(vip, 0, false, ip1, ip1, ip1, ip1);});
    return ip_filt;
}

//auto filter_any = [&ip_pool](auto any)
//{
//    decltype(ip_pool) ip_filt;
//    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
//        if(std::stoi((*ip)[0]) == any || std::stoi((*ip)[1]) == any || std::stoi((*ip)[2]) == any || std::stoi((*ip)[3])== any)
//            ip_filt.push_back(*ip);
//    return ip_filt;
//};
