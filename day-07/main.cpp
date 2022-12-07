#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>

struct File {
    int size;
    std::string name;

    File(int size, std::string name) : size(size), name(std::move(name)) {}
};

struct Dir {
    Dir *parent;
    std::string name;
    std::vector<std::unique_ptr<Dir>> dirs;
    std::vector<std::unique_ptr<File>> files;

    explicit Dir(Dir *parent, std::string name) : parent(parent), name(std::move(name)) {}

    [[nodiscard]] int size() const {
        int acc = 0;
        for (const auto &file: files) {
            acc += file->size;
        }
        for (const auto &dir: dirs) {
            acc += dir->size();
        }
        return acc;
    }
};

int filtered_size(const Dir &dir) {
    int acc = 0;
    const auto size = dir.size();
    if (size <= 100000) {
        acc += size;
    }
    for (const auto &item: dir.dirs) {
        acc += filtered_size(*item);
    }
    return acc;
}

void deletable_dirs(const Dir &dir, int min_size, std::vector<int> &sizes) {
    const auto size = dir.size();
    if (size >= min_size) {
        sizes.push_back(size);
        for (const auto &item: dir.dirs) {
            deletable_dirs(*item, min_size, sizes);
        }
    }
}

std::unique_ptr<Dir> parse_dirs() {
    std::string line;

    auto root_dir = std::make_unique<Dir>(nullptr, "");
    auto *current_dir = root_dir.get();

    while (std::getline(std::cin, line)) {
        auto ss = std::istringstream(line);
        if (line.starts_with("$ cd")) {
            std::string dir_name;
            ss >> dir_name >> dir_name >> dir_name;
            if (dir_name == "/") {
                current_dir = root_dir.get();
            } else if (dir_name == "..") {
                current_dir = current_dir->parent;
            } else {
                // check if dir already exists?
                auto dir = std::make_unique<Dir>(current_dir, dir_name);
                auto *p = dir.get();
                current_dir->dirs.push_back(std::move(dir));
                current_dir = p;
            }
        } else if (line.starts_with("$ ls")) {
            // do nothing
        } else if (line.starts_with("dir")) {
            // do nothing
        } else {
            int size;
            std::string file_name;
            ss >> size >> file_name;
            current_dir->files.push_back(std::make_unique<File>(size, file_name));
        }
    }
    return root_dir;
}

void part_1() {
    const auto root_dir = parse_dirs();
    const auto foo = filtered_size(*root_dir);
    std::cout << foo << '\n';
}

void part_2() {
    const auto root_dir = parse_dirs();
    const auto free_space = 70000000 - root_dir->size();
    std::vector<int> sizes;
    deletable_dirs(*root_dir, free_space, sizes);
    std::cout << *std::min_element(sizes.cbegin(), sizes.cend()) << '\n';
}

int main() {
//    part_1(); // 1644735
    part_2();
    return 0;
}
