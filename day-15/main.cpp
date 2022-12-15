#include <iostream>
#include <vector>

struct Point {
    int x, y;

    void plus(const Point &point) { x += point.x; y += point.y; }
    bool operator<(const Point &rhs) const { return std::tie(x, y) < std::tie(rhs.x, rhs.y); }
    bool operator==(const Point &rhs) const { return std::tie(x, y) == std::tie(rhs.x, rhs.y); }
    bool operator!=(const Point &rhs) const { return !(rhs == *this); }
};

int manhattan_distance(const Point &l, const Point &r) {
    return std::abs(l.x - r.x) + std::abs(l.y - r.y);
}

class SparseInterval {

public:
    explicit SparseInterval(size_t capacity) {
        intervals.reserve(capacity);
    }

    void reset() {
        intervals.clear();
    }

    void add(int min, int max) {
        intervals.emplace_back(min, max);
    }

    int first_gap() {
        int x = 0;
        std::sort(intervals.begin(), intervals.end());
        for (const auto &[min, max]: intervals) {
            if (x < min) return x;
            else if (max + 1 > x) x = max + 1;
        }
        return x;
    }

    int filled() {
        int count = 0;
        std::sort(intervals.begin(), intervals.end());
        int x = intervals[0].first;
        for (const auto &[min, max]: intervals) {
            if (x >= min && x < max) count += (max - x);
            if (x < max) x = max;
        }
        return count;
    }

private:
    std::vector<std::pair<int, int>> intervals;
};

void part_1() {
    int sx, sy, bx, by;
    const int row = 2000000;
    auto si = SparseInterval(33);

    while (std::cin.ignore(12), std::cin >> sx, std::cin.ignore(4), std::cin >> sy, std::cin.ignore(25), std::cin >> bx, std::cin.ignore(4), std::cin >> by) {
        std::cin.ignore(1);
        auto sensor = Point{sx, sy};
        auto beacon = Point{bx, by};
        const auto distance = manhattan_distance(sensor, beacon);
        const auto row_distance = manhattan_distance(sensor, {sensor.x, row});
        if (row_distance <= distance) {
            const auto spread = distance - row_distance;
            si.add(sx - spread, sx + spread);
        }
    }

    std::cout << si.filled() << '\n';
}

struct SensorRange {
    Point sensor;
    int distance;
    int min_y;
    int max_y;
};

void part_2() {
    int sx, sy, bx, by;
    auto sensors = std::vector<SensorRange>();

    const auto size = 4000000;
    while (std::cin.ignore(12), std::cin >> sx, std::cin.ignore(4), std::cin >> sy, std::cin.ignore(25), std::cin >> bx, std::cin.ignore(4), std::cin >> by) {
        std::cin.ignore(1);
        const auto sensor = Point{sx, sy};
        const auto beacon = Point{bx, by};
        const auto distance = manhattan_distance(sensor, beacon);
        const auto min_y = std::max(sy - distance, 0);
        const auto max_y = std::min(sy + distance, size);
        sensors.push_back({sensor, distance, min_y, max_y});
    }

    auto si = SparseInterval(sensors.size());
    for (int y = 0; y <= size; ++y) {
        si.reset();
        for (const auto &sensor_range: sensors) {
            if (y < sensor_range.min_y || y > sensor_range.max_y) continue;
            const auto x = sensor_range.sensor.x;
            const auto distance = manhattan_distance(Point{x, y}, sensor_range.sensor);
            if (distance <= sensor_range.distance) {
                const auto spread = sensor_range.distance - distance;
                const auto min_x = std::max(x - spread, 0);
                const auto max_x = std::min(x + spread, size);
                si.add(min_x, max_x);
            }
        }
        const int x = si.first_gap();
        if (x <= size) {
            std::cout << (static_cast<uint64_t>(x) * 4000000) + static_cast<uint64_t>(y) << '\n';
            return;
        }
    }

    assert(false);
}

int main() {
    part_1(); // 4725496
//    part_2(); // 12051287042458
    return 0;
}