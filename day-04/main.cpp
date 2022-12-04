#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>

/*
 * Priority Queue
 * auto cmp = [](const Foo &left, const Foo &right) { return left.b > right.b; };
 * std::priority_queue<Foo, std::vector<Foo>, decltype(cmp)> pq(cmp);
 */

int main() {
    auto ifs = std::ifstream();
    ifs.open("input.txt");

    auto line = std::string();

    std::string s_start_1, s_end_1, s_start_2, s_end_2;
    int64_t start_1, end_1, start_2, end_2;
    int64_t res = 0;

    while (std::getline(ifs, line)) {
        auto ss = std::istringstream(line);

        std::getline(ss, s_start_1, '-');
        std::getline(ss, s_end_1, ',');
        std::getline(ss, s_start_2, '-');
        std::getline(ss, s_end_2);

        start_1 = std::stoll(s_start_1);
        end_1 = std::stoll(s_end_1);
        start_2 = std::stoll(s_start_2);
        end_2 = std::stoll(s_end_2);

        if ((start_2 >= start_1 && end_2 <= end_1) || (start_1 >= start_2 && end_1 <= end_2)) {
            ++res;
        }
    }

    std::cout << res << '\n';
    return 0;
}
