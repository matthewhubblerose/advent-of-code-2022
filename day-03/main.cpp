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

std::set<char> to_char_set(std::string_view sv) {
    auto set = std::set<char>();
    for (const auto c: sv) {
        set.insert(c);
    }
    return set;
}

int score(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 1;
    } else {
        return c - 'A' + 27;
    }
}

int main() {
    auto ifs = std::ifstream();
    ifs.open("input.txt");

    auto acc = static_cast<uint64_t>(0);

    auto line = std::string();
    while (std::getline(ifs, line)) {
        auto s = std::string_view(line);
        auto pack_1 = s.substr(0, s.size() / 2);
        auto pack_2 = s.substr(s.size() / 2, s.size());

        const auto chars_1 = to_char_set(pack_1);
        const auto chars_2 = to_char_set(pack_2);

        std::vector<char> intersection;
        std::set_intersection(chars_1.begin(), chars_1.end(), chars_2.begin(), chars_2.end(),
                              std::back_inserter(intersection));

        assert(intersection.size() == 1);
        acc += static_cast<uint64_t>(score(intersection[0]));

    }

    std::cout << acc << '\n';
    return 0;
}
