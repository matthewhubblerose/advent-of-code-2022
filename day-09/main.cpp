#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

void part_1() {
    const std::unordered_map<char, std::pair<int, int>> deltas = {
            {'U', {0,  1}},
            {'R', {1,  0}},
            {'D', {0,  -1}},
            {'L', {-1, 0}}
    };
    std::set<std::pair<int, int>> visited = {{0, 0}};
    int hx = 0, hy = 0, tx = 0, ty = 0;
    char direction;
    int count;
    while (std::cin >> direction >> count) {
        const auto &delta = deltas.at(direction);
        for (int i = 0; i < count; ++i) {
            hx += delta.first;
            hy += delta.second;
            if (hx == tx) {
                if (hy - ty < -1) --ty;
                else if (hy - ty > 1) ++ty;
            } else if (hy == ty) {
                if (hx - tx < -1) --tx;
                else if (hx - tx > 1) ++tx;
            } else if (std::abs(hy - ty) == 1 && std::abs(hx - tx) > 1) {
                ty = hy;
                if (hx - tx > 1) ++tx;
                else if (hx - tx < -1) --tx;
            } else if (std::abs(hx - tx) == 1 && std::abs(hy - ty) > 1) {
                tx = hx;
                if (hy - ty > 1) ++ty;
                else if (hy - ty < -1) --ty;
            }
            visited.insert({tx, ty});
        }
    }

    std::cout << visited.size() << '\n';
}
void part_2() {
    const std::unordered_map<char, std::pair<int, int>> deltas = {
            {'U', {0,  1}},
            {'R', {1,  0}},
            {'D', {0,  -1}},
            {'L', {-1, 0}}
    };
    std::set<std::pair<int, int>> visited = {{0, 0}};
    std::vector<std::pair<int, int>> rope(10);
    char direction;
    int count;
    while (std::cin >> direction >> count) {
        const auto &delta = deltas.at(direction);
        for (int i = 0; i < count; ++i) {
            int &x = rope[0].first, &y = rope[0].second;
            x += delta.first;
            y += delta.second;
            for (size_t j = 1; j < rope.size(); ++j) {
                int &hx = rope[j - 1].first, &hy = rope[j - 1].second;
                int &tx = rope[j].first, &ty = rope[j].second;
                if (hx == tx) {
                    if (hy - ty < -1) --ty;
                    else if (hy - ty > 1) ++ty;
                } else if (hy == ty) {
                    if (hx - tx < -1) --tx;
                    else if (hx - tx > 1) ++tx;
                } else if (std::abs(hy - ty) == 1 && std::abs(hx - tx) > 1) {
                    ty = hy;
                    if (hx - tx > 1) ++tx;
                    else if (hx - tx < -1) --tx;
                } else if (std::abs(hx - tx) == 1 && std::abs(hy - ty) > 1) {
                    tx = hx;
                    if (hy - ty > 1) ++ty;
                    else if (hy - ty < -1) --ty;
                } else if (std::abs(hx - tx) == 2 && std::abs(hy - ty) == 2) {
                    if (tx < hx) tx = hx - 1;
                    else tx = hx + 1;
                    if (hy - ty > 1) ++ty;
                    else if (hy - ty < -1) --ty;
                }
            }
            visited.insert({rope.back().first, rope.back().second});
        }
    }

    std::cout << visited.size() << '\n';
}

int main() {
    // part_1(); // 6026
    part_2(); // 2273
    return 0;
}
