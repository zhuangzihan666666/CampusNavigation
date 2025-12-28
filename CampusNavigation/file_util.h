#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <fstream>
#include <iostream>
#include <string>
#include <direct.h>  // Windows mkdir
#include <sys/stat.h> // Linux mkdir
#include <algorithm>

// 获取源文件所在目录（即项目根目录）
inline std::string getProjectRoot() {
    std::string path = __FILE__; // 当前源文件路径
    // 查找最后一个路径分隔符
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos) return "./"; // fallback
    return path.substr(0, pos + 1);
}

// 创建目录，如果目录存在会自动忽略
inline void ensureDirectory(const std::string& dir) {
#ifdef _WIN32
    _mkdir(dir.c_str());
#else
    mkdir(dir.c_str(), 0755);
#endif
}

// 返回 data 目录的完整路径，并确保目录存在
inline std::string getDataDir() {
    std::string dataPath = getProjectRoot() + "data/";
    ensureDirectory(dataPath);
    return dataPath;
}

// 打开输入文件（在 data/ 下）
inline std::ifstream openInputFile(const std::string& filename) {
    std::string filepath = getDataDir() + filename;
    std::ifstream fin(filepath);
    if (!fin.is_open()) {
        std::cerr << "【错误】无法打开文件: " << filepath << std::endl;
    }
    return fin;
}

// 打开输出文件（在 data/ 下）
inline std::ofstream openOutputFile(const std::string& filename) {
    std::string filepath = getDataDir() + filename;
    std::ofstream fout(filepath);
    if (!fout.is_open()) {
        std::cerr << "【错误】无法写入文件: " << filepath << std::endl;
    }
    return fout;
}

#endif // FILE_UTIL_H
