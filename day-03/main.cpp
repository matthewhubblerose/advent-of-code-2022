#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

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
    auto line_2 = std::string();
    auto line_3 = std::string();
    while (std::getline(ifs, line)) {
        std::getline(ifs, line_2);
        std::getline(ifs, line_3);

        const auto chars_1 = to_char_set(line);
        const auto chars_2 = to_char_set(line_2);
        const auto chars_3 = to_char_set(line_3);

        auto intersection_1 = std::vector<char>();
        std::set_intersection(chars_1.begin(), chars_1.end(), chars_2.begin(), chars_2.end(),
                              std::back_inserter(intersection_1));
        auto intersection_2 = std::vector<char>();
        std::set_intersection(intersection_1.begin(), intersection_1.end(), chars_3.begin(), chars_3.end(),
                              std::back_inserter(intersection_2));

        assert(intersection_2.size() == 1);
        acc += static_cast<uint64_t>(score(intersection_2[0]));
    }

    std::cout << acc << '\n';
    return 0;
}
