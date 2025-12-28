#include "graph.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <climits>
#include <algorithm>
#include "place.h"

using namespace std;

Graph::Graph(int n, const std::string& file) : n(n), filename(file)
{
    adj.resize(n + 1);
}

void Graph::resizeTo(int newN)
{
    if (newN <= 0 || newN == n) return;

    // 如果缩小，需要先剔除越界的边
    if (newN < n) {
        for (int u = 1; u <= newN; ++u) {
            auto &edges = adj[u];
            edges.erase(std::remove_if(edges.begin(), edges.end(), [newN](const std::pair<int,int>& e){
                return e.first > newN;
            }), edges.end());
        }
    }

    n = newN;
    adj.resize(n + 1);
}

void Graph::printGraph() const
{
    for (int u = 1; u <= n; ++u)
    {
        cout << "地点 " << u << ": ";
        for (auto i : adj[u])
        {
            int v = i.first, w = i.second;
            cout << "(" << v << ", " << w << ") ";
        }
        cout << endl;
    }
}

pair<int,vector<int>> Graph::dijkstra(int start, int end) const
{
    vector<int> dist(n + 1, INT_MAX);
    vector<bool> vis(n + 1, false);
    vector<int> prev(n + 1, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        auto tt = pq.top();
        int u = tt.second;
        pq.pop();

        if (vis[u])
            continue;
        vis[u] = true;

        if (u == end)
            break;
// cout<<"3";
        for (auto i : adj[u])
        {
            int v = i.first, w = i.second;
            // cout<<u<<" "<<v<<" "<<w<<endl;
            // if (dist[v] > dist[u] + w)
            if (dist[u] != INT_MAX && dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    vector<int>path;
    if(dist[end] != INT_MAX){
        for (int cur = end; cur != -1; cur = prev[cur]) {
            path.push_back(cur);
        }
        std::reverse(path.begin(), path.end());
    }
// cout<<"4";
    return {dist[end],path};
}


bool Graph::saveToFile() const
{
    ofstream out(filename);
    if(!out.is_open()){
        cout << "【错误】无法写入文件：" << filename << endl;
        return false;
    }

    for(int u=1;u<=n;u++){
        for(auto i : adj[u]){
            int v = i.first, w = i.second;
            if(u<v)out<<u<<" "<<v<<" "<<w<<endl;
        }
    }

    out.close();
    return true;
}

bool Graph::loadFromFile()
{
    std::ifstream in(filename);
    if(!in.is_open()){
        std::cout << "【错误】无法打开道路文件：" << filename << std::endl;
        return false;
    }

    int u,v,w;
    while(in>>u>>v>>w){
        if (u <= 0 || v <= 0 || u > n || v > n || w <= 0) {
            std::cout << "【警告】非法道路数据："
                      << u << " " << v << " " << w << std::endl;
            continue;
        }
        addEdge(u, v, w, false);
    }

    in.close();

    return true;
}

void Graph::addEdge(int u, int v, int w, bool needToSave)
{
    if (u <= 0 || v <= 0 || u > n || v > n) {
        cout << "【错误】顶点超出范围，无法添加道路\n";
        return;
    }
    if (w <= 0) {
        cout << "【错误】路程长度必须为正\n";
        return;
    }
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
    if(needToSave)this->saveToFile();
}