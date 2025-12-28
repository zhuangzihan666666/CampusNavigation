#include "place.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

PlaceManager::PlaceManager(const std::string &filename) : filename(filename)
{

}


// 从文件加载地点数据
bool PlaceManager::loadFromFile()
{
    ifstream in(filename);
    if (!in.is_open())
    {
        cout << "ERROR: 无法打开文件：" << filename << endl;
        return false;
    }

    places.clear();
    idIndex.clear();

    Place p;
    while (in >> p.id >> p.name)
    {
        if (idIndex.count(p.id))
        {
            cout << "WRONG: 地点编号重复：" << p.id << endl;
            continue;
        }
        idIndex[p.id] = places.size();
        places.push_back(p);
    }

    in.close();
    return true;
}

// 保存到文件
bool PlaceManager::saveToFile() const
{
    ofstream out(filename);
    if (!out.is_open()) {
        cout << "【错误】无法写入文件：" << filename << endl;
        return false;
    }

    for (const auto& p : places) {
        out << p.id << " "
             << p.name << endl;
    }

    out.close();
    return true;
}

// 添加新地点
bool PlaceManager::addPlace(int id, const std::string &name)
{
    if (idIndex.count(id)) {
        cout << "【错误】地点编号已存在：" << id << endl;
        return false;
    }

    Place p{ id, name};
    idIndex[id] = places.size();
    places.push_back(p);
    this->saveToFile();
    return true;
}

// 删除地点
bool PlaceManager::deletePlace(int id) {
    if (!idIndex.count(id)) {
        cout << "【错误】地点不存在：" << id << endl;
        return false;
    }

    int idx = idIndex[id];
    int lastIdx = places.size() - 1;

    // 用最后一个元素覆盖被删除元素
    places[idx] = places[lastIdx];
    idIndex[places[idx].id] = idx;

    places.pop_back();
    idIndex.erase(id);

    return true;
}

// 修改地点信息
bool PlaceManager::updatePlace(int id, const std::string &newName)
{  
    Place* p = findById(id);
    if (!p) {
        cout << "【错误】地点不存在：" << id << endl;
        return false;
    }

    p->name = newName;
    return true;
}

// 按 id 查找
Place* PlaceManager::findById(int id) {
    if (!idIndex.count(id)) return nullptr;
    return &places[idIndex[id]];
}


// 按名称关键字查找
vector<Place*> PlaceManager::findByName(const string& keyword) {
    vector<Place*> result;
    for (auto& p : places) {
        if (p.name.find(keyword) != string::npos) {
            result.push_back(&p);
        }
    }   
    return result;
}

// 打印所有地点
void PlaceManager::printAll() const {
    cout << "ID\t名称\n";
    for (const auto& p : places) {
        cout << p.id << "\t"
             << p.name << endl;
    }
}

// 返回地点数量
int PlaceManager::size() const {
    return places.size();
}

// 获取全部地点
const vector<Place>& PlaceManager::getAll() const {
    return places;
}

// 确定选择地点
int PlaceManager::decidePlace(const std::string &keyword)
{
    vector<Place*> p = this->findByName(keyword);
    int sum = p.size();
    if(sum == 0){
        // cout << "地点名称不存在\n";
        return -1;
    }
    else if(sum == 1){
        return p[0]->id;
    }
    else{
        int idx=1;
        cout<<"匹配到多个地址，请输入序号确定"<<endl;
        for(auto i : p){
            cout<<idx<<": "<<i->name<<endl;
            idx++;
        }
        int ok = -1;
        cout<<"请输入: "<<endl;
        while(cin>>ok){
            if(ok<1||ok>idx){
                cout<<"序号不存在，请重新输入"<<endl;
            }
            else{
                return p[ok-1]->id;
                break;
            }
        }
    }

    return 0;
}
