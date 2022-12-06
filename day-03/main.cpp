#include <iostream>
#include <vector>
#include <string>
#include <set>

std::set<char> to_char_set(std::string_view sv) {
    return {sv.cbegin(), sv.cend()};
}

int score(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 1;
    } else {
        return c - 'A' + 27;
    }
}

template<typename T, typename C1, typename C2>
std::vector<T> set_intersection(const C1 &a, const C2 &b) {
    std::vector<T> i;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(i));
    return i;
}

void part_1() {
    int acc = 0;
    std::string line;

    while (std::cin >> line) {
        const auto s = std::string_view(line);
        const auto pack_1 = to_char_set(s.substr(0, s.size() / 2));
        const auto pack_2 = to_char_set(s.substr(s.size() / 2, s.size()));
        const auto intersection = set_intersection<char>(pack_1, pack_2);
        assert(intersection.size() == 1);
        acc += score(intersection[0]);
    }

    std::cout << acc << '\n';
}

void part_2() {
    int acc = 0;
    std::string line_1, line_2, line_3;

    while (std::cin >> line_1 >> line_2 >> line_3) {
        const auto chars_1 = to_char_set(line_1);
        const auto chars_2 = to_char_set(line_2);
        const auto chars_3 = to_char_set(line_3);

        auto intersection_1 = set_intersection<char>(chars_1, chars_2);
        auto intersection_2 = set_intersection<char>(intersection_1, chars_3);

        assert(intersection_2.size() == 1);
        acc += score(intersection_2[0]);
    }

    std::cout << acc << '\n';
}

int main() {
//    part_1(); // 7674
    part_2(); // 2805
    return 0;
}
