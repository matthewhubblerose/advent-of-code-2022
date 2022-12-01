#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>

int main() {
    auto ifs = std::ifstream();
    ifs.open("input.txt");

    auto elf_calories = std::priority_queue<int64_t>();
    auto acc = static_cast<int64_t>(0);

    auto line = std::string();
    while (std::getline(ifs, line)) {
        if (line.empty()) {
            elf_calories.push(acc);
            acc = 0;
        } else {
            acc += std::stol(line);
        }
    }

    auto total = static_cast<int64_t>(0);
    auto count = 0;
    while (!elf_calories.empty() && count < 3) {
        total += elf_calories.top();
        elf_calories.pop();
        count++;
    }

    std::cout << total << '\n';
    return 0;
}
