#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

std::string coord(size_t x, size_t y) {
    std::ostringstream oss;
    oss << x << ',' << y;
    return oss.str();
}

std::vector<std::vector<int>> parse_grid() {
    std::vector<std::vector<int>> grid;
    std::string line;
    while (std::cin >> line) {
        grid.emplace_back();
        auto &row = grid.back();
        for (char i : line) {
            row.push_back(i - '0');
        }
    }
    return grid;
}

void part_1() {
    const auto grid = parse_grid();

    std::unordered_set<std::string> visible;

    std::vector<std::pair<int, int>> d = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    for (size_t y = 0; y < grid.size(); ++y) {
        const auto &row = grid[y];
        int max = -1;
        for (size_t x = 0; x < row.size(); ++x) {
            if (grid[x][y] > max) {
                max = grid[x][y];
                visible.insert(coord(x, y));
            } else if (grid[x][y] == 9) {
                break;
            }
        }
        max = -1;
        for (size_t x = row.size(); x-- > 0;) {
            if (grid[x][y] > max) {
                max = grid[x][y];
                visible.insert(coord(x, y));
            } else if (grid[x][y] == 9) {
                break;
            }
        }
    }

    for (size_t x = 0; x < grid[0].size(); ++x) {
        int max = -1;
        for (size_t y = 0; y < grid.size(); ++y) {
            if (grid[x][y] > max) {
                max = grid[x][y];
                visible.insert(coord(x, y));
            } else if (grid[x][y] == 9) {
                break;
            }
        }
        max = -1;
        for (size_t y = grid.size(); y-- > 0;) {
            if (grid[x][y] > max) {
                max = grid[x][y];
                visible.insert(coord(x, y));
            } else if (grid[x][y] == 9) {
                break;
            }
        }
    }

    std::cout << visible.size() << '\n';
}

int calc_score(const std::vector<std::vector<int>> &grid, size_t x, size_t y) {
    if (x == 0 || y == 0) return 0;
    int u = 0, d = 0, l = 0, r = 0;

    for (size_t i = y - 1; i != std::numeric_limits<size_t>::max(); --i) {
        ++u;
        if (grid[i][x] >= grid[y][x]) break;
    }
    for (size_t i = y + 1; i < grid.size(); ++i) {
        ++d;
        if (grid[i][x] >= grid[y][x]) break;
    }
    for (size_t i = x - 1; i != std::numeric_limits<size_t>::max(); --i) {
        ++l;
        if (grid[y][i] >= grid[y][x]) break;
    }
    for (size_t i = x + 1; i < grid[0].size(); ++i) {
        ++r;
        if (grid[y][i] >= grid[y][x]) break;
    }
    return u * d * l * r;
}

void part_2() {
    const auto grid = parse_grid();
    int max_score = -1;

    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[0].size(); ++x) {
            int score = calc_score(grid, x, y);
            if (score > max_score) {
                max_score = score;
            }
        }
    }

    std::cout << max_score << '\n';
}

int main() {
//    part_1(); // 1843
    part_2(); // 180000
    return 0;
}
