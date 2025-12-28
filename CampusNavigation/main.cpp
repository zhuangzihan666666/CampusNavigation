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

void showAllPlaces(PlaceManager &pm);
void calculate(PlaceManager &pm, Graph &g);
void addPlace(PlaceManager &pm);
void addRoad(Graph &g);

int main()
{

    // 自动获取 data 目录下的文件路径
    string placesFile = getDataDir() + "places.txt";
    string roadsFile = getDataDir() + "roads.txt";

    PlaceManager pm(placesFile);
    pm.loadFromFile();
    Graph g(pm.size(),roadsFile);
    g.loadFromFile();

    // addRoad(g);
    // calculate(pm,g,placesFile,roadsFile);
    // addPlace(pm,placesFile);
    // calculate(pm,g,placesFile,roadsFile);
    bool ok=true;
    while(ok){

        int choice;
        cout<<"1. 显示所有地点\n2. 查询地点信息\n3. 添加地点\n4. 删除地点\n5. 修改地点\n6. 添加道路\n7. 查询最短路径\n0. 退出\n";
        cin>>choice;
        switch (choice)
        {
        case 1:
        {
            showAllPlaces(pm);
            break;
        }
        case 2:
        {
            
            break;
        }
        case 3:
        {
            addPlace(pm);
            break;
        }
        case 4:
        {
            
            break;
        }
        case 5:
        {
            
            break;
        }
        case 6:
        {
            addRoad(g);
            break;
        }
        case 7:
        {
            calculate(pm, g);
            break;
        }
        case 8:
        {
            
            break;
        }
        
        default:
            ok=false;
            break;
        }

    }

    return 0;
}



// 1. 显示所有地点
void showAllPlaces(PlaceManager &pm){
    pm.printAll();
}

// 2. 查询地点信息


// 3. 添加地点
void addPlace(PlaceManager &pm){
    int id;
    string name, type;
    cin>>id>>name>>type;
    pm.addPlace(id,name);
}

// 4. 删除地点


// 5. 修改地点


// 6. 添加道路
void addRoad(Graph &g){
    cout<<"请输入起点、终点、路程长度: ";
    int u,v,w;
    cin>>u>>v>>w;
    g.addEdge(u,v,w,true);
}

// 7. 查询最短路径
void calculate(PlaceManager &pm, Graph &g){
    pm.loadFromFile();
    g.loadFromFile();

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
