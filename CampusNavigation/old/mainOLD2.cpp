#include "place.h"
#include "graph.h"
#include "file_util.h" // 用于自动处理 data/ 路径
#include <iostream>
#include <climits>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;

int main()
{
    PlaceManager pm;

    // 自动获取 data 目录下的文件路径
    std::string placesFile = getDataDir() + "places.txt";
    std::string roadsFile = getDataDir() + "roads.txt";
    std::string placesOutFile = getDataDir() + "places_out.txt";

    pm.loadFromFile(placesFile);
    Graph g(pm.size());
    g.loadFromFile(roadsFile);

    string start, end;
    cout << "Start:" << endl;
    cin >> start;
    int s = pm.decidePlace(start);
    start = pm.findById(s)->name;
    if (s == -1) {
        cout << "地点名称不存在\n";
        return 0;
    }
    else {
        cout << "已匹配到: "<<start<<endl;
    }

    cout << "End:" << endl;
    cin >> end;
    int e = pm.decidePlace(end);
    end = pm.findById(e)->name;
    if (e == -1) {
        cout << "地点名称不存在\n";
        return 0;
    }
    else {
        cout << "已匹配到: "<<end<<endl;
    }
    
    pair<int,vector<int>>pd = g.dijkstra(s, e);
    int dist = pd.first;
    vector<int>path = pd.second;

    if (dist == INT_MAX) {
        std::cout << "无法从 " << start << " 到达 " << end << std::endl;
    } else {
        std::cout << start << " 到 " << end << " 的最短距离为：" << dist << std::endl;
        cout<<"路线为: ";
        bool ok = false;
        for(auto i : path){
            if(ok)cout<<" -> ";
            ok = true;
            cout<<"["<<i<<"]"<<pm.findById(i)->name;
        }
    }

    return 0;
}
