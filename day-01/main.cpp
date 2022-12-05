#include <iostream>
#include <string>
#include <queue>

void solve(size_t size) {
    auto calories = std::priority_queue<int, std::vector<int>, std::greater<>>();
    int acc = 0;

    auto line = std::string();
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            if (calories.size() < size) {
                calories.push(acc);
            } else if (acc > calories.top()) {
                calories.pop();
                calories.push(acc);
            }
            acc = 0;
        } else {
            acc += std::stoi(line);
        }
    }

    int total = 0;
    while (!calories.empty()) {
        total += calories.top();
        calories.pop();
    }
    std::cout << total << '\n';
}

void part_1() {
    solve(1);
}

void part_2() {
    solve(3);
}

int main() {
//    part_1(); // 71924
    part_2(); // 210406
    return 0;
}
