#include "place.h"
#include "graph.h"
#include "file_util.h"
#include <iostream>
#include <climits>

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

void menu(bool &ok,PlaceManager &pm, Graph &g);
void showAllPlaces(PlaceManager &pm);
void findPlace(PlaceManager &pm);
void addPlace(PlaceManager &pm, Graph &g);
void deletePlace(PlaceManager &pm, Graph &g);
void updatePlace(PlaceManager &pm);
void addRoad(PlaceManager &pm, Graph &g);
void calculate(PlaceManager &pm, Graph &g);

int main()
{
    string placesFile = getDataDir() + "places.txt";
    string roadsFile = getDataDir() + "roads.txt";

    PlaceManager pm(placesFile);
    pm.loadFromFile();
    Graph g(pm.size(), roadsFile);
    g.loadFromFile();

    bool ok = true;
    while (ok)
    {
        menu(ok,pm,g);
    }

    return 0;
}

// 菜单
void menu(bool &ok,PlaceManager &pm, Graph &g){
    int choice;
    cout << "1. 显示所有地点\n2. 查询地点信息\n3. 添加地点\n4. 删除地点\n5. 修改地点\n6. 添加道路\n7. 查询最短路径\n0. 退出\n";
    cout << "\n请输入选项：\n" ;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        cout<<"------------------------\n";
        cout<<">显示所有地点 \n";
        showAllPlaces(pm);
        cout<<"------------------------\n";
        break;
    }
    case 2:
    {
        cout<<"------------------------\n";
        cout<<">查询地点信息 \n";
        findPlace(pm);
        cout<<"------------------------\n";
        break;
    }
    case 3:
    {
        cout<<"------------------------\n";
        cout<<">添加地点 \n";
        addPlace(pm, g);
        cout<<"------------------------\n";
        break;
    }
    case 4:
    {
        cout<<"------------------------\n";
        cout<<">删除地点 \n";
        deletePlace(pm, g);
        cout<<"------------------------\n";
        break;
    }
    case 5:
    {
        cout<<"------------------------\n";
        cout<<">修改地点 \n";
        updatePlace(pm);
        cout<<"------------------------\n";
        break;
    }
    case 6:
    {
        cout<<"------------------------\n";
        cout<<">添加道路 \n";
        addRoad(pm, g);
        cout<<"------------------------\n";
        break;
    }
    case 7:
    {
        cout<<"------------------------\n";
        cout<<">查询最短路径 \n";
        calculate(pm, g);
        cout<<"------------------------\n";
        break;
    }
    case 0:
    {
        cout<<"------------------------\n";
        cout<<">退出 \n";
        ok = false;
        cout<<"------------------------\n";
        break;
    }
    default:
        cout<<"------------------------\n";
        cout<<">参数错误，请重输 \n";
        cout<<"------------------------\n";
        break;
    }
}

// 1. 显示所有地点
void showAllPlaces(PlaceManager &pm)
{
    pm.printAll();
}

// 2. 查询地点信息
void findPlace(PlaceManager &pm)
{

    cout << "1. 根据id查询\n2. 根据名称查询\n";
    int chioce;
    cin >> chioce;
    if (chioce == 1)
    {
        cout << "输入id: \n";
        int id;
        cin >> id;
        Place *place = pm.findById(id);
        if (place)
        {
            cout << "找到地点  id: " << place->id << "  地点名: " << place->name << endl;
        }
        else
        {
            cout << "地点不存在" << endl;
        }
    }
    else if (chioce == 2)
    {
        cout << "输入地点名称: \n";
        string name;
        cin >> name;
        vector<Place *> p = pm.findByName(name);
        int sum = p.size();
        if (sum == 0)
        {
            cout << "地点名称不存在\n";
        }
        else if (sum == 1)
        {
            cout << "匹配到 id: " << p[0]->id << "  地点名: " << p[0]->name << '\n';
        }
        else
        {
            int idx = 1;
            cout << "匹配到多个地址" << endl;
            for (auto i : p)
            {
                cout << "[" << idx << "] id: " << i->id << "  地点名: " << i->name << endl;
                idx++;
            }
        }
    }
    else
    {
        cout << "参数错误" << '\n';
    }
}

// 3. 添加地点
void addPlace(PlaceManager &pm, Graph &g)
{
    cout<<"请输入地点id及地点名\n";
    int id;
    string name;
    cin >> id >> name;
    if(pm.addPlace(id, name)){
        cout<<"添加成功\n";
        g.resizeTo(pm.size());
    }
}

// 4. 删除地点
void deletePlace(PlaceManager &pm, Graph &g){
    
    cout<<"请输入要删除地点的id: \n";
    int id;
    cin>>id;
    if(pm.deletePlace(id)){
        cout<<"删除成功\n";
        g.resizeTo(pm.size());
    }

}

// 5. 修改地点
void updatePlace(PlaceManager &pm){
    
    cout<<"请输入要修改地点的id及新地点名: \n";
    int id;
    string name;
    cin>>id>>name;
    if(pm.updatePlace(id,name)){
        cout<<"修改成功\n";
    }

}

// 6. 添加道路
void addRoad(PlaceManager &pm, Graph &g)
{
    cout << "请输入起点、终点、路程长度: ";
    int u, v, w;
    cin >> u >> v >> w;
    Place* p1 = pm.findById(u);
    Place* p2 = pm.findById(v);
    if (!p1 && !p2) {
        cout << "起点与终点均不存在\n";
        return;
    }
    if (!p1) {
        cout << "起点不存在\n";
        return;
    }
    if (!p2) {
        cout << "终点不存在\n";
        return;
    }
    
    g.addEdge(u, v, w, true);
}

// 7. 查询最短路径
void calculate(PlaceManager &pm, Graph &g)
{
    pm.loadFromFile();
    g.resizeTo(pm.size());
    g.loadFromFile();

    string start, end;
    cout << "请输入起点地点名: " << endl;
    cin >> start;
    int s = pm.decidePlace(start);
    if (s == -1)
    {
        cout << "地点名称不存在\n";
        return;
    }
    else
    {
        start = pm.findById(s)->name;
        cout << "已匹配到: " << start << endl;
    }

    cout << "请输入终点地点名: " << endl;
    cin >> end;
    int e = pm.decidePlace(end);
    if (e == -1)
    {
        cout << "地点名称不存在\n";
        return;
    }
    else
    {
        end = pm.findById(e)->name;
        cout << "已匹配到: " << end << endl;
    }

    pair<int, vector<int>> pd = g.dijkstra(s, e);
    int dist = pd.first;
    vector<int> path = pd.second;

    if (dist == INT_MAX)
    {
        std::cout << "无法从 " << start << " 到达 " << end << std::endl;
    }
    else
    {
        std::cout << start << " 到 " << end << " 的最短距离为：" << dist << std::endl;
        cout << "路线为: ";
        bool ok = false;
        for (auto i : path)
        {
            if (ok)
                cout << " -> ";
            ok = true;
            cout << "[" << i << "]" << pm.findById(i)->name;
        }
        cout<<'\n';
    }
}
