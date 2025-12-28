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

void calculate(PlaceManager &pm, Graph &g, string &placesFile, string &roadsFile);
void addPlace(PlaceManager &pm, string &placesFile);
void addRoad(Graph &g);

int main()
{
    PlaceManager pm;

    // 自动获取 data 目录下的文件路径
    string placesFile = getDataDir() + "places.txt";
    string roadsFile = getDataDir() + "roads.txt";

    pm.loadFromFile(placesFile);
    Graph g(pm.size(),roadsFile);
    g.loadFromFile(roadsFile);

    addRoad(g);
    // calculate(pm,g,placesFile,roadsFile);
    // addPlace(pm,placesFile);
    // calculate(pm,g,placesFile,roadsFile);

    return 0;
}

// 计算路程
void calculate(PlaceManager &pm, Graph &g, string &placesFile, string &roadsFile){
    pm.loadFromFile(placesFile);
    g.loadFromFile(roadsFile);

    string start, end;
    cout << "Start:" << endl;
    cin >> start;
    int s = pm.decidePlace(start);
    if (s == -1) {
        cout << "地点名称不存在\n";
        return;
    }
    else {
        start = pm.findById(s)->name;
        cout << "已匹配到: "<<start<<endl;
    }

    cout << "End:" << endl;
    cin >> end;
    int e = pm.decidePlace(end);
    if (e == -1) {
        cout << "地点名称不存在\n";
        return;
    }
    else {
        end = pm.findById(e)->name;
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
}

// 添加地点
void addPlace(PlaceManager &pm, string &placesFile){
    int id;
    string name, type;
    cin>>id>>name>>type;
    pm.addPlace(id,name,type,placesFile);
}

// 添加道路
void addRoad(Graph &g){
    cout<<"请输入起点、终点、路程长度: ";
    int u,v,w;
    cin>>u>>v>>w;
    g.addEdge(u,v,w);
}

