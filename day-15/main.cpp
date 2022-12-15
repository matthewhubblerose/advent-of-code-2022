#include <iostream>
#include <vector>
#include <set>

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

void part_1() {
    auto sensor = Point();
    auto beacon = Point();
    auto min_x = std::numeric_limits<int>::max();
    auto max_x = std::numeric_limits<int>::min();
    auto pairs = std::vector<std::pair<Point, Point>>();

    const int row = 2000000;
    auto beacons = std::set<int>();
    auto sensors = std::set<int>();

    while (std::cin.ignore(12), std::cin >> sensor.x, std::cin.ignore(4), std::cin >> sensor.y, std::cin.ignore(25), std::cin >> beacon.x, std::cin.ignore(4), std::cin >> beacon.y) {
        std::cin.ignore(1);
        const auto distance = manhattan_distance(sensor, beacon);
        min_x = std::min(min_x, std::min(sensor.x - distance, beacon.x));
        max_x = std::max(max_x, std::max(sensor.x + distance, beacon.x));
        pairs.emplace_back(std::pair(sensor, beacon));
        if (beacon.y == row) {
            beacons.insert(beacon.x);
        }
        if (sensor.y == row) {
            sensors.insert(sensor.x);
        }
    }

    auto no_beacons = std::set<int>();

    for (const auto &[s, b]: pairs) {
        const auto distance = manhattan_distance(s, b);
        for (int x = min_x; x <= max_x; ++x) {
            const auto point = Point{x,row};
            if (manhattan_distance(s, point) <= distance && !beacons.contains(x)) {
                no_beacons.insert(x);
            }
        }
    }

    std::cout << no_beacons.size() << '\n';
}

struct SensorRange {
    Point sensor;
    int distance;
    int min_y;
    int max_y;
};

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

private:
    std::vector<std::pair<int, int>> intervals;
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
//    part_1(); // 4725496
    part_2(); // 12051287042458
    return 0;
}