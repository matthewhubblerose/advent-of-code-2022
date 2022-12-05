#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <deque>

bool get_crate(std::string_view sv, size_t &index, char &crate) {
    if (index >= sv.length()) { return false; }
    crate = sv[index + 1];
    index += 4;
    return true;
}

void part_1() {
    auto stacks = std::vector<std::deque<char>>();

    std::string line;
    // Read stacks
    while (std::getline(std::cin, line) && line[1] != '1') {
        auto ss = std::istringstream(line);
        char crate;
        size_t stack = 0;
        size_t index = 0;
        while (get_crate(line, index, crate)) {
            if (stacks.size() < stack + 1) {
                stacks.emplace_back();
            }
            if (crate != ' ') {
                stacks[stack].push_front(crate);
            }
            ++stack;
        }
    }

    // Read instructions and process
    std::string s;
    size_t count, src, dst;
    while (std::cin >> s >> count >> s >> src >> s >> dst) {
        while (count != 0) {
            stacks[dst - 1].push_back(stacks[src - 1].back());
            stacks[src - 1].pop_back();
            --count;
        }
    }

    for (const auto &stack: stacks) {
        std::cout << stack.back();
    }
    std::cout << '\n';
}

void part_2() {

}

int main() {
    part_1();
    part_2();
    return 0;
}
