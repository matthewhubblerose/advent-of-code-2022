#include <iostream>
#include <sstream>
#include <vector>

struct Point {
    int x, y;

    void plus(const Point &point) { x += point.x; y += point.y; }
    bool operator<(const Point &rhs) const { return std::tie(x, y) < std::tie(rhs.x, rhs.y); }
    bool operator==(const Point &rhs) const { return std::tie(x, y) == std::tie(rhs.x, rhs.y); }
    bool operator!=(const Point &rhs) const { return !(rhs == *this); }
};

char get(const std::vector<std::vector<char>> &grid, const Point &pos) {
    return grid[static_cast<size_t>(pos.y)][static_cast<size_t>(pos.x)];
}

void set(std::vector<std::vector<char>> &grid, const Point &pos, char c) {
    grid[static_cast<size_t>(pos.y)][static_cast<size_t>(pos.x)] = c;
}

bool contains(std::vector<std::vector<char>> &grid, const Point &pos) {
    return pos.x >= 0 && static_cast<size_t>(pos.x) < grid[0].size() && pos.y >= 0 && static_cast<size_t>(pos.y) < grid.size();
}

void resize(std::vector<std::vector<char>> &grid, int width, int height) {
    grid.resize(static_cast<size_t>(height));
    for (auto &row: grid) row.resize(static_cast<size_t>(width));
}

int sign(int val) {
    return val == 0 ? 0 : val > 0 ? 1 : -1;
}

void part_1() {
    std::string line;
    std::vector<std::vector<Point>> paths;
    int min_x = std::numeric_limits<int>::max();
    int max_x = std::numeric_limits<int>::min();
    int max_y = std::numeric_limits<int>::min();
    while (std::getline(std::cin, line)) {
        auto &path = paths.emplace_back();
        auto ss = std::istringstream(line);
        int x, y;
        char c;
        while (ss >> x >> c >> y) {
            path.push_back({x, y});
            if (x < min_x) min_x = x;
            if (x > max_x) max_x = x;
            if (y > max_y) max_y = y;
            ss.ignore(4);
        }
    }

    std::vector<std::vector<char>> grid;

    int width = max_x - min_x + 1;
    int height = max_y + 1;
    resize(grid, width, height);
    for (auto &row: grid) {
        for (auto &c: row) c = '.';
    }

    const auto sand = Point{500, 0};
    set(grid, {sand.x - min_x, sand.y}, '+');

    for (const auto &path: paths) {
        for (size_t i = 1; i < path.size(); ++i) {
            const auto &start = path[i - 1];
            const auto &end = path[i];
            const auto d = Point{sign(end.x - start.x), sign(end.y - start.y)};
            auto pos = start;
            while (pos != end) {
                set(grid, {pos.x - min_x, pos.y}, '#');
                pos.plus(d);
            }
            set(grid, {pos.x - min_x, pos.y}, '#');
        }
    }

    int sand_count = 0;

    const std::vector<Point> directions = {{0, 1},{-1,1},{1,1}};

    const auto sand_start = Point{sand.x - min_x, sand.y};
    while (true) {
        auto pos = sand_start;
        bool settled = false;
        bool off_grid = false;
        while (!settled) {
            settled = true;
            for (const auto &d: directions) {
                auto next = pos;
                next.plus(d);
                if (contains(grid, next)) {
                    if (get(grid, next) == '.') {
                        pos = next;
                        settled = false;
                        break;
                    }
                } else {
                    off_grid = true;
                    break;
                }
            }

        }

        if (off_grid || pos == sand_start) break;
        ++sand_count;
        set(grid, pos, 'o');

//        std::cout << "Sand count: " << sand_count  << '\n';
//        for (const auto &row: grid) {
//            for (const auto &c: row) std::cout << c;
//            std::cout << '\n';
//        }
//        std::cout << '\n';
    }

    std::cout << sand_count << '\n';
}

void part_2() {
    std::string line;
    std::vector<std::vector<Point>> paths;
    int min_x = std::numeric_limits<int>::max();
    int max_x = std::numeric_limits<int>::min();
    int max_y = std::numeric_limits<int>::min();
    while (std::getline(std::cin, line)) {
        auto &path = paths.emplace_back();
        auto ss = std::istringstream(line);
        int x, y;
        char c;
        while (ss >> x >> c >> y) {
            path.push_back({x, y});
            if (x < min_x) min_x = x;
            if (x > max_x) max_x = x;
            if (y > max_y) max_y = y;
            ss.ignore(4);
        }
    }

    std::vector<std::vector<char>> grid;

    int width = max_x - min_x + 1 + 2000;
    int height = max_y + 3;
    int offset = min_x - 1000;
    resize(grid, width, height);
    for (auto &row: grid) {
        for (auto &c: row) c = '.';
    }
    for (auto &c: grid.back()) c = '#';

    const auto sand = Point{500, 0};
    set(grid, {sand.x - offset, sand.y}, '+');

    for (const auto &path: paths) {
        for (size_t i = 1; i < path.size(); ++i) {
            const auto &start = path[i - 1];
            const auto &end = path[i];
            const auto d = Point{sign(end.x - start.x), sign(end.y - start.y)};
            auto pos = start;
            while (pos != end) {
                set(grid, {pos.x - offset, pos.y}, '#');
                pos.plus(d);
            }
            set(grid, {pos.x - offset, pos.y}, '#');
        }
    }

    int sand_count = 0;

    const std::vector<Point> directions = {{0, 1},{-1,1},{1,1}};

    const auto sand_start = Point{sand.x - offset, sand.y};
    while (true) {
        auto pos = sand_start;
        bool settled = false;
        while (!settled) {
            settled = true;
            for (const auto &d: directions) {
                auto next = pos;
                next.plus(d);
                if (contains(grid, next)) {
                    if (get(grid, next) == '.') {
                        pos = next;
                        settled = false;
                        break;
                    }
                }
            }

        }

        ++sand_count;
        set(grid, pos, 'o');

        if (pos == sand_start) break;
    }

    std::cout << sand_count << '\n';
}

int main() {
//    part_1(); // 873
    part_2(); // 24813
    return 0;
}
