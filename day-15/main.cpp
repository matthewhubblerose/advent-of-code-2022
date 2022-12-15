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

struct Sensed {
    Point sensor;
    int distance;
};

struct SparseRange {

    std::vector<std::pair<int, int>> ranges;

    void add(int min, int max) {
        ranges.emplace_back(min, max);
    }

    int first_gap() {
        int val = 0;
        std::sort(ranges.begin(), ranges.end());
        for (const auto &r: ranges) {
            if (val < r.first) return val;
            else if (r.second + 1 > val) val = r.second + 1;
        }
        return val;
    }

};

void part_2() {
    auto sensor = Point();
    auto beacon = Point();
    auto sensed = std::vector<Sensed>();

    while (std::cin.ignore(12), std::cin >> sensor.x, std::cin.ignore(4), std::cin >> sensor.y, std::cin.ignore(25), std::cin >> beacon.x, std::cin.ignore(4), std::cin >> beacon.y) {
        std::cin.ignore(1);
        sensed.push_back({sensor, manhattan_distance(sensor, beacon)});
    }

    const auto size = 4000000;
    for (int y = 0; y <= size; ++y) {
        auto sr = SparseRange();
        for (const auto &s: sensed) {
            const auto &sen = s.sensor;
            const auto x = sen.x;
            const auto p = Point{x, y};
            const auto distance = manhattan_distance(p, sen);
            if (distance <= s.distance) {
                const auto spread = s.distance - distance;
                const auto min_x = std::max(x - spread, 0);
                const auto max_x = std::min(x + spread, size);
                sr.add(min_x, max_x);
            }
        }
        int gap = sr.first_gap();
        if (gap <= size) {
            const auto ans = (static_cast<uint64_t>(gap) * static_cast<uint64_t>(4000000)) + static_cast<uint64_t>(y);
            std::cout << ans << '\n';
            return;
        }
    }

    std::cout << "Oops" << '\n';
}

int main() {
//    part_1(); // 4725496
    part_2(); // 12051287042458
    return 0;
}