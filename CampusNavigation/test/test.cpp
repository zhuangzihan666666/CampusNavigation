#include <fstream>
#include <string>
#include <iostream>
#include <direct.h> // mkdir for Windows

void ensureDataDir() {
    _mkdir("data"); // Windows 创建目录，如果已存在会忽略
}

int main() {
    ensureDataDir();

    std::ifstream fin("data/places.txt");
    if(!fin.is_open()) {
        std::cout << "无法打开文件 data/places.txt\n";
        return 1;
    }

    std::ofstream fout("data/places_out.txt");
    if(!fout.is_open()) {
        std::cout << "无法写入文件 data/places_out.txt\n";
        return 1;
    }

    fout << "测试内容\n";

    return 0;
}
