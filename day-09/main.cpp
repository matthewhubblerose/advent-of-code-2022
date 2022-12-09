#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

struct Point {
    int x, y;

    bool operator<(const Point &rhs) const {
        return std::tie(x, y) < std::tie(rhs.x, rhs.y);
    }
};

int sign(int val) {
    return val == 0 ? 0 : val > 0 ? 1 : -1;
}

void follow(const Point &head, Point &tail) {
    const auto dx = head.x - tail.x;
    const auto dy = head.y - tail.y;
    if (std::abs(dx) > 1 || std::abs(dy) > 1) {
        tail.x += sign(dx);
        tail.y += sign(dy);
    }
}

size_t solve(size_t size) {
    const std::unordered_map<char, Point> deltas = {
            {'U', {0,  1}},
            {'R', {1,  0}},
            {'D', {0,  -1}},
            {'L', {-1, 0}}
    };
    std::set<Point> visited = {{0, 0}};
    std::vector<Point> rope(size);
    char direction;
    int count;
    while (std::cin >> direction >> count) {
        const auto &delta = deltas.at(direction);
        while (count > 0) {
            --count;
            rope[0].x += delta.x;
            rope[0].y += delta.y;
            for (size_t j = 1; j < rope.size(); ++j) {
                follow(rope[j - 1], rope[j]);
            }
            visited.insert(rope.back());
        }
    }
    return visited.size();
}

void part_1() {
    std::cout << solve(2) << '\n';
}

void part_2() {
    std::cout << solve(10) << '\n';
}

int main() {
//     part_1(); // 6026
    part_2(); // 2273
    return 0;
}
