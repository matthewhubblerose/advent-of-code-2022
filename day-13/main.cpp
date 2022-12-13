#include <iostream>
#include <vector>
#include <string>
#include <stack>

struct Packet {
    std::vector<std::unique_ptr<Packet>> children;
    int val = -1;
};

std::unique_ptr<Packet> parse_packet(std::string_view s) {
    auto stack = std::stack<Packet*>();
    auto packet = std::make_unique<Packet>();
    auto current = packet.get();
    for (size_t i = 0; i < s.size(); ++i) {
        const char c = s[i];
        if (c == '[') {
            auto child = current->children.emplace_back(std::make_unique<Packet>()).get();
            stack.push(current);
            current = child;
        } else if (c == ']') {
            current = stack.top();
            stack.pop();
        } else if (c != ',') {
            const auto start = i;
            while (i < s.size() - 1 && std::isdigit(s[i + 1])) ++i;
            const int val = std::stoi(std::string(s.substr(start, (i + 1) - start)));
            auto child = current->children.emplace_back(std::make_unique<Packet>()).get();
            child->val = val;
        }
    }
    return packet;
}

int order(const Packet &p1, const Packet &p2) {
    if (p1.val >= 0 && p2.val >= 0) {
        // both values are integers
        if (p1.val < p2.val) return -1;
        else if (p1.val > p2.val) return 1;
        else return 0;
    } else if (p1.val == -1 && p2.val == -1) {
        // both values are lists
        const auto size = std::min(p1.children.size(), p2.children.size());
        for (size_t i = 0; i < size; ++i) {
            const auto o = order(*p1.children[i], *p2.children[i]);
            if (o != 0) return o;
        }
        if (p1.children.size() < p2.children.size()) return -1;
        else if (p1.children.size() > p2.children.size()) return 1;
        else return 0;
    } else {
        // one is an integer, one is a list
        if (p1.val == -1) {
            auto l2 = std::make_unique<Packet>();
            auto *child = l2->children.emplace_back(std::make_unique<Packet>()).get();
            child->val = p2.val;
            return order(p1, *l2);
        } else {
            auto l1 = std::make_unique<Packet>();
            auto *child = l1->children.emplace_back(std::make_unique<Packet>()).get();
            child->val = p1.val;
            return order(*l1, p2);
        }
    }
}

bool in_order(const Packet &p1, const Packet &p2) {
    return order(p1, p2) == -1;
}

void part_1() {
    std::string line_1, line_2;
    int index = 1;
    int total = 0;
    while (std::cin >> line_1 >> line_2) {
        auto packet_1 = parse_packet(line_1);
        auto packet_2 = parse_packet(line_2);
        if (in_order(*packet_1, *packet_2)) {
            total += index;
        }
        ++index;
    }

    std::cout << total << '\n';
}

void part_2() {
    std::vector<std::string> packets;
    packets.emplace_back("[[2]]");
    packets.emplace_back("[[6]]");

    std::string line_1, line_2;
    while (std::cin >> line_1 >> line_2) {
        packets.push_back(line_1);
        packets.push_back(line_2);
    };

    std::sort(packets.begin(), packets.end(), [](const std::string &l, const std::string &r) {
        const auto p1 = parse_packet(l);
        const auto p2 = parse_packet(r);
        return in_order(*p1, *p2);
    });

    const auto start = std::distance(packets.begin(), std::find(packets.begin(), packets.end(), "[[2]]")) + 1;
    const auto end = std::distance(packets.begin(), std::find(packets.begin(), packets.end(), "[[6]]")) + 1;
    std::cout << (start * end) << '\n';
}

int main() {
//    part_1(); // 4734
    part_2(); // 21836
    return 0;
}
