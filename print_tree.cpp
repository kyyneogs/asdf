#include <algorithm>
#include <filesystem>  // C++17 이상 필요
#include <iostream>
#include <string>
#include <system_error>
#include <vector>

namespace fs = std::filesystem;

// 전역 카운터 (루트 디렉토리는 카운트하지 않음)
int file_count = 0;
int dir_count = 0;

// 재귀적으로 디렉토리 내용을 출력하는 함수
void print_tree(const fs::path& path, const std::string& prefix = "") {
    std::error_code ec;
    if (!fs::exists(path, ec) || !fs::is_directory(path, ec)) {
        return;
    }

    // 디렉토리 내 엔트리를 수집한 후 이름 순으로 정렬
    std::vector<fs::directory_entry> entries;
    for (const auto& entry : fs::directory_iterator(path, ec)) {
        entries.push_back(entry);
    }
    std::sort(entries.begin(), entries.end(),
              [](const fs::directory_entry& a, const fs::directory_entry& b) {
                  return a.path().filename().string() <
                         b.path().filename().string();
              });

    // 엔트리 순회 (마지막 항목 판별)
    for (size_t i = 0; i < entries.size(); ++i) {
        bool is_last = (i == entries.size() - 1);
        std::cout << prefix << (is_last ? "└── " : "├── ");
        auto filename = entries[i].path().filename().string();

        // 심볼릭 링크 체크
        if (fs::is_symlink(entries[i].symlink_status(ec))) {
            // 심볼릭 링크이면 -> 대상 정보 출력
            std::error_code ec2;
            auto target = fs::read_symlink(entries[i].path(), ec2);
            std::cout << filename << " -> "
                      << (ec2 ? "unreadable" : target.string()) << std::endl;
            ++file_count;
        } else if (fs::is_directory(entries[i].status(ec))) {
            // 디렉토리인 경우 (카운터 증가 후 재귀 호출)
            std::cout << filename << std::endl;
            ++dir_count;
            std::string new_prefix = prefix + (is_last ? "    " : "│   ");
            print_tree(entries[i].path(), new_prefix);
        } else {
            // 파일이면
            std::cout << filename << std::endl;
            ++file_count;
        }
    }
}

int main(int argc, char* argv[]) {
    // 인자 없으면 현재 디렉토리, 있으면 지정한 경로 사용
    fs::path root = (argc >= 2 ? argv[1] : ".");
    std::error_code ec;

    // 루트 존재 여부와 디렉토리 여부 확인
    if (!fs::exists(root, ec)) {
        std::cerr << "Error: " << root << " 경로가 존재하지 않습니다."
                  << std::endl;
        return 1;
    }

    // 루트가 디렉토리면 트리 출력, 파일이면 그냥 이름 출력
    std::cout << root.string() << std::endl;
    if (fs::is_directory(root, ec)) {
        print_tree(root);
    } else {
        ++file_count;
    }
    std::cout << std::endl;
    std::cout << dir_count << " directories, " << file_count << " files"
              << std::endl;
    return 0;
}