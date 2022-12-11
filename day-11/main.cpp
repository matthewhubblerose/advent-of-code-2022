#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <numeric>

class Rule {

public:
    enum class Operation {
        ADD, MULTIPLY, SQUARE
    };

    Rule(int id, int id_true, int id_false, Operation op, uint64_t op_val, uint64_t divisor) :
            id(id), id_true(id_true), id_false(id_false), op(op), op_val(op_val), divisor(divisor) {}

    [[nodiscard]] uint64_t operate(uint64_t value) const {
        switch (op) {
            case Operation::ADD:
                return value + op_val;
            case Operation::MULTIPLY:
                return value * op_val;
            case Operation::SQUARE:
                return value * value;
        }
    }

    [[nodiscard]] int pass_id(uint64_t value) const {
        return value % divisor == 0 ? id_true : id_false;
    }

    const int id, id_true, id_false;
    const Operation op;
    const uint64_t op_val, divisor;
};

struct State {
    std::unordered_map<int, std::deque<uint64_t>> items;
    std::vector<Rule> rules;
    std::unordered_map<int, uint64_t> inspections;
};

State parse_state() {
    auto state = State();

    std::string s;
    int id;
    while (std::cin >> s >> id, std::cin.ignore(17)) {
        state.items[id] = {};
        state.inspections[id] = 0;

        char c;
        std::cin >> c;
        uint64_t item;
        while (std::cin >> c >> item) {
            state.items[id].push_back(item);
        }
        std::cin.clear();

        std::cin.ignore(20), std::cin >> c >> s;
        const auto op = s == "old" ? Rule::Operation::SQUARE : c == '*' ? Rule::Operation::MULTIPLY : Rule::Operation::ADD;
        uint64_t op_val = 0;
        if (op != Rule::Operation::SQUARE) {
            op_val = std::stoull(s);
        }

        uint64_t divisor;
        std::cin.ignore(22), std::cin >> divisor;

        int id_true, id_false;
        std::cin.ignore(29), std::cin >> id_true;
        std::cin.ignore(30), std::cin >> id_false;

        state.rules.emplace_back(id, id_true, id_false, op, op_val, divisor);
    }
    return state;
}

uint64_t monkey_business(const std::unordered_map<int, uint64_t> &inspections) {
    auto pq = std::priority_queue<uint64_t, std::vector<uint64_t>, std::greater<>>();
    for (size_t i = 0; i < 2; ++i) pq.push(0);
    for (const auto &item: inspections) {
        if (item.second > pq.top()) {
            pq.pop();
            pq.push(item.second);
        }
    }

    uint64_t total = 1;
    while (!pq.empty()) {
        total *= pq.top();
        pq.pop();
    }
    return total;
}

void part_1() {
    auto state = parse_state();
    for (size_t i = 0; i < 20; ++i) {
        for (const auto &rule: state.rules) {
            auto &items = state.items[rule.id];
            while (!items.empty()) {
                const auto item = items.front();
                items.pop_front();
                const auto value = rule.operate(item) / 3;
                state.items[rule.pass_id(value)].push_back(value);
                ++state.inspections[rule.id];
            }
        }
    }

    std::cout << monkey_business(state.inspections) << '\n';
}

void part_2() {
    auto state = parse_state();

    const auto multiply = [](uint64_t acc, const Rule &rule) { return acc * rule.divisor; };
    const auto lcm = std::accumulate(state.rules.cbegin(), state.rules.cend(), static_cast<uint64_t>(1), multiply);

    for (size_t i = 0; i < 10000; ++i) {
        for (const auto &rule: state.rules) {
            auto &items = state.items[rule.id];
            while (!items.empty()) {
                const auto item = items.front();
                items.pop_front();
                const auto value = rule.operate(item) % lcm;
                state.items[rule.pass_id(value)].push_back(value);
                ++state.inspections[rule.id];
            }
        }
    }

    std::cout << monkey_business(state.inspections) << '\n';
}

int main() {
//    part_1(); // 120756
    part_2(); // 39109444654
    return 0;
}
