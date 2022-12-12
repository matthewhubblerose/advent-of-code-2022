#include <iostream>
#include <vector>
#include <set>
#include <queue>

struct Point {
    int x, y;

    Point plus(const Point &point) const { return {x + point.x, y + point.y}; }
    bool operator<(const Point &rhs) const { return std::tie(x, y) < std::tie(rhs.x, rhs.y); }
    bool operator==(const Point &rhs) const { return std::tie(x, y) == std::tie(rhs.x, rhs.y); }
    bool operator!=(const Point &rhs) const { return !(rhs == *this); }
};

std::vector<std::vector<char>> parse_grid() {
    std::vector<std::vector<char>> grid;
    std::string line;
    while (std::cin >> line) {
        grid.emplace_back();
        auto &row = grid.back();
        for (char c : line) {
            row.push_back(c);
        }
    }
    return grid;
}

char get(const std::vector<std::vector<char>> &grid, const Point &pos) {
    return grid[static_cast<size_t>(pos.y)][static_cast<size_t>(pos.x)];
}

void set(std::vector<std::vector<char>> &grid, const Point &pos, char c) {
    grid[static_cast<size_t>(pos.y)][static_cast<size_t>(pos.x)] = c;
}

bool contains(std::vector<std::vector<char>> &grid, const Point &pos) {
    return pos.x >= 0 && static_cast<size_t>(pos.x) < grid[0].size() && pos.y >= 0 && static_cast<size_t>(pos.y) < grid.size();
}

Point char_pos(const std::vector<std::vector<char>> &grid, char c) {
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == c) return {static_cast<int>(x), static_cast<int>(y)};
        }
    }
    assert(false);
}

struct Path {
    Point pos;
    std::vector<Point> steps;
};

const std::vector<Point> directions = {{0, 1},{1,0},{0,-1},{-1,0}};

void part_1() {
    auto grid = parse_grid();
    const auto start = char_pos(grid, 'S');
    const auto end = char_pos(grid, 'E');
    set(grid, start, 'a');
    set(grid, end, 'z');

    auto min_steps = [](const Path &l, const Path &r){ return l.steps.size() > r.steps.size(); };
    auto pq = std::priority_queue<Path, std::vector<Path>, decltype(min_steps)>(min_steps);
    auto visited = std::set<Point>();
    pq.push({start, {start}});

    while (!pq.empty()) {
        auto path = pq.top();
        pq.pop();
        if (visited.contains(path.pos)) continue;
        visited.insert(path.pos);
        if (path.pos == end) {
            std::cout << path.steps.size() - 1 << '\n';
            break;
        }

        for (const auto &dir: directions) {
            const auto cur_pos = path.pos;
            const auto dst_pos = cur_pos.plus(dir);
            if (!contains(grid, dst_pos)) continue;
            if (get(grid, dst_pos) <= get(grid, cur_pos) + 1) {
                auto steps = path.steps;
                steps.push_back(dst_pos);
                pq.push({dst_pos, steps});
            }
        }
    }
}

void part_2() {
    auto grid = parse_grid();
    const auto start = char_pos(grid, 'E');
    set(grid, start, 'z');

    auto min_steps = [](const Path &l, const Path &r){ return l.steps.size() > r.steps.size(); };
    auto pq = std::priority_queue<Path, std::vector<Path>, decltype(min_steps)>(min_steps);
    auto visited = std::set<Point>();
    pq.push({start, {start}});

    while (!pq.empty()) {
        auto path = pq.top();
        pq.pop();
        if (visited.contains(path.pos)) continue;
        visited.insert(path.pos);

        if (get(grid, path.pos) == 'a') {
            std::cout << path.steps.size() - 1 << '\n';
            break;
        }

        for (const auto &dir: directions) {
            const auto cur_pos = path.pos;
            const auto dst_pos = cur_pos.plus(dir);
            if (!contains(grid, dst_pos)) continue;
            if (get(grid, dst_pos) >= get(grid, cur_pos) - 1) {
                auto steps = path.steps;
                steps.push_back(dst_pos);
                pq.push({dst_pos, steps});
            }
        }
    }
}

int main() {
    part_1(); // 370
//    part_2(); // 363
    return 0;
}
