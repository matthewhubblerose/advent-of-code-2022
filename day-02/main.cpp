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

    auto points = std::unordered_map<char, uint64_t>();
    points['A'] = 1;
    points['B'] = 2;
    points['C'] = 3;
    points['X'] = 1;
    points['Y'] = 2;
    points['Z'] = 3;
    // loss = 0
    // draw = 3
    // win  = 6

    auto line = std::string();

    auto score = static_cast<uint64_t>(0);

    while (std::getline(ifs, line)) {
        auto ss = std::istringstream(line);

        char elf;
        char you;
        ss >> elf >> you;

        score += points.at(you);

        if ((you == 'X' && elf == 'A') || (you == 'Y' && elf == 'B') || (you == 'Z' && elf == 'C')) {
            score += 3;
        } else if ((you == 'X' && elf == 'C') || (you == 'Y' && elf == 'A') || (you == 'Z' && elf == 'B')) {
            score += 6;
        }

    }

    std::cout << score << '\n';
    return 0;
}
