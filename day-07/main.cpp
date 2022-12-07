#include <iostream>
#include <sstream>
#include <vector>
#include <numeric>

struct Dir {
    Dir *parent;
    std::vector<Dir> dirs;
    int files_size = 0;

    explicit Dir(Dir *parent) : parent(parent) {}

    [[nodiscard]] int size() const {
        const auto dirs_size = std::accumulate(dirs.begin(), dirs.end(), 0, [](const int acc, const Dir &dir) {
            return acc + dir.size();
        });
        return files_size + dirs_size;
    }
};

int summed_small_dir_sizes(const Dir &dir) {
    int acc = 0;
    const auto size = dir.size();
    if (size <= 100000) acc += size;
    for (const auto &child_dir: dir.dirs) {
        acc += summed_small_dir_sizes(child_dir);
    }
    return acc;
}

void smallest_deletable_dir_size(const Dir &dir, int needed_space, int &out_size) {
    const auto size = dir.size();
    if (size < needed_space) return;
    if (size < out_size) out_size = size;
    for (const auto &child_dir: dir.dirs) {
        smallest_deletable_dir_size(child_dir, needed_space, out_size);
    }
}

std::unique_ptr<Dir> parse_dirs() {
    auto root_dir = std::make_unique<Dir>(nullptr);
    auto *current_dir = root_dir.get();

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "$ cd ..") {
            current_dir = current_dir->parent;
        } else if (line.starts_with("$ cd")) {
            current_dir->dirs.emplace_back(current_dir);
            current_dir = &current_dir->dirs.back();
        } else if (std::isdigit(line[0])) {
            int size;
            std::istringstream(line) >> size;
            current_dir->files_size += size;
        }
    }
    return root_dir;
}

void part_1() {
    std::cout << summed_small_dir_sizes(*parse_dirs()) << '\n';
}

void part_2() {
    const auto root_dir = parse_dirs();
    int size = std::numeric_limits<int>::max();
    smallest_deletable_dir_size(*root_dir, root_dir->size() - 40000000, size);
    std::cout << size << '\n';
}

int main() {
//    part_1(); // 1644735
    part_2(); // 1300850
    return 0;
}
