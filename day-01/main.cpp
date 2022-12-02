#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <functional>

int main() {
    auto ifs = std::ifstream();
    ifs.open("input.txt");

    auto calories = std::priority_queue<int64_t, std::vector<int64_t>, std::greater<>>();
    auto acc = static_cast<int64_t>(0);

    auto line = std::string();
    while (std::getline(ifs, line)) {
        if (line.empty()) {
            if (calories.size() < 3) {
                calories.push(acc);
            } else if (acc > calories.top()) {
                calories.pop();
                calories.push(acc);
            }
            acc = 0;
        } else {
            acc += std::stol(line);
        }
    }

    auto total = static_cast<int64_t>(0);
    while (!calories.empty()) {
        total += calories.top();
        calories.pop();
    }

    std::cout << total << '\n';
    return 0;
}
