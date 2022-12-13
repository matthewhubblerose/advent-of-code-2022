#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <charconv>

template<typename C, typename T>
typename C::difference_type index_of(const C &v, const T &f) {
    const auto it = std::find(v.cbegin(), v.cend(), f);
    if (it == v.cend()) return -1;
    return std::distance(v.begin(), it);
}

template<typename T>
int compare(const T &l, const T &r) { return (l < r) ? -1 : (l > r) ? 1 : 0; }

int svtoi(std::string_view sv) {
    int i;
    const auto res = std::from_chars(sv.begin(), sv.end(), i);
    assert(static_cast<int>(res.ec) == 0);
    return i;
}

struct Packet {
    std::vector<Packet> children;
    int val = -1;
};

Packet packet_with_child(int val) {
    auto p = Packet();
    p.children.emplace_back().val = val;
    return p;
}

Packet parse(std::string_view s) {
    s = s.substr(1, s.size() - 2); // optional - ignore opening and closing []
    auto stack = std::stack<Packet*>();
    auto packet = Packet();
    auto current = &packet;
    for (size_t i = 0; i < s.size(); ++i) {
        const char c = s[i];
        if (c == '[') {
            auto &child = current->children.emplace_back();
            stack.push(current);
            current = &child;
        } else if (c == ']') {
            current = stack.top();
            stack.pop();
        } else if (c != ',') {
            const auto start = i;
            size_t len = 1;
            while (i + len < s.size() && std::isdigit(s[i + len])) ++len;
            i += len;
            current->children.emplace_back().val = svtoi(s.substr(start, len));
        }
    }
    return packet;
}

int order(const Packet &p1, const Packet &p2) {
    if (p1.val != -1 && p2.val != -1) {
        return compare(p1.val, p2.val);
    } else if (p1.val == -1 && p2.val == -1) {
        const auto size = std::min(p1.children.size(), p2.children.size());
        for (size_t i = 0; i < size; ++i) {
            const auto cmp = order(p1.children[i], p2.children[i]);
            if (cmp != 0) return cmp;
        }
        return compare(p1.children.size(), p2.children.size());
    } else {
        if (p1.val != -1) return order(packet_with_child(p1.val), p2);
        else              return order(p1, packet_with_child(p2.val));
    }
}

void part_1() {
    int index = 1;
    int total = 0;
    std::string line_1, line_2;
    while (std::cin >> line_1 >> line_2) {
        if (order(parse(line_1), parse(line_2)) == -1) total += index;
        ++index;
    }
    std::cout << total << '\n';
}

void part_2() {
    using namespace std::string_literals;
    std::vector<std::string> p = {"[[2]]", "[[6]]"};
    std::string line_1, line_2;
    while (std::cin >> line_1 >> line_2) { p.push_back(line_1); p.push_back(line_2); }
    std::sort(p.begin(), p.end(), [](const std::string &l, const std::string &r) {
        return order(parse(l), parse(r)) == -1;
    });
    std::cout << ((index_of(p, "[[2]]"s) + 1) * (index_of(p, "[[6]]"s) + 1)) << '\n';
}

int main() {
//    part_1(); // 4734
    part_2(); // 21836
    return 0;
}
