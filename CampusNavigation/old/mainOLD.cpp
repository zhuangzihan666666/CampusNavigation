#include "place.h"
#include "graph.h"
#include "file_util.h"  // 用于自动处理 data/ 路径
#include <iostream>
#include <climits>

int main() {
    PlaceManager pm;

    // 自动获取 data 目录下的文件路径
    std::string placesFile = getDataDir() + "places.txt";
    std::string roadsFile = getDataDir() + "roads.txt";
    std::string placesOutFile = getDataDir() + "places_out.txt";

    // 1️⃣ 加载数据
    pm.loadFromFile(placesFile);

    std::cout << "=== 初始数据 ===" << std::endl;
    pm.printAll();

    // 2️⃣ 增删改查测试
    pm.addPlace(8, "体育馆", "运动设施");
    pm.updatePlace(1, "教学楼A1111", "教学楼");
    pm.deletePlace(2);

    std::cout << "\n=== 修改后数据 ===" << std::endl;
    pm.printAll();

    // 3️⃣ 保存到 places_out.txt
    pm.saveToFile(placesOutFile);

    std::cout << "\n文件处理完成，places_out.txt 已生成" << std::endl;


    // ----------------------------------
    Graph g(6);

    if (!g.loadFromFile(roadsFile)) {
        return 0;
    }

    std::cout << "【道路结构】\n";
    g.printGraph();

    int start = 1;
    int end = 5;

    int dist = g.dijkstra(start, end);
    if (dist == INT_MAX) {
        std::cout << "无法从 " << start << " 到达 " << end << std::endl;
    } else {
        std::cout << start << " 到 " << end
                  << " 的最短距离为：" << dist << std::endl;
    }

    g.printGraph();

    int d = g.dijkstra(1, 4);
    std::cout << "1 到 4 的最短距离 = " << d << std::endl;
    

    return 0;
}
