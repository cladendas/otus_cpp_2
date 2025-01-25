#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <ranges>

template<typename T>
void print_ip(T ip_pool) {
    for (auto ip: ip_pool) {
        for (auto oktet: ip) {
            if (*(ip.end() - 1) != oktet) {
                std::cout << oktet << '.';
            } else {
               std::cout << oktet; 
            }
        }
        std::cout << std::endl;
    }
}

template<typename T>
void filter(T ip_pool, int oktet) {
    auto ip_view_filter = ip_pool | std::ranges::views::filter([](auto ip) {
        return std::stoi(ip[0]) == 1;
    });
    print_ip(ip_view_filter);
}

template<typename T>
void filter(T ip_pool, int oktet_0, int oktet_1) {
    auto ip_view_filter = ip_pool | std::ranges::views::filter([oktet_0, oktet_1](auto ip) {
        return (std::stoi(ip[0]) == oktet_0 && std::stoi(ip[1]) == oktet_1);
    });
    print_ip(ip_view_filter);
}

template<typename T>
void filter_any(T ip_pool, int oktet) {
    auto ip_view_filter = ip_pool | std::ranges::views::filter([oktet](auto ip) {
        for (auto tmp: ip) {
            if (std::stoi(tmp) == oktet) {
                return true;
            }
        } 
        return false;
    });
    print_ip(ip_view_filter);
}

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
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

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), [](auto ip_0, auto ip_1){

            for (size_t i = 0; i < ip_0.size(); i++) {
                if (std::stoi(ip_0[i]) != std::stoi(ip_1[i])) {
                    return std::stoi(ip_0[i]) > std::stoi(ip_1[i]);
                }
            }

            return false;
        });

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8
        print_ip(ip_pool);


        // TODO filter by first byte and output
        // ip = filter(1)

        filter(ip_pool, 1);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        filter(ip_pool, 46, 70);

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        filter_any(ip_pool, 46);

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
