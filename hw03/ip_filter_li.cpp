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
    return std::stoi(lhs) > std::stoi(rhs);
}

struct greater
{
    template<typename T>
     bool operator()(const T &a, const T &b) const { return a > b; }
};

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

void reversed_sort(std::vector<std::vector<std::string>>& ip_pool)
{
    std::sort(ip_pool.begin(), ip_pool.end(), greater());
}
