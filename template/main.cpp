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
    while (std::getline(ifs, line)) {
        auto ss = std::istringstream(line);

//        auto token = std::string();
//        std::getline(ss, token, ' ');

//        auto token = std::string();
//        while (std::getline(ss, token, ' ')) {
//        }
    }

    std::cout << "" << '\n';
    return 0;
}
