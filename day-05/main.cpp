#include <iostream>
#include <vector>
#include <deque>

std::vector<std::vector<char>> parse_stacks() {
    auto stacks = std::vector<std::vector<char>>();
    std::string line;

    while (std::getline(std::cin, line) && line[1] != '1') {
        for (size_t i = 0; i < line.size(); i += 4) {
            const auto crate = line[i + 1];
            const auto stack_index = i / 4;
            if (stacks.size() < stack_index + 1) stacks.emplace_back();
            if (crate != ' ') stacks[stack_index].insert(stacks[stack_index].cbegin(), crate);
        }
    }
    std::getline(std::cin, line); // skip stack numbers line
    return stacks;
}

void part_1() {
    auto stacks = parse_stacks();

    std::string s;
    size_t src_num, dst_num;
    std::ptrdiff_t count;
    while (std::cin >> s >> count >> s >> src_num >> s >> dst_num) {
        auto &src = stacks[src_num - 1];
        auto &dst = stacks[dst_num - 1];
        std::copy(src.rbegin(), src.rbegin() + count, std::back_inserter(dst));
        src.erase(src.end() - count, src.end());
    }

    for (const auto &stack: stacks) std::cout << stack.back();
    std::cout << '\n';
}

void part_2() {
    auto stacks = parse_stacks();

    std::string s;
    size_t src_num, dst_num;
    std::ptrdiff_t count;
    while (std::cin >> s >> count >> s >> src_num >> s >> dst_num) {
        auto &src = stacks[src_num - 1];
        auto &dst = stacks[dst_num - 1];
        std::copy(src.end() - count, src.end(), std::back_inserter(dst));
        src.erase(src.end() - count, src.end());
    }
    for (const auto &stack: stacks) std::cout << stack.back();
    std::cout << '\n';
}

int main() {
//    part_1(); // QGTHFZBHV
    part_2(); // MGDMPSZTM
    return 0;
}
