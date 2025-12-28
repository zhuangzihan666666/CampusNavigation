#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <utility>

class Graph {
private:
    int n;  // 顶点数量
    std::string filename;
    std::vector<std::vector<std::pair<int, int>>> adj; // v1 v2 edge

public:
    Graph(int n = 0, const std::string& file = "");

    // 添加道路
    void addEdge(int u, int v, int w, bool needToSave);

    // 打印全部道路
    void printGraph() const;

    // 计算最短路径
    std::pair<int,std::vector<int>> dijkstra(int start, int end) const;

    // 从文件中加载路径
    bool loadFromFile();

    // 保存路径至文件
    bool saveToFile() const;
};

#endif
